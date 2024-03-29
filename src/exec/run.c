/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jre-gonz <jre-gonz@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 12:42:48 by jre-gonz          #+#    #+#             */
/*   Updated: 2023/06/18 22:52:19 by jre-gonz         ###   ########.fr       */
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

/**
 * @brief Merge function of close_fds_free() and exit().
 * 
 * @param cmd List of commands.
 * @param exit_code Exit code to return.
 */
void	close_free_exit(t_cmd_lst *cmd, int exit_code)
{
	close_fds_free(cmd);
	exit(exit_code);
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

static int	*allocate_and_return(int **ptr, size_t size)
{
	*ptr = ft_calloc(size, sizeof(void *));
	return (*ptr);
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
	if (!allocate_and_return(&pids, sizeof(pid_t) * (ft_lstsize(cmd) + 1)))
		close_free_exit(cmd, INVALID);
	ite = cmd;
	while (ite)
	{
		pids[i] = ft_exe_cmd(ite, cmd, envp);
		signal(SIGINT, SIG_IGN);
		if (pids[i++] == INVALID)
			return (kill_all_children(pids), close_free_exit(cmd, INVALID));
		ite = ite->next;
	}
	close_fds_free(cmd);
	ft_store_result_code(ft_wait_result(pids), false);
}
