/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jre-gonz <jre-gonz@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 10:07:27 by jre-gonz          #+#    #+#             */
/*   Updated: 2023/01/21 18:40:44 by jre-gonz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "debug_minishell.h"

void	ft_free_file(t_file *file)
{
	if (!file)
		return ;
	if (file->name)
		free(file->name);
	if (file->fd != -1)
		close(file->fd);
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
	if (cmd->args)
		ft_free_array(cmd->args);
	free(cmd);
}

void	ft_free_cmd_lst(t_cmd_lst *cmd)
{
	ft_lstclear((t_list**) &cmd, (void (*)(void *)) ft_free_cmd);
}
