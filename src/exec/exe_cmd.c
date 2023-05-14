/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jre-gonz <jre-gonz@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 11:21:42 by jre-gonz          #+#    #+#             */
/*   Updated: 2023/05/10 23:15:05 by jre-gonz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

#define STDIN 0
#define STDOUT 1

/**
 * @brief Redirects the given file descriptors with dup2. Closes the fd
 * once it's setup on the new fd.
 * 
 * @note - Both fds must be valid.
 * @note - dup2 is not checked because it can only fail if:
 * "If oldfd is not a valid file descriptor, then the call fails, and newfd is
 * not closed."
 * @note - The fds must be different. If not, this function will do nothing.
 * In this project, this condition is always met.
 * 
 * @param fd_new The new file descriptor to use.
 * @param fd_old The old file descriptor to close (example: STDIN)
 */
static void ft_redirect(int *fd_new, int fd_old)
{
	if (*fd_new != fd_old)
	{
		dup2(*fd_new, fd_old);
		ft_close_fd(fd_new);
	}
}

/**
 * @brief Set the appropriate file descriptors as stdin and stdout to execute
 * the given command.
 * 
 * @note Keep in mind that the redirect will only be done if needed.
 * 
 * @param cmd The command to execute.
 */
static void	ft_redirect_io(t_cmd *cmd)
{
	if (cmd->in)
		ft_redirect(&get_file(ft_lstlast(cmd->in))->fd, STDIN);
	if (cmd->out)
		ft_redirect(&get_file(ft_lstlast(cmd->out))->fd, STDOUT);
}

/**
 * @brief Handles when the command could not be set up correctly.
 * 
 * @note This command ends the execution of the calling process.
 * The function returns a value so it can be used in a return statement,
 * making the code more readable.
 * 
 * @note sends EOF to the pipe / output fd
 * 
 * @param cmd_lst current command.
 * @param full full list of commands.
 * @return int INVALID.
 */
static int	ft_error_in_cmd(t_cmd_lst *cmd_lst, t_cmd_lst *full)
{
	write(get_file(ft_lstlast(get_cmd(cmd_lst)->out))->fd, "", 1);
	ft_close_all_fds(full);
	ft_free_cmd_lst(full);
	return (exit(INVALID), INVALID);
}

/**
 * @brief Executes the command in a child process.
 * @note The full list is needed to finish the execution in case of error.
 * 
 * @param cmd_lst List element with the command to execute.
 * @param full List with all the commands.
 * @param envp List with the environment variables.
 * @return int INVALID if error, the pid of the child process otherwise.
 */
int	ft_exe_cmd(t_cmd_lst *cmd_lst, t_cmd_lst *full, t_env_lst *envp)
{
	int		pid;
	t_cmd	*cmd;
	char	**envp_arr;

	pid = fork();
	if (pid)
		return (pid);
	cmd = get_cmd(cmd_lst);
	envp_arr = build_envp(envp);
	if (!cmd->cmd || !cmd->args || !envp_arr || !ft_open_all_files(cmd))
		return (ft_error_in_cmd(cmd_lst, full));
	ft_redirect_io(cmd);
	ft_close_all_fds(full);
	ft_builtins(cmd, full);
	if (!ft_get_path(cmd, envp))
		return (ft_free_cmd_lst(full), exit(INVALID), INVALID);
	execve(cmd->cmd, cmd->args, envp_arr);
	ft_free_array(envp_arr);
	return (exit(INVALID), INVALID); // TODO error code?
}
