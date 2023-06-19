/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jre-gonz <jre-gonz@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 17:27:52 by dangonza          #+#    #+#             */
/*   Updated: 2023/06/18 00:07:49 by jre-gonz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/**
 * @brief Given a type of quote, and the last char of a string,
 *        returns if the String Quotes are closed or not.
 * 
 * @param quote, que type of quote. (\' for simple quotes, \" for double, 
 *        and \0 for no-quotes).
 * @param last_char, the last char of the string
 * 
 * @return t_bool, whether the string's quotes are closed or not
 * 
 * @note This function were created because Norminette Issues.
 *       For some reason, Logic Operations as a Variable Asignation
 *       (e.g.: 't_bool a = b || c;' ) causes 'Missing tabs for indent level',
 * 		 or at least this logic operation does :(
*/
static t_bool	check_if_closed(char quote, char last_char)
{
	if ((quote == '\'' || quote == '\"') && last_char != quote)
		return (false);
	return (true);
}

/**
 * @brief Given a string wrapped in quotes (or not), dequotes them if needed
 *        and returns the result.
 * @note  This function is similar to dequote(), but it doesn't expand the
 *        variables inside of the string.
 * 
 * @param str 
 * @return char* 
 */
char	*dequote_all(char *str)
{
	char	*final_str;
	char	*next_quote;
	size_t	idx;

	if (!str)
		return (str);
	idx = 0;
	final_str = str;
	next_quote = get_next_quote(str + idx, &idx);
	if (!next_quote || str_equals(next_quote, ""))
		return (ft_strdup(""));
	final_str = join_two(dequote(next_quote), dequote_all(str + idx));
	return (final_str);
}

/**
 * @brief Given a string wrapped in quotes (or not), dequotes them if needed
 *        and returns the result.
 * 
 * @param str, the String wrapped in quotes (or not)
 * 
 * @return char*, the new String after De-Quoting it. Can be NULL if the quotes
 *         are not closed.
*/
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
	is_unclosed = !check_if_closed(quote, str[s_len - 1]);
	if ((s_len == 1 && (quote == '\'' || quote == '"')) || is_unclosed)
	{
		ft_store_result_code(258, true);
		if (quote == '\'')
			print_parse_error(MINISHELL_ERROR INV_TKN_MSG" `\''", false);
		else
			print_parse_error(MINISHELL_ERROR INV_TKN_MSG" `\"'", false);
		free(str);
		return (NULL);
	}
	if (quote != '\'' && quote != '"')
		return (str);
	dequoted = ft_substr(str, 1, s_len - 2);
	free(str);
	return (dequoted);
}

/**
 * @brief Given a String that contains zero or more quoted-characters,
 *        returns the first quoted group of characters it encounters.
 * 
 * @param str, the String to check
 * @param idx, the index of the original string, to skip the characters
 *       we're about to remove. It's just to ensure correct behaviour!
 * 
 * @return char*, the next quoted group of chars. If there are none, the
 *         whole string will be returned.
*/
char	*get_next_quote(char *str, size_t *idx)
{
	char	quote;
	size_t	quote_idx;
	char	*quoted_str;

	if (!str || str_equals(str, ""))
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
