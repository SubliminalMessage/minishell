/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_str.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonza <dangonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 17:27:22 by dangonza          #+#    #+#             */
/*   Updated: 2022/11/27 18:24:17 by dangonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/**
 * @brief Compares two strings and returns a boolean
 * 
 * @return int, 0 if not equal, 1 otherwise
*/
bool strEquals(char* a, char* b)
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