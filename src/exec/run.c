/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jre-gonz <jre-gonz@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 12:42:48 by jre-gonz          #+#    #+#             */
/*   Updated: 2023/05/01 14:43:36 by jre-gonz         ###   ########.fr       */
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

static void	close_free_exit(t_cmd_lst *cmd, int exit_code)
{
	close_fds_free(cmd);
	exit(exit_code);
}

static void	kill_all_children(pid_t *pids)
{
	int	i;

	i = 0;
	while (pids[i])
		kill(pids[i++], SIGKILL);
	free(pids);
}

/**
 * @brief Runs the command given by the list.
 * TODO check what is needed to handle $?
 * 
 * @param cmd List of commands.
 * @param envp List of environment variables.
 * @return int INVALID if error, the exit code of the last command otherwise.
 */
void	run(t_cmd_lst *cmd, t_env_lst *envp)
{
	int			i;
	t_cmd_lst	*ite;
	pid_t		*pids;

	if (!cmd)
		return ;
	if (ft_lstsize(cmd) == 1 && ft_strcmp(get_cmd(cmd)->cmd, "exit") == 0)
		close_free_exit(cmd, ft_exit(get_cmd(cmd)));
	i = 0;
	pids = ft_calloc(sizeof(pid_t) , 2 + 1);
	if (!pids)
		close_free_exit(cmd, INVALID);
	ite = cmd;
	while (ite)
	{
		pids[i] = ft_exe_cmd(ite, cmd, envp);
		if (pids[i] == INVALID) // Fork error
		{
			kill_all_children(pids);
			close_free_exit(cmd, INVALID);
		}
		++i;
		ite = ite->next;
	}
	// return (close_fds_free(cmd), ft_wait_result(pids));
	close_fds_free(cmd);
	// TODO store exit code in envp
	i = ft_wait_result(pids);
	printf("run finished. Result code: %d\n", i);
}
