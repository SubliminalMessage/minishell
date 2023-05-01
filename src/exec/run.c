/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jre-gonz <jre-gonz@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 12:42:48 by jre-gonz          #+#    #+#             */
/*   Updated: 2023/05/01 18:13:00 by jre-gonz         ###   ########.fr       */
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

static void ft_store_result_code(int result_code, t_env_lst *envp)
{
	t_bool	updated;
	char	*result_code_str;

	result_code_str = ft_itoa(result_code);
	if (!result_code_str)
		exit(INVALID);
	updated = update_env(&envp, "?", result_code_str, false);
	free(result_code_str);
	if (!updated)
		exit(INVALID);
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
	if (!ft_add_pipes(cmd))
		close_free_exit(cmd, INVALID);
	if (ft_lstsize(cmd) == 1 && ft_strcmp(get_cmd(cmd)->cmd, "exit") == 0)
		close_free_exit(cmd, ft_exit(get_cmd(cmd)));
	i = 0;
	pids = ft_calloc(sizeof(pid_t), 2 + 1);
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
	ft_store_result_code(ft_wait_result(pids), envp);
}
