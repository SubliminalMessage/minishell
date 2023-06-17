/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arrsize.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jre-gonz <jre-gonz@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 21:22:14 by jre-gonz          #+#    #+#             */
/*   Updated: 2023/06/12 21:22:23 by jre-gonz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/**
 * @brief Returns the size of an array of strings.
 * 
 * @param array, the array
 * 
 * @param int, the size of the array.
 */
int	ft_arrsize(char **array)
{
	int	i;

	if (!array || !(*array))
		return (0);
	i = 0;
	while (array[i])
		i++;
	return (i);
}
