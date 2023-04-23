/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonza <dangonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 01:38:45 by dangonza          #+#    #+#             */
/*   Updated: 2023/04/23 22:47:11 by dangonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_bool is_redirection(char *string)
{
	if (!string)
		return (false);
	return (string[0] == '>' || string[0] == '<');
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

t_bool	fill_redirections(t_cmd **cmd)
{
	char **argv;
	int	i;

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
	if (str_equals(a, ">") || str_equals(a, ">>") || str_equals(a, "<") || str_equals(a, "<<"))
	{
		did_work = save_redirection_double_arg(cmd, *first_arg, *second_arg);
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

t_bool save_redirection_single_arg(t_cmd **cmd, char *redir)
{
	size_t	redir_length;
	size_t	redir_end;
	char *redirection;
	char *redirects_to;
	t_bool	did_work;

	redir_length = ft_strlen(redir);
	redir_end = 1;
	if (redir_length >= 2 && (redir[1] == '>' || redir[1] == '<'))
		redir_end++;
	if (redir_end == 2 && redir[0] != redir[1])
	{
		printf(INVALID_TOKEN_CHR, redir[1]);
		return (false);
	}
	redirection = ft_substr(redir, 0, redir_end);
	redirects_to = ft_substr(redir, redir_end, redir_length);
	did_work = save_redirection_double_arg(cmd, redirection, redirects_to);
	free(redirection);
	if (!did_work)
		free(redirects_to);
	return (did_work);
}

t_bool save_redirection_double_arg(t_cmd **cmd, char *redirection, char *redirects_to)
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
		print_parse_error(ERROR_MALLOC, false);
		return (false);
	}
	if (redirection_type == TRUNC_FTYPE || redirection_type == APPEND_FTYPE)
		ft_lstadd_back(&(*cmd)->out, ft_lstnew(file));
	else if (redirection_type == READ_FTYPE || redirection_type == HEREDOC_FTYPE)
		ft_lstadd_back(&(*cmd)->in, ft_lstnew(file));
	return (true);
}
