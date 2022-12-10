/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_str.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonza <dangonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 17:27:22 by dangonza          #+#    #+#             */
/*   Updated: 2022/12/10 19:51:27 by dangonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/**
 * @brief Compares two strings and returns a boolean
 * 
 * @return boolean, true if the strings are equal, false otherwise
*/
t_bool str_equals(char* a, char* b)
{
    size_t a_len;

    a_len = ft_strlen(a);
    if (a_len != ft_strlen(b))
        return (false);
    if (ft_strncmp(a, b, a_len) != 0)
        return (false);
    return (true);
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
char *join_three(char *a, char *b, char *c)
{
    char *auxOne;
    char *auxTwo;

    auxOne = ft_strjoin(a, b);
    auxTwo = ft_strjoin(auxOne, c);
    free(a);
    free(b);
    free(c);
    free(auxOne);
    return (auxTwo);
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
char *ft_strtrim_free(char *str, char *set)
{
    char *aux;
    char in_quote;
    int i;

    if (!str)
        return (NULL);
    in_quote = '\0';
    i = -1;
    while (str[++i])
        if (str[i] == '\'' || str[i] == '\"')
        {
            if (in_quote == '\0')
                in_quote = str[i];
            else if (in_quote == str[i])
                in_quote = '\0';
        }
    if (in_quote != '\0')
        str = join_three(str, ft_chardup(in_quote), ft_chardup('\0')); // join_three to free 'str'. ft_strjoin() does not frees it
    aux = ft_strtrim(str, set);
    free(str);
    return (aux);
}

/**
 * @brief Filters a string array, removing all the NULL elements
 * 
 * @param str, the array of strings to be filtered 
 * 
 * @return char**, the filtered array with no NULL elements (or '\0' strings)
*/
char **clean_nulls(char **str)
{
    int null_count;
    int str_index;
    int final_index;
    char **final;

    null_count = 0;
    str_index = -1;
    while (str[++str_index])
        if (*(str[str_index]) == '\0')
            null_count++;
    if (null_count == 0)
        return (str);
    final = malloc(sizeof(char *) * (str_index - null_count + 1));
    final[str_index - null_count] = NULL;
    str_index = -1;
    final_index = -1;
    while (str[++str_index])
        if (*(str[str_index]) != '\0')
            final[++final_index] = str[str_index];
        else
            free(str[str_index]);
    free(str);
    return (final);
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

/**
 * @brief Frees a string array
 * 
 * @param array, the array to be freed
*/
void    free_str_array(char **array)
{
    int i;

    i = -1;
    while (*(array + ++i))
        free(*(array + i));
    free(array);
}