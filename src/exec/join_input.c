/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jre-gonz <jre-gonz@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 11:25:53 by jre-gonz          #+#    #+#             */
/*   Updated: 2023/04/19 22:50:55 by jre-gonz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/**
 * @brief Joins all the input files into a pipe.
 * 
 * @param cmd The command with the input files to join.
 * @return int INVALID if an error occurs, the read end of the pipe otherwise.
 */
int	ft_join_input(t_cmd	*cmd)
{
	int			pipe_fds[2];
	t_file_lst	*file_lst;

	if (pipe(pipe_fds) == INVALID)
		return (INVALID);
	cmd->fd_in = pipe_fds[0];
	file_lst = cmd->in;
	while (file_lst)
	{
		if (ft_copyall(get_file(file_lst)->fd, pipe_fds[1]) == INVALID)
			return (ft_close_fd(&pipe_fds[1]), INVALID);
		ft_close_fd(&get_file(file_lst)->fd);
		file_lst = file_lst->next;
	}
	return (ft_close_fd(&pipe_fds[1]), pipe_fds[0]);
}
