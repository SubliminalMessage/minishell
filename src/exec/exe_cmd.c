/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jre-gonz <jre-gonz@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 11:21:42 by jre-gonz          #+#    #+#             */
/*   Updated: 2023/04/28 17:01:19 by jre-gonz         ###   ########.fr       */
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

int	ft_echo(t_cmd *cmd)
{
	int	i;
	t_bool	n;

	i = 1;
	n = true;
	if (cmd->args[i] && ft_strcmp(cmd->args[i], "-n") == 0)
	{
		n = false;
		i++;
	}
	while (cmd->args[i])
	{
		ft_putstr_fd(cmd->args[i], STDOUT);
		if (cmd->args[i + 1])
			ft_putchar_fd(' ', STDOUT);
		i++;
	}
	if (n)
		ft_putchar_fd('\n', STDOUT);
	return (0);
}

int ft_exit(t_cmd *cmd)
{
	int	exit_code;

	// TODO if no pipes, FULL exit
	exit_code = 0;
	if (!cmd->args[1])
		exit_code = 0;
	else if (cmd->args[1] && !cmd->args[2])
	{
		exit_code = 2;
		if (ft_isnbr(cmd->args[1]))
			exit_code = (int) ((char) ft_atoi(cmd->args[1]));
		else
			ft_printf_fd(2, "exit: %s: numeric argument required\n", cmd->args[1]); // TODO refactor msg. perror?
	}
	else
	{
		ft_printf_fd(2, "exit: too many arguments\n"); // TODO refactor. perror?
		exit_code = 1;
	}
	return (exit_code);
}

int ft_handle_specials(t_cmd *cmd, t_cmd_lst *full)
{
	int	exit_code;

	exit_code = 0;
	if (cmd->cmd == NULL)
		ft_copyall(STDIN, STDOUT);
	else if (ft_strncmp(cmd->cmd, "echo", 4) == 0)
		exit_code = ft_echo(cmd);
	else if (ft_strcmp(cmd->cmd, "exit") == 0)
		exit_code = ft_exit(cmd);
	// else if (ft_strcmp(cmd->cmd, "cd") == 0)
	// 	exit_code = ft_cd(cmd);
	// else if (ft_strcmp(cmd->cmd, "pwd") == 0)
	// 	exit_code = ft_pwd(cmd);
	// else if (ft_strcmp(cmd->cmd, "export") == 0)
	// 	exit_code = ft_export(cmd);
	// else if (ft_strcmp(cmd->cmd, "unset") == 0)
	// 	exit_code = ft_unset(cmd);
	// else if (ft_strcmp(cmd->cmd, "env") == 0)
	// 	exit_code = ft_env(cmd);
	else
		return (0);
	ft_free_cmd_lst(full);
	exit(exit_code);
	return (INVALID);
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
	if (ft_join_input(cmd) == INVALID)
		return (INVALID * 2);
	ft_redirect_io(&cmd->fd_in, &get_file(cmd->out)->fd);
	ft_close_all_fds(full);
	if (ft_handle_specials(cmd, full) == INVALID)
		return (INVALID * 4);
	// TODO check path with env
	// ? no command given
	ft_printf_fd(2, "******************* Executing *******************\n");
	//char **envp = build_envp(envp);
	execve(cmd->cmd, cmd->args, NULL); // NULL -> envp tol royo
	//free_array_double(envp)
	ft_printf_fd(2, "Error executing execve!\n"); // TODO
	return (INVALID * 2);
}
