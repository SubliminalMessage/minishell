/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jre-gonz <jre-gonz@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 12:42:48 by jre-gonz          #+#    #+#             */
/*   Updated: 2023/03/24 12:46:59 by jre-gonz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "debug_minishell.h"

/**
 * @brief Closes all the file descriptors and frees the cmd_lst.
 * 
 * @param cmd List of commands.
 */
static void	close_fds_free(t_cmd_lst *cmd)
{
	ft_close_all_fds(cmd);
	ft_free_cmd_lst(cmd);
}

/**
 * @brief Runs the command given by the list.
 * TODO error code?
 * 
 * @param cmd List of commands.
 * @return int INVALID if error, the exit code of the last command otherwise.
 */
int	run(t_cmd_lst *cmd)
{
	int			i;
	t_cmd_lst	*ite;
	pid_t		*pids;

	atexit(exit_checks); // TODO debug
	if (!cmd)
		return (INVALID);
	i = 0;
	pids = ft_calloc(sizeof(pid_t) , 2 + 1);
	if (!pids)
		return (close_fds_free(cmd), INVALID);
	ite = cmd;
	while (ite)
	{
		pids[i++] = ft_exe_cmd(ite, cmd);
		ite = ite->next;
	}
	return (close_fds_free(cmd), ft_wait_result(pids));
}