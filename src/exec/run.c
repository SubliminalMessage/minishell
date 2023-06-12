/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonza <dangonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 12:42:48 by jre-gonz          #+#    #+#             */
/*   Updated: 2023/06/07 23:38:10 by dangonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/**
 * @brief Closes all the file descriptors and frees the cmd_lst.
 * 
 * @param cmd List of commands.
 */
void	close_fds_free(t_cmd_lst *cmd)
{
	ft_close_all_fds(cmd);
	ft_free_cmd_lst(cmd);
}

// TODO: Document this function
void	close_free_exit(t_cmd_lst *cmd, int exit_code)
{
	close_fds_free(cmd);
	exit(exit_code);
}

// TODO: Document this function
static void	kill_all_children(pid_t *pids)
{
	int	i;

/**
 * @brief Kills all the processes in the given array.
 * 
 * @param pids Array of pids to kill.
 */
	while (pids[i])
		kill(pids[i++], SIGKILL);
	free(pids);
}

/**
 * @brief Stores a result code into the global 'g_status_code'.
 * 
 * @note The result_code will only be stored if the previous code
 *       is exactly 0, or if the 'force' argument is true.
 * 
 * @param result_code, the code to store
 * @param force, whether the 'protection logic' must be ignored or not
*/
void ft_store_result_code(int result_code, t_bool force)
{
	if (g_status_code == 0 || force)
		g_status_code = result_code;
}

/**
 * @brief given a string of a command, returns if it is a Write-Builtin or not
 * 	
 * @note A Write-Builtin is one that Writes (modifies) the Environment List,
 *       and thus, can't be executed inside of a fork(). This builtins are:
 *       'exit', 'export', 'unset' and 'cd'.
 * 
 * @note 'exit' builtin does not write into the Env. List, but needs to run on
 *       the parent when executed alone. 
 * 
 * @param cmd, the String of the command
 * 
 * @return t_bool, whether it is a Write-Builin or not
*/
t_bool	is_write_builtin(char *cmd)
{
	if (str_equals(cmd, "exit"))
		return (true);
	if (str_equals(cmd, "export"))
		return (true);
	if (str_equals(cmd, "unset"))
		return (true);
	if (str_equals(cmd, "cd"))
		return (true);
	return (false);
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
	if (ft_lstsize(cmd) == 1 && is_write_builtin(get_cmd(cmd)->cmd))
		return (execute_write_builtin(cmd, envp));
	i = 0;
	pids = ft_calloc(sizeof(pid_t), ft_lstsize(cmd) + 1); // TODO
	if (!pids)
		close_free_exit(cmd, INVALID);
	ite = cmd;
	while (ite)
	{
		pids[i] = ft_exe_cmd(ite, cmd, envp);
		signal(SIGINT, SIG_IGN);
		if (pids[i] == INVALID) // Fork error
		{
			kill_all_children(pids);
			close_free_exit(cmd, INVALID);
		}
		++i;
		ite = ite->next;
	}
	close_fds_free(cmd);
	ft_store_result_code(ft_wait_result(pids), false);
}
