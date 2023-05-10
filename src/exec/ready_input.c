/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ready_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jre-gonz <jre-gonz@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 11:25:53 by jre-gonz          #+#    #+#             */
/*   Updated: 2023/05/10 22:27:33 by jre-gonz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
// TODO Remove file if really not needed

/**
 * @brief Makes the input ready for the command.
 * Joins all the input files into a pipe.
 * 
 * @param cmd The command with the input files to join.
 * @return int false if an error occurs, true otherwise.
 */
static t_bool	ft_join_input(t_cmd *cmd)
{
	int			pipe_fds[2];
	t_file_lst	*file_lst;

	if (pipe(pipe_fds) == INVALID)
		return (false);
	cmd->fd_in = pipe_fds[0];
	file_lst = cmd->in;
	while (file_lst)
	{
		if (ft_copyall(get_file(file_lst)->fd, pipe_fds[1]) == INVALID)
			return (ft_close_fd(&pipe_fds[1]), false);
		ft_close_fd(&get_file(file_lst)->fd);
		file_lst = file_lst->next;
	}
	ft_close_fd(&pipe_fds[1]);
	return (true);
}

static int	ft_fd_dup(t_cmd *cmd)
{
	int	pipe_fds[2];
	t_file	*f;

	f = get_file(ft_lstlast(cmd->in));
	if (pipe(pipe_fds) == INVALID)
		return (INVALID);
	if (ft_copyall(f->fd, pipe_fds[1]) == INVALID)
		return (ft_close_fd(&pipe_fds[0]), ft_close_fd(&pipe_fds[1]), INVALID);
	ft_close_fd(&pipe_fds[1]);
	return (pipe_fds[0]);
}


t_bool	ft_ready_input(t_cmd *cmd)
{
	t_file	*f;

	if (!ft_open_all_files(cmd))
		return (false);
	f = get_file(cmd->in);
	if (!f || f->type != PIPE_FTYPE)
		return (ft_join_input(cmd));
	cmd->fd_in = ft_fd_dup(cmd);
	return (cmd->fd_in != INVALID);
}
