/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonza <dangonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 18:15:42 by dangonza          #+#    #+#             */
/*   Updated: 2023/04/24 18:27:59 by dangonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_bool	is_redirection(char *string)
{
	if (!string)
		return (false);
	return (string[0] == '>' || string[0] == '<');
}

// 'INVALID' Should never be reached
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
	return (INVALID);
}

t_bool	is_invalid_argument(char *string)
{
	if (contains_outside_quotes(string, ';'))
		return (false);
	if (contains_outside_quotes(string, '\\'))
		return (false);
	return (true);
}

t_file	*create_file(char *identifier, int redirection_type)
{
	if (redirection_type == HEREDOC_FTYPE)
		return (ft_new_here_doc(identifier));
	return (ft_newfile(identifier, redirection_type));
}

t_bool	contains_outside_quotes(char *str, char c)
{
	char	in_quote;
	int		i;

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
			print_parse_error_str(INV_TKN_MSG" `", ft_chardup(c));
			return (true);
		}
		i++;
	}
	return (false);
}
