/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonza <dangonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 01:38:45 by dangonza          #+#    #+#             */
/*   Updated: 2023/04/22 01:40:12 by dangonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_bool is_redirection(char *string)
{
	if (!string)
		return (false);
	return (str_equals(string, ">") || str_equals(string, ">>") || str_equals(string, "<") || str_equals(string, "<<"));
}

int	get_redirection_type(char *redirection)
{
	if (str_equals(redirection, ">"))
		return (TRUNC_FTYPE);
	if (str_equals(redirection, ">>"))
		return (APPEND_FTYPE);
	if (str_equals(redirection, "<"))
		return (READ_FTYPE);
	if (str_equals(redirection, "<<"))
		return (HEREDOC_FTYPE);
	return (INVALID); // Should never be reached
}

t_bool	fill_redirections(t_cmd **cmd, char ***str_array)
{
	char **argv;
	int	i;

	argv = *str_array;
	i = -1;
	while (argv[++i])
	{
		if (is_redirection(argv[i]))
		{
			if (save_redirection(cmd, argv[i], argv[i + 1]))
			{
				free(argv[i]);
				argv[i] = ft_strdup(""); // Places a '\0' on that position
				argv[++i] = ft_strdup(""); // clean_nulls() will delete these two after
			}
			else
				return (false);
		}
	}
	*str_array = clean_nulls(*str_array);
	return (true);
}

t_bool save_redirection(t_cmd **cmd, char *redirection, char *redirects_to)
{
	int	redirection_type;
	t_file	*file;

	if (!redirects_to || redirects_to[0] == '>' || redirects_to[0] == '<')
	{
		if (!redirects_to)
			printf(INVALID_TOKEN_STR, "\\n");
		else
			printf(INVALID_TOKEN_CHR, redirects_to[0]);
		return (false);
	}
	redirection_type = get_redirection_type(redirection);
	file = ft_newfile(redirects_to, redirection_type);
	if (!file)
	{
		printf(ERROR_MALLOC);
		return (false);
	}
	if (redirection_type == TRUNC_FTYPE || redirection_type == APPEND_FTYPE)
		ft_lstadd_back(&(*cmd)->out, ft_lstnew(file));
	else if (redirection_type == READ_FTYPE || redirection_type == HEREDOC_FTYPE)
		ft_lstadd_back(&(*cmd)->in, ft_lstnew(file));
	return (true);
}