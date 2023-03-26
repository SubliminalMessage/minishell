/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jre-gonz <jre-gonz@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 10:07:27 by jre-gonz          #+#    #+#             */
/*   Updated: 2023/03/26 16:21:30 by jre-gonz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "debug_minishell.h" // TODO use minishell

/**
 * @brief Closes the given fd. If null, nothing done.
 * If closed, the null value is assigned as a check.
 *
 * @param fd File descriptor.
 */
void	ft_close_fd(int *fd)
{
	if (*fd > 1)
		close(*fd);
	*fd = INVALID;
}

void	ft_free_file(t_file *file)
{
	if (!file)
		return ;
	if (file->name)
		free(file->name);
	ft_close_fd(&file->fd);
	free(file);
}

static void	ft_close_fds(t_cmd *cmd)
{
	if (!cmd)
		return ;
	ft_lstclear((t_list**) &cmd->in, (void (*)(void *)) ft_free_file);
	ft_lstclear((t_list**) &cmd->out, (void (*)(void *)) ft_free_file);
	ft_close_fd(&cmd->fd_in);
}

void	ft_free_cmd(t_cmd *cmd)
{
	if (!cmd)
		return ;
	if (cmd->cmd)
		free(cmd->cmd);
	ft_close_fds(cmd);
	ft_free_array(cmd->args);
	free(cmd);
}

void	ft_close_all_fds(t_cmd_lst *cmd)
{
	ft_lstiter((t_list*) cmd, (void (*)(void *)) ft_close_fds);
}

void	ft_free_cmd_lst(t_cmd_lst *cmd)
{
	ft_lstclear((t_list**) &cmd, (void (*)(void *)) ft_free_cmd);
}
