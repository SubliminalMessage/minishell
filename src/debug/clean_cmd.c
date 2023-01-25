/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jre-gonz <jre-gonz@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 10:07:27 by jre-gonz          #+#    #+#             */
/*   Updated: 2023/01/25 16:19:47 by jre-gonz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "debug_minishell.h"

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
	*fd = -1;
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

void	ft_free_cmd(t_cmd *cmd)
{
	if (!cmd)
		return ;
	if (cmd->cmd)
		free(cmd->cmd);
	if (cmd->in)
		ft_lstclear((t_list**) &cmd->in, (void (*)(void *)) ft_free_file);
	if (cmd->out)
		ft_lstclear((t_list**) &cmd->out, (void (*)(void *)) ft_free_file);
	if (cmd->args)
		ft_free_array(cmd->args);
	free(cmd);
}

void	ft_free_cmd_lst(t_cmd_lst *cmd)
{
	ft_lstclear((t_list**) &cmd, (void (*)(void *)) ft_free_cmd);
}
