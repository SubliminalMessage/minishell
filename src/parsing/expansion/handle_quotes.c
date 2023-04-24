/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonza <dangonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 17:27:52 by dangonza          #+#    #+#             */
/*   Updated: 2023/04/24 18:46:15 by dangonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

// Norminette issues. 
// For some reason Logic Operations causes 'Missing tabs for indent level'
static t_bool	check_if_unclosed(char quote, char char_at)
{
	if ((quote == '\'' || quote == '\"') && char_at != quote)
		return (true);
	return (false);
}

char	*dequote(char *str)
{
	size_t	s_len;
	t_bool	is_unclosed;
	char	quote;
	char	*dequoted;

	if (!str)
		return (NULL);
	quote = str[0];
	s_len = ft_strlen(str);
	is_unclosed = check_if_unclosed(quote, str[s_len - 1]);
	if ((s_len == 1 && (quote == '\'' || quote == '"')) || is_unclosed)
	{
		if (quote == '\'')
			print_parse_error(INV_TKN_MSG" `\''", false);
		else
			print_parse_error(INV_TKN_MSG" `\"'", false);
		free(str);
		return (NULL);
	}
	if (quote != '\'' && quote != '"')
		return (str);
	dequoted = ft_substr(str, 1, s_len - 2);
	free(str);
	return (dequoted);
}

char	*get_next_quote(char *str, size_t *idx)
{
	char	quote;
	size_t	quote_idx;
	char	*quoted_str;

	if (!str)
		return (NULL);
	quote = '\0';
	if (str[0] == '\'' || str[0] == '"')
		quote = str[0];
	quote_idx = 0;
	while (str[++quote_idx])
		if (str[quote_idx] == '\'' || str[quote_idx] == '"')
			if (quote == '\0' || str[quote_idx] == quote)
				break ;
	if (quote != '\'' && quote != '"')
		quote_idx--;
	if (str[quote_idx] == '$' && quote == '\0' && str[quote_idx + 1] != '\0')
	{
		quote_idx--;
		*idx += 1;
	}
	quoted_str = ft_substr(str, 0, quote_idx + 1);
	*idx += quote_idx + 1;
	return (quoted_str);
}
