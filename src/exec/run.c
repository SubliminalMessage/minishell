/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonza <dangonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 12:42:48 by jre-gonz          #+#    #+#             */
/*   Updated: 2023/05/31 21:27:07 by dangonza         ###   ########.fr       */
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

static void ft_store_result_code(int result_code)
{
	g_status_code = result_code;
}

/**
 * @brief Runs the command given by the list.
 * 
 * @param cmd List of commands.
 * @param envp List of environment variables.
 * @return int INVALID if error, the exit code of the last command otherwise.
 */
void	run(t_cmd_lst *cmd, t_env_lst **envp)
{
	int			i;
	t_cmd_lst	*ite;
	pid_t		*pids;

	if (!cmd)
		return ;
	if (!ft_add_pipes(cmd))
		close_free_exit(cmd, INVALID);
	if (ft_lstsize(cmd) == 1 && ft_strcmp(get_cmd(cmd)->cmd, "exit") == 0)
		close_free_exit(cmd, ft_exit(get_cmd(cmd)));
	if (ft_lstsize(cmd) == 1)
		execute_write_builtin(get_cmd(cmd), envp);
	i = 0;
	pids = ft_calloc(sizeof(pid_t), ft_lstsize(cmd) + 1); // TODO
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
	close_fds_free(cmd);
	ft_store_result_code(ft_wait_result(pids));
}
