/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonza <dangonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 17:45:54 by dangonza          #+#    #+#             */
/*   Updated: 2023/04/25 16:15:29 by dangonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/**
 * @brief Given two strings, joins them and free()-s its content.
 * 
 * @param a, the first string
 * @param b, the second string
 * 
 * @return char*, the string resulting of joining those two
*/
char	*join_two(char *a, char *b)
{
	char	*final;

	if (!a || !b)
	{
		if (a)
			free(a);
		if (b)
			free(b);
		return (NULL);
	}
	final = ft_strjoin(a, b);
	free(a);
	free(b);
	return (final);
}

/**
 * @brief Joins three strings, freeing each of them
 * 
 * @param a, the first string
 * @param b, the second string
 * @param c, the third string
 * 
 * @return char*, the joined string
*/
char	*join_three(char *a, char *b, char *c)
{
	return (join_two(join_two(a, b), c));
}

/**
 * @brief Duplicates a char.
 * 
 * @param c Char to duplicate.
 * @return char* New char* with the result.
 */
char	*ft_chardup(const char c)
{
	char	*str;

	str = malloc(sizeof(char) * 2);
	if (str == NULL)
		return (0);
	str[0] = c;
	str[1] = '\0';
	return (str);
}