/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_str.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonza <dangonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 17:27:22 by dangonza          #+#    #+#             */
/*   Updated: 2023/04/24 19:03:02 by dangonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/**
 * @brief Compares two strings and returns a boolean
 * 
 * @return boolean, true if the strings are equal, false otherwise
*/
t_bool	str_equals(char *a, char *b)
{
	size_t	a_len;

	a_len = ft_strlen(a);
	if (a_len != ft_strlen(b))
		return (false);
	if (ft_strncmp(a, b, a_len) != 0)
		return (false);
	return (true);
}

/**
 * @brief Normalizes the quotes in a string, adding the missing quotes.
 *        Then, it trims the string, and frees the original one.
 * 
 * @param str, the string to be trimmed
 * @param set, the set of characters to be trimmed off
 * 
 * @return char*, the trimmed and normalized string
*/
char	*ft_strtrim_free(char *str, char *set)
{
	char	*aux;
	char	in_quote;
	int		i;

	if (!str)
		return (NULL);
	in_quote = '\0';
	i = -1;
	while (str[++i])
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			if (in_quote == '\0')
				in_quote = str[i];
			else if (in_quote == str[i])
				in_quote = '\0';
		}
	}
	aux = ft_strtrim(str, set);
	free(str);
	return (aux);
}

static void	clean_nulls_init_vars(int *n_count, int *str_idx, int *f_idx)
{
	*n_count = 0;
	*str_idx = -1;
	*f_idx = -1;
}

/**
 * @brief Filters a string array, removing all the NULL elements
 * 
 * @param str, the array of strings to be filtered 
 * 
 * @return char**, the filtered array with no NULL elements (or '\0' strings)
*/
char	**clean_nulls(char **str)
{
	int		null_count;
	int		str_index;
	int		final_index;
	char	**final;

	clean_nulls_init_vars(&null_count, &str_index, &final_index);
	while (str && str[++str_index])
		if (*(str[str_index]) == '\0')
			null_count++;
	if (null_count == 0)
		return (str);
	final = ft_calloc(str_index - null_count + 1, sizeof(char *));
	if (!final)
		return (NULL);
	str_index = -1;
	while (str[++str_index])
	{
		if (*(str[str_index]) != '\0')
			final[++final_index] = str[str_index];
		else
			free(str[str_index]);
	}
	free(str);
	return (final);
}

/**
 * @brief Frees a string array
 * 
 * @param array, the array to be freed
*/
void	free_str_array(char **array)
{
	int	i;

	i = -1;
	while (array[++i])
		free(array[i]);
	free(array);
}
