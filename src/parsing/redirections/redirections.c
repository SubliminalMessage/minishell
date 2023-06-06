/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonza <dangonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 01:38:45 by dangonza          #+#    #+#             */
/*   Updated: 2023/06/06 17:33:44 by dangonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

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
	char	*redirs;
	int		i;

	if (!cmd || !*cmd || !(*cmd)->args)
		return (false);
	i = -1;
	redirs = ft_strdup("");
	while (((*cmd)->args)[++i])
	{
		if (!is_valid_argument(((*cmd)->args)[i]))
		{
			free(redirs);
			return (false);
		}
		if (handle_redirection_argument(&((*cmd)->args)[i], &redirs))
			break ;
	}
	if (ft_hasany("<>", last_char(redirs)))
	{
		print_parse_error_str(INV_TKN_MSG" `", ft_chardup(last_char(redirs)));
		free(redirs);
		return (false);
	}
	(*cmd)->args = clean_nulls((*cmd)->args);
	return (save_redirection_single_arg(cmd, redirs));
}
/**
 * @brief Auxiliar function of 'save_redirection_single_arg()', due to
 *        Norminette's rules :(
 * 		  Given a 'single-argument redirection', calls to
 *        'save_redirection_double()' with the proper arguments, and
 *        cleans everything up.
 * 
 * @return t_bool, whether if everything did work out OK or not
*/
t_bool	save_and_clear_single_arg(t_cmd **cmd, char *redir, size_t redir_end)
{
	char	*redirection;
	char	*redirects_to;
	t_bool	did_work;
	size_t	redir_length;

	redir_length = ft_strlen(redir);
	redirection = ft_substr(redir, 0, redir_end);
	redirects_to = ft_substr(redir, redir_end, redir_length);
	did_work = save_redirection_double(cmd, redirection, redirects_to);
	free(redirection);
	if (!did_work)
		free(redirects_to);
	free(redir);
	return (did_work);
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
	return (save_and_clear_single_arg(cmd, redir, redir_end));
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
	if (!create_file(&file, identifier, redir_type))
	{
		if (g_status_code != HEREDOC_KILL_CODE)
			print_parse_error(ERROR_MALLOC, false);
		if (leftover)
			free(leftover);
		return (false);
	}
	add_redirection_back(cmd, redir_type, file);
	if (leftover != NULL)
		return (save_redirection_single_arg(cmd, leftover));
	return (true);
}
