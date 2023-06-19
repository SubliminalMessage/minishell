/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonza <dangonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 17:45:54 by dangonza          #+#    #+#             */
/*   Updated: 2023/06/19 20:33:54 by dangonza         ###   ########.fr       */
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

	str = ft_calloc(2, sizeof(char));
	if (str == NULL)
		return (0);
	str[0] = c;
	str[1] = '\0';
	return (str);
}

/**
 * @brief Given a string, returns the last character
 *
 * @param str, the String to read
 *
 * @return char, the last character of the string. If the string is Empty ("")
 *         or NULL, it will be '\0'.
*/
char	last_char(char *str)
{
	size_t	len;

	if (!str)
		return ('\0');
	len = ft_strlen(str);
	if (len == 0)
		return (str[0]);
	return (str[len - 1]);
}

t_bool	is_valid(char *line)
{
	size_t	i;

	if (!line)
		return (true);
	i = 0;
	while (line[i])
	{
		if (line[i] > 0 && line[i] < ' ')
			return (false);
		i++;
	}
	return (true);
}
