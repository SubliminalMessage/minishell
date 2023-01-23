/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dequote.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonza <dangonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 15:46:53 by dangonza          #+#    #+#             */
/*   Updated: 2023/01/23 13:30:39 by dangonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/**
 * @brief De-quotes a single string, whose structure is the following: '<str>'
 * 	It doesn't care about the quote type (either single ' or double " quotes),
 * and the <str> can contain extra quotes if they are valid. For example: " ' "
 * 
 * @param str, the string that will be dequoted
 * @param start, the index of that string where the first quote is located
 * @param end, the end of the quoted-section of the string
 * 
 * @return char*, the string without the extra quotes
*/
char	*dequote_str(char *str, int start, int end)
{
	char	*first_fragment;
	char	*second_fragment;
	char	*middle;

	first_fragment = ft_substr(str, 0, start);
	second_fragment = ft_substr(str, end + 1, ft_strlen(str));
	middle = ft_substr(str + start, 1, end - start - 1);
	free(str);
	return (join_three(first_fragment, middle, second_fragment));
}

/**
 * @brief De-quotes all occurencies of a string
 * 
 * @param str, the string with quotes in it
 * 
 * @return char *, the new string, without any quotes left
 * 
*/
char	*dequote_all(char *str)
{
	char	in_quote;
	int		i;
	int		start;

	i = 0;
	in_quote = '\0';
	while (str[i])
	{
		if (str[i] == in_quote)
		{
			in_quote = '\0';
			str = dequote_str(str, start, i);
			i -= 2;
		}
		else if (in_quote == '\0' && (str[i] == '\'' || str[i] == '"'))
		{
			in_quote = str[i];
			start = i;
		}
		i++;
	}
	return (str);
}
