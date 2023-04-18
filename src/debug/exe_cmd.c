/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jre-gonz <jre-gonz@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 11:21:42 by jre-gonz          #+#    #+#             */
/*   Updated: 2023/04/18 21:37:48 by jre-gonz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "debug_minishell.h"

#define STDIN 0
#define STDOUT 1

/**
 * @brief Set's the given file descriptors as stdin and stdout.
 * Closes the given file descriptors.
 *
 * Note: Both fd_in and fd_out must be valid fds.
 * Note: dup2 is not checked because it can only fail if:
 * "If oldfd is not a valid file descriptor, then the call fails, and newfd is
 * not closed."
 *
 * @param fd_in File descriptor for stdin.
 * @param fd_out File descriptor for stdout.
 */
static void	ft_redirect_io(int *fd_in, int *fd_out)
{
	if (*fd_in != STDIN)
	{
		// ft_printf_fd(2, "redirecting stdin: %d -> %d\n", *fd_in, STDIN); // TODO debug
		dup2(*fd_in, STDIN);
		ft_close_fd(fd_in);
	}
	if (*fd_out != STDOUT)
	{
		// ft_printf_fd(2, "redirecting stdout: %d -> %d\n", *fd_out, STDOUT); // TODO debug
		dup2(*fd_out, STDOUT);
		ft_close_fd(fd_out);
	}
}

/**
 * @brief Executes the command in a child process.
 * @note The full list is needed to finish the execution in case of error.
 * 
 * @param cmd_lst List element with the command to execute.
 * @param full List with all the commands.
 * @return int INVALID if error, the pid of the child process otherwise.
 */
// TODO builtins
// ? ? builtin and args
int	ft_exe_cmd(t_cmd_lst *cmd_lst, t_cmd_lst *full)
{
	int		pid;
	t_cmd	*cmd;

	pid = fork();
	if (pid)
		return (pid);
	cmd = get_cmd(cmd_lst);
	if (!ft_open_all_files(cmd))
		return (INVALID * 2); // TODO refactor INVALID logic
	// TODO check path
	// ? no command given
	if (ft_join_input(cmd) == INVALID)
		return (INVALID * 2);
	ft_redirect_io(&cmd->fd_in, &get_file(cmd->out)->fd);
	ft_close_all_fds(full);
	ft_printf_fd(2, "******************* Executing *******************\n");
	execve(cmd->cmd, cmd->args, NULL);
	ft_printf_fd(2, "Error executing execve!\n"); // TODO
	return (INVALID * 2);
}
