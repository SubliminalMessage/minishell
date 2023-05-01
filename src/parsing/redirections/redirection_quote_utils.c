/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_quote_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonza <dangonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 16:58:43 by dangonza          #+#    #+#             */
/*   Updated: 2023/05/01 19:39:03 by dangonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/**
 * @brief Given a string and some characters, checks if any of those characters
 *        are present in the string, but outside quotes.
 * 
 * @brief str, the String to check
 * @brief c, the String of Chars to look for
 * 
 * @return t_bool, whether any character is present and outside quotes, or not
*/
t_bool	contains_outside_quotes(char *str, char *c)
{
	if (index_of_outside_quotes(str, c) != -1)
		return (true);
	return (false);
}

/**
 * @brief Given a string and some characters, checks if any of those characters
 *        are present in the string, and returns the index of the first one
 * 
 * @brief str, the String to check
 * @brief c, the String of Chars to look for
 * 
 * @return int, the index of the first character found
*/
int	index_of_outside_quotes(char *str, char *c)
{
	char	in_quote;
	int		i;

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
		if (ft_hasany(c, str[i]) && in_quote == '\0')
			return (i);
		i++;
	}
	return (-1);
}
