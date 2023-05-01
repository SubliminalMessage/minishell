/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonza <dangonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 01:38:45 by dangonza          #+#    #+#             */
/*   Updated: 2023/05/01 16:50:03 by dangonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	last_char(char *str)
{
	size_t len;

	if (!str)
		return ('\0');
	len = ft_strlen(str);
	if (len <= 0)
		return (str[0]);
	return (str[len - 1]);
}
void	split_redirection(char **arg, char **redir)
{
	int		index;
	char	*aux;

	index = index_of_outside_quotes(*arg, "<>");
	if (index == -1)
		return ;
	*redir = join_two(*redir, ft_substr(*arg, index, ft_strlen(*arg)));
	aux = ft_substr(*arg, 0, index);
	free(*arg);
	*arg = aux;
}
static t_bool	handle_redirection_argument(char **arg, char **redir)
{
	if (ft_hasany("<>", last_char(*redir))) // Ends with '>' or '<'
	{
		if (ft_hasany("<>", *arg[0]))
			return (true);
		*redir = join_two(*redir, *arg);
		*arg = ft_strdup("");
	}
	else if (contains_outside_quotes(*arg, "<>"))
		split_redirection(arg, redir);
	return (false);
}

/**
 * @brief Given a Command, converts all redirections into f_files and
 * 		  saves them into their corresponding structure of the command.
 * 
 * @param cmd Double pointer to the command. Will be modified
 * 
 * @return t_bool, whether if everything went OK or not.
*/
t_bool	fill_redirections(t_cmd **cmd)
{
	char	**argv;
	char	*redirs;
	int		i;

	if (!cmd || !*cmd || !(*cmd)->args)
		return (false);
	argv = (*cmd)->args;
	i = -1;
	redirs = ft_strdup("");
	while (argv[++i])
	{
		if (!is_valid_argument(argv[i]))
		{
			free(redirs);
			return (false);
		}
		if (handle_redirection_argument(&argv[i], &redirs))
			break ;
	}
	if (ft_hasany("<>", last_char(redirs)))
	{
		print_parse_error_str(INV_TKN_MSG" `", ft_chardup(last_char(redirs)));
		free(redirs);
		return (false);
	}
	(*cmd)->args = clean_nulls((*cmd)->args);
	
	t_bool to_return = save_redirection_single_arg(cmd, redirs);
	return (to_return);
}
/**
 * @brief Given a single argument representing both a redirection and the
 *        identifier of the redirection, saves it into a command.
 * 
 * @param cmd, the Command to where the redirection will be saved to
 * @param redir, the redirection + identifier (e.g.: '>file')
 * 
 * @return t_bool, whether if it went OK or not.
*/
t_bool	save_redirection_single_arg(t_cmd **cmd, char *redir)
{
	size_t	redir_length;
	size_t	redir_end;
	char	*redirection;
	char	*redirects_to;
	t_bool	did_work;

	redir_length = ft_strlen(redir);
	if (redir_length <= 0)
	{
		free(redir);
		return (true);
	}
	redir_end = 1;
	if (redir_length >= 2 && (redir[1] == '>' || redir[1] == '<'))
		redir_end++;
	if (redir_end == 2 && redir[0] != redir[1])
	{
		print_parse_error_str(INV_TKN_MSG" `", ft_chardup(redir[1]));
		free(redir);
		return (false);
	}
	redirection = ft_substr(redir, 0, redir_end);
	redirects_to = ft_substr(redir, redir_end, redir_length);
	did_work = save_redirection_double(cmd, redirection, redirects_to);
	free(redirection);
	if (!did_work)
		free(redirects_to);
	free(redir);
	return (did_work);
}

static void get_next_redirection(char **identifier, char **leftover)
{
	int		idx;
	char	*aux;

	*leftover = NULL;
	if (!*identifier)
		return ;
	idx = index_of_outside_quotes(*identifier, "<>");
	if (idx != -1)
	{
		aux = ft_substr(*identifier, 0, idx);
		*leftover = ft_substr(*identifier, idx, ft_strlen(*identifier));
		free(*identifier);
		*identifier = aux;
	}
}

/**
 * @brief Given a redirection and the identifier, creates and saves the
 *        redirection file into the command.
 * 
 * @param cmd, the Command where the redirection will be saved to
 * @param redir, the redirection (e.g.: '>')
 * @param identifier, the identifier (e.g.: 'file')
 * 
 * @return t_bool, whether if it went OK or not.
*/
t_bool	save_redirection_double(t_cmd **cmd, char *redir, char *identifier)
{
	int		redir_type;
	char	*leftover;
	t_file	*file;

	if (!identifier || identifier[0] == '>' || identifier[0] == '<')
	{
		if (!identifier)
			print_parse_error_str(INV_TKN_MSG" `", ft_strdup("\\n"));
		else
			print_parse_error_str(INV_TKN_MSG" `", ft_chardup(identifier[0]));
		return (false);
	}
	redir_type = get_redirection_type(redir);
	get_next_redirection(&identifier, &leftover);
	file = create_file(identifier, redir_type);
	if (!file)
	{
		print_parse_error(ERROR_MALLOC, false);
		if (leftover)
			free(leftover);
		return (false);
	}
	if (redir_type == TRUNC_FTYPE || redir_type == APPEND_FTYPE)
		ft_lstadd_back(&(*cmd)->out, ft_lstnew(file));
	else if (redir_type == READ_FTYPE || redir_type == HEREDOC_FTYPE)
		ft_lstadd_back(&(*cmd)->in, ft_lstnew(file));
	if (leftover != NULL)
		return (save_redirection_single_arg(cmd, leftover));
	return (true);
}
