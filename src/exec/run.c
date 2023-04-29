/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jre-gonz <jre-gonz@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 12:42:48 by jre-gonz          #+#    #+#             */
/*   Updated: 2023/04/29 19:04:58 by jre-gonz         ###   ########.fr       */
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
	{
		i = ft_exit(get_cmd(cmd));
		close_fds_free(cmd);
		exit(i);
	}
	i = 0;
	pids = ft_calloc(sizeof(pid_t) , 2 + 1);
	if (!pids)
		return (close_fds_free(cmd), INVALID);
	ite = cmd;
	while (ite)
	{
		pids[i] = ft_exe_cmd(ite, cmd, envp);
		// TODO can fail with fork, execve or invalid command
		if (pids[i] == INVALID) // Fork error
		{
			ft_printf_fd(2, "\nError: fork failed.\n"); // TODO debug
			// TODO ? kill all children
			return (close_fds_free(cmd), exit(42), INVALID); // TODO error code
		}
		if (pids[i] == INVALID * 2) // Child with error
		{
			ft_printf_fd(2, "\nChild with error\n"); // TODO debug
			// send send EOF to the pipe
			write(get_file(ft_lstlast(get_cmd(ite)->out))->fd, "", 1); // TODO refactor?
			return (close_fds_free(cmd), exit(42), INVALID); // TODO error code
		}
		++i;
		ite = ite->next;
	}
	return (close_fds_free(cmd), ft_wait_result(pids));
}
