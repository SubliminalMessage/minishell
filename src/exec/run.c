/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jre-gonz <jre-gonz@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 12:42:48 by jre-gonz          #+#    #+#             */
/*   Updated: 2023/04/29 20:11:59 by jre-gonz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

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
 * @param envp List of environment variables.
 * @return int INVALID if error, the exit code of the last command otherwise.
 */
int	run(t_cmd_lst *cmd, t_env_lst *envp)
{
	int			i;
	t_cmd_lst	*ite;
	pid_t		*pids;

	if (!cmd)
		return (INVALID);
	if (ft_lstsize(cmd) == 1 && ft_strcmp(get_cmd(cmd)->cmd, "exit") == 0)
		return (close_fds_free(cmd), exit(ft_exit(get_cmd(cmd))), 0);
	i = 0;
	pids = ft_calloc(sizeof(pid_t) , 2 + 1);
	if (!pids)
		return (close_fds_free(cmd), INVALID);
	ite = cmd;
	while (ite)
	{
		pids[i] = ft_exe_cmd(ite, cmd, envp);
		if (pids[i] == INVALID) // Fork error
		{
			ft_printf_fd(2, "\nError: fork failed.\n"); // TODO debug
			// TODO ? kill all children
			return (close_fds_free(cmd), exit(INVALID), INVALID);
		}
		++i;
		ite = ite->next;
	}
	return (close_fds_free(cmd), ft_wait_result(pids));
}
