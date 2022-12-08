/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_str.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonza <dangonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 17:27:22 by dangonza          #+#    #+#             */
/*   Updated: 2022/12/08 00:51:04 by dangonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/**
 * @brief Compares two strings and returns a boolean
 * 
 * @return int, 0 if not equal, 1 otherwise
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

// this also normalizes the quotes (if a quote is not ended, it adds it) making arguments trim-able :)
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
    {
        if (str[i] == '\'' || str[i] == '\"')
        {
            if (in_quote == '\0')
                in_quote = str[i];
            else if (in_quote == str[i])
                in_quote = '\0';
        }
    }
    if (in_quote != '\0')
        str = join_three(str, ft_strdup(&in_quote), ft_strdup("")); // join_three to free 'str'. ft_strjoin() does not frees it
    aux = ft_strtrim(str, set);
    free(str);
    return (aux);
}

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