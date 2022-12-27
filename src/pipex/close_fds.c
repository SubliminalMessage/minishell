/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_fds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jre-gonz <jre-gonz@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 19:11:37 by jre-gonz          #+#    #+#             */
/*   Updated: 2022/12/27 09:30:00 by jre-gonz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/**
 * @brief Closes all the file descriptors in the pipex program.
 *
 * @param p pipex structure with all the file descriptors.
 */
void	ft_close_fds(t_pipex *p)
{
	int	i;

	i = 0;
	while (i < p->cmd_count - 1)
	{
		ft_close_fd(&p->fds[2 * i]);
		ft_close_fd(&p->fds[2 * i + 1]);
		i++;
	}
	ft_close_fd(&p->f_input);
	ft_close_fd(&p->f_output);
}
