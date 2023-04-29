/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jre-gonz <jre-gonz@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 11:21:42 by jre-gonz          #+#    #+#             */
/*   Updated: 2023/04/29 21:37:31 by jre-gonz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

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
		dup2(*fd_in, STDIN);
		ft_close_fd(fd_in);
	}
	if (*fd_out != STDOUT)
	{
		dup2(*fd_out, STDOUT);
		ft_close_fd(fd_out);
	}
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
 * @brief Creates a path to the given command. It concatenates following:
 * 
 * String.format("%s/%s", path, cmd)
 * 
 * @param path The path to concatenate.
 * @param cmd The command to concatenate.
 * @return char* The path to the command.
 */
char	*ft_make_path(char *path, char *cmd)
{
	int		path_len;
	int		cmd_len;
	char	*str;

	if (!path || !cmd)
		return (NULL);
	path_len = ft_strlen(path);
	cmd_len = ft_strlen(cmd);
	str = (char *) ft_calloc(sizeof(char), path_len + cmd_len + 2);
	if (!str)
		return (NULL);
	ft_strlcpy(str, path, path_len + 1);
	ft_strlcpy(str + path_len, "/", 2);
	ft_strlcpy(str + path_len + 1, cmd, cmd_len + 1);
	return (str);
}

t_bool	ft_get_path(t_cmd *cmd, t_env_lst *envp)
{ // TODO check is not a dir
	char	**path;
	char	*path_cmd;
	int		i;

	if (access(cmd->cmd, X_OK) == 0) // TODO fix: "minishell"
		return (true);
	path = ft_split(ft_getenv(envp, "PATH"), ':');
	if (!path)
		return (false);
	i = 0;
	while (path[i])
	{
		path_cmd = ft_make_path(path[i], cmd->cmd);
		if (!path_cmd)
			return (ft_free_array(path), false);
		if (access(path_cmd, X_OK) == 0)
		{
			free(cmd->cmd);
			cmd->cmd = path_cmd;
			return (ft_free_array(path), true);
		}
		free(path_cmd);
		i++;
	}
	return (ft_free_array(path), false);
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

	pid = fork();
	if (pid)
		return (pid);
	cmd = get_cmd(cmd_lst);
	if (!ft_open_all_files(cmd) || ft_join_input(cmd) == INVALID)
		return (ft_error_in_cmd(cmd_lst, full));
	ft_redirect_io(&cmd->fd_in, &get_file(cmd->out)->fd);
	ft_close_all_fds(full);
	ft_builtins(cmd, full);

	if (!ft_get_path(cmd, envp))
	{
		// TODO handle cmd not found
		ft_printf_fd(2, "cmd: %s\n", cmd->cmd);
		exit(INVALID);
	}
	ft_printf_fd(2, "******************* Executing *******************\n");
	ft_printf_fd(2, "cmd: %s\n", cmd->cmd);
	char **envp_arr = build_envp(envp); // TODO malloc
	execve(cmd->cmd, cmd->args, envp_arr);
	ft_free_array(envp_arr);
	ft_printf_fd(2, "Error executing execve!\n"); // TODO
	return (exit(INVALID), INVALID); // TODO error code?
}
