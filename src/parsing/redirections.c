/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonza <dangonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 01:38:45 by dangonza          #+#    #+#             */
/*   Updated: 2023/04/23 18:34:23 by dangonza         ###   ########.fr       */
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

t_bool contains_outside_quotes(char *str, char c) // TODO: Move this function to a more appropiate file
{
	char	in_quote;
	int	i;

	if (c == '\'' || c == '"')
		return (false);
	in_quote = '\0';
	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
		{
			if (str[i] == in_quote)
				in_quote = '\0';
			else if (in_quote == '\0')
				in_quote = str[i];
		}
		if (str[i] == c && in_quote == '\0')
		{
			printf(INVALID_TOKEN_CHR, c);
			return (true);
		}
		i++;
	}
	return (false);
}

t_bool is_invalid_argument(char *string) // TODO: Move this function to a more appropiate file
{
	if (contains_outside_quotes(string, ';'))
		return (false);
	if (contains_outside_quotes(string, '\\'))
		return (false);
	return (true);
}

t_bool	fill_redirections(t_cmd **cmd) // TODO: echo >file does not work
{
	char **argv;
	int	i;

	argv = (*cmd)->args;
	i = -1;
	while (argv[++i])
	{
		if (is_redirection(argv[i]))
		{
			if (save_redirection(cmd, argv[i], argv[i + 1])) // TODO: Split into two: single arg, and double arg
			{
				free(argv[i]);
				argv[i] = ft_strdup(""); // Places a '\0' on that position
				argv[++i] = ft_strdup(""); // clean_nulls() will delete these two after
			}
			else
				return (false);
		}
		else if (!is_invalid_argument(argv[i]))
			return (false);
	}
	(*cmd)->args = clean_nulls((*cmd)->args);
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
