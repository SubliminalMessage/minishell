/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jre-gonz <jre-gonz@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 11:44:07 by jre-gonz          #+#    #+#             */
/*   Updated: 2023/03/26 16:21:27 by jre-gonz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "debug_minishell.h" // TODO use minishell.h

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 4096
#endif

/**
 * @brief Copies all the content of a file descriptor into another.
 * @note The file descriptors are not closed.
 * @note The file descriptors are not checked.
 * @note If an error occurs, the number of bytes copied is returned.
 * 
 * @param rfd The file descriptor to read from.
 * @param wfd The file descriptor to write to.
 * @return int The number of bytes copied.
 */
int	ft_copyall(int rfd, int wfd)
{
	int		r;
	int		total;
	char	buffer[BUFFER_SIZE];

	total = 0;
	while (true)
	{
		r = read(rfd, buffer, BUFFER_SIZE);
		if (r == INVALID)
			break ;
		write(wfd, buffer, r);
		total += r;
		if (r < BUFFER_SIZE)
			break ;
	}
	return (total);
}
