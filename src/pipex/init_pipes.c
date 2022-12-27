/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_pipes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jre-gonz <jre-gonz@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 21:18:55 by jre-gonz          #+#    #+#             */
/*   Updated: 2022/12/27 09:34:44 by jre-gonz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/**
 * @brief Creates the pipes need to communicate the processes.
 *
 * Keep in mind the amount of of pipes are num(cmd) - 1.
 * 2 fds per pipe.
 *
 * pipex(3): input fd1.in fd1.out fd2.in fd2.out out
 *
 * @param pipex Structure that contains will contain the pipes.
 */
void	ft_init_pipes(t_pipex *pipex)
{
	int	i;

	pipex->fds = malloc(sizeof(int) * (pipex->cmd_count - 1) * 2);
	if (!pipex->fds)
		ft_free_end(pipex, 1, ERROR_MALLOC);
	i = 0;
	while (i < pipex->cmd_count - 1)
	{
		if (pipe(&(pipex->fds[2 * i])) != 0)
			ft_free_end(pipex, 1, ERROR_PIPE_INIT);
		i++;
	}
}
