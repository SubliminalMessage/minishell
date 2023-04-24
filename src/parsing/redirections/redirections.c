/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonza <dangonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 01:38:45 by dangonza          #+#    #+#             */
/*   Updated: 2023/04/24 18:46:21 by dangonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_bool	fill_redirections(t_cmd **cmd)
{
	char	**argv;
	int		i;

	argv = (*cmd)->args;
	i = -1;
	while (argv[++i])
	{
		if (is_redirection(argv[i]))
		{
			if (!save_redirection(cmd, &argv[i], &argv[i + 1]))
				return (false);
		}
		else if (!is_invalid_argument(argv[i]))
			return (false);
	}
	(*cmd)->args = clean_nulls((*cmd)->args);
	return (true);
}

t_bool	save_redirection(t_cmd **cmd, char **first_arg, char **second_arg)
{
	t_bool	did_work;
	char	*a;

	a = *first_arg;
	if (str_equals(a, ">") || str_equals(a, ">>")
		|| str_equals(a, "<") || str_equals(a, "<<"))
	{
		did_work = save_redirection_double(cmd, *first_arg, *second_arg);
		if (!did_work)
			return (false);
		free(*first_arg);
		*first_arg = ft_strdup("");
		*second_arg = ft_strdup("");
		return (true);
	}
	did_work = save_redirection_single_arg(cmd, *first_arg);
	if (did_work)
	{
		free(*first_arg);
		*first_arg = ft_strdup("");
	}
	return (did_work);
}

t_bool	save_redirection_single_arg(t_cmd **cmd, char *redir)
{
	size_t	redir_length;
	size_t	redir_end;
	char	*redirection;
	char	*redirects_to;
	t_bool	did_work;

	redir_length = ft_strlen(redir);
	redir_end = 1;
	if (redir_length >= 2 && (redir[1] == '>' || redir[1] == '<'))
		redir_end++;
	if (redir_end == 2 && redir[0] != redir[1])
	{
		print_parse_error_str(INV_TKN_MSG" `", ft_chardup(redir[1]));
		return (false);
	}
	redirection = ft_substr(redir, 0, redir_end);
	redirects_to = ft_substr(redir, redir_end, redir_length);
	did_work = save_redirection_double(cmd, redirection, redirects_to);
	free(redirection);
	if (!did_work)
		free(redirects_to);
	return (did_work);
}

t_bool	save_redirection_double(t_cmd **cmd, char *redir, char *identifier)
{
	int		redir_type;
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
	file = create_file(identifier, redir_type);
	if (!file)
	{
		print_parse_error(ERROR_MALLOC, false);
		return (false);
	}
	if (redir_type == TRUNC_FTYPE || redir_type == APPEND_FTYPE)
		ft_lstadd_back(&(*cmd)->out, ft_lstnew(file));
	else if (redir_type == READ_FTYPE || redir_type == HEREDOC_FTYPE)
		ft_lstadd_back(&(*cmd)->in, ft_lstnew(file));
	return (true);
}
