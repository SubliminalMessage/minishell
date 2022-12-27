/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   use_pipe.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jre-gonz <jre-gonz@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 13:41:16 by jre-gonz          #+#    #+#             */
/*   Updated: 2022/12/27 09:33:11 by jre-gonz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/**
 * @brief Set's the given arguments as file descriptors of stdin and stdout.
 * Closes the given file descriptors.
 * 
 * @param fd_in File descriptor of stdin.
 * @param fd_out File descriptor of stdout.
 */
void	ft_use_pipe(int *fd_in, int *fd_out)
{
	dup2(*fd_in, STDIN);
	dup2(*fd_out, STDOUT);
	ft_close_fd(fd_in);
	ft_close_fd(fd_out);
}
