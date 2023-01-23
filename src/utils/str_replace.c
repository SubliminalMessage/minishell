/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_replace.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonza <dangonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 14:29:55 by dangonza          #+#    #+#             */
/*   Updated: 2023/01/23 13:25:36 by dangonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/**
 * @brief Finds a string in another, and return the index of the first char
 * 
 * @return int, if the string isn't present, -1, 
 *  otherwise the index of the first char
*/
int	str_index_of(char *str, char *to_find, int from)
{
	char	*occurrency;

	occurrency = ft_strnstr(str + from, to_find, ft_strlen(str));
	if (occurrency == NULL)
		return (-1);
	return (occurrency - str);
}

/**
 * @brief Replaces the first occurency of a string for another
 * 
 * @param str, the String where the string to replace is hidden
 * @param find, the String to find and replace
 * @param replacement, the new String that will replace the old one
 * @param from, the index from to start looking for a string to replace.
 *  set to 0 for default behaviour
 * 
 * @return char *, the new string with the replacement done
*/
char	*str_replace(char *str, char *find, char *replacement, int from)
{
	char	*first_fragment;
	char	*second_fragment;
	char	*result;
	int		index;

	index = str_index_of(str, find, from);
	if (index == -1)
	{
		free(find);
		free(replacement);
		return (str);
	}
	first_fragment = ft_substr(str, 0, index);
	second_fragment = ft_substr(str, index + ft_strlen(find), ft_strlen(str));
	result = join_three(first_fragment, replacement, second_fragment);
	free(str);
	free(find);
	return (result);
}
