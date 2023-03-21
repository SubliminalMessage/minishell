/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jre-gonz <jre-gonz@student.42madrid.com>   +#+  +:+       +#+        */
/*   main.c                                               ||           ||     */
/*   Created: 2023/01/19 09:19:19 by jre-gonz          #+#    #+#             */
/*   Updated: 2023/03/21 08:08:21 by jre-gonz         ###   ########.fr       */
/*   Updated: 2023/03/08 20:32:18 by jre-gonz         ###   ########.fr       */
/*   Updated: 2023/03/08 20:17:33 by jre-gonz         ###   ########.fr       */
/*   Updated: 2023/03/21 08:08:21 by Jkutkut            '-----------------'   */
/*   Updated: 2023/03/08 20:32:18 by jre-gonz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "debug_minishell.h"

// < Makefile cat | wc -l
t_cmd_lst	*ft_cmd1()
{
	t_cmd_lst	*cmd;
	t_cmd		*command;

	command = ft_calloc(1, sizeof(t_cmd));
	if (!command)
		return (NULL);
	command->cmd = ft_strdup("/bin/cat");
	command->args = ft_split("cat", ' ');
	if (!command->cmd || !command->args)
	{
		ft_free_cmd(command);
		return (NULL);
	}

	cmd = ft_lstnew(command);
	if (!cmd)
	{
		ft_free_cmd(command);
		return (NULL);
	}

	command->in = ft_lstnew(openfile(ft_strdup("Makefile")));
	if (!command->in || !get_file(command->in))
	{
		ft_free_cmd_lst(cmd);
		return (NULL);
	}
	ft_printf("makefile file: %d, type: %d\n",
		get_file(command->in)->fd, get_file(command->in)->type
	);

	command = ft_calloc(1, sizeof(t_cmd));
	if (!command)
	{
		ft_free_cmd_lst(cmd);
		return (NULL);
	}
	command->cmd = ft_strdup("/bin/wc");
	command->args = ft_split("wc -l", ' ');
	if (!command->cmd || !command->args)
	{
		ft_free_cmd(command);
		ft_free_cmd_lst(cmd);
		return (NULL);
	}
	ft_lstadd_back(&cmd, ft_lstnew(command));
	if (ft_lstsize(cmd) == 1)
	{
		ft_free_cmd(command);
		ft_free_cmd_lst(cmd);
		return (NULL);
	}

	// ****************************************
	// TODO continue protection
	int	*fds = ft_calloc((2 - 1) * 2, sizeof(int));
	int	i = 0;
	while (i < 2 - 1)
	{
		pipe(&(fds[2 * i]));
		// if (pipe(&(fds[2 * i])) != 0)
			// TODO
		ft_printf_fd(2, "pipe between cmds: %d, %d\n", fds[0], fds[1]);
		i++;
	}

	t_cmd_lst *new;
	t_cmd_lst *tmp = cmd;
	i = 0;
	while (i < 2 - 1)
	{
		new = ft_lstnew(ft_newpipefd(fds[i * 2 + 1]));
		// TODO malloc error
		ft_lstadd_back(&get_cmd(tmp)->out, new);

		new = ft_lstnew(ft_newpipefd(fds[i * 2]));
		// TODO malloc error
		ft_lstadd_back(&get_cmd(tmp->next)->in, new);
		tmp = tmp->next;
		i++;
	}
	free(fds); // The array is no longer needed
	// stdin?
	command->fd_in = -1; // INVALID
	new = ft_lstnew(ft_newpipefd(1));
	// TODO malloc error
	get_file(new)->type = TRUNC_FTYPE;
	ft_lstadd_back(&get_cmd(tmp)->out, new);

	return (cmd);
}

// ************************** Execution
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
void	ft_redirect_io(int *fd_in, int *fd_out)
{
	if (*fd_in != STDIN)
	{
		ft_printf_fd(2, "redirecting stdin: %d -> %d\n", *fd_in, STDIN);
		dup2(*fd_in, STDIN);
		ft_close_fd(fd_in);
	}
	if (*fd_out != STDOUT)
	{
		ft_printf_fd(2, "redirecting stdout: %d -> %d\n", *fd_out, STDOUT);
		dup2(*fd_out, STDOUT);
		ft_close_fd(fd_out);
	}
}

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 4098
#endif

static int	ft_copyall(int rfd, int wfd)
{
	int		r;
	int		total;
	char	buffer[BUFFER_SIZE];

	total = 0;
	while (1) // TODO use t_bool
	{
		r = read(rfd, buffer, BUFFER_SIZE);
		if (r == -1)
			break;
		write(wfd, buffer, r);
		total += r;
		if (r < BUFFER_SIZE)
			break;
	}
	return (total); // TODO check -1
}

int	ft_join_input(t_cmd	*cmd)
{
	int			pipe_fds[2];
	t_file_lst *file_lst;

	if (pipe(pipe_fds) == -1)
		return (-1);
	// ft_printf_fd(2, "Pipe executed: %d, %d\n", pipe_fds[0], pipe_fds[1]);
	cmd->fd_in = pipe_fds[0];
	// ft_printf_fd(2, "cmd->fd_in: %d\n", cmd->fd_in);
	file_lst = cmd->in;
	while (file_lst)
	{
		ft_copyall(get_file(file_lst)->fd, pipe_fds[1]); // TODO check error?
		ft_close_fd(&get_file(file_lst)->fd);
		file_lst = file_lst->next;
	}
	ft_close_fd(&pipe_fds[1]);
	return (pipe_fds[0]);
}

// void	ft_print_minishell(t_cmd_lst *command, int fd, int recursive)
// {
// 	t_cmd		*cmd;
// 	t_file_lst	*f;
// 
// 	cmd = get_cmd(command);
// 	ft_printf_fd(fd, "Cmd: '%s'\n", cmd->cmd);
// 	ft_printf_fd(fd, "fd_in: %d\n", cmd->fd_in);
// 	ft_printf_fd(fd, "In:\n");
// 	f = cmd->in;
// 	while (f)
// 	{
// 		ft_printf_fd(fd, "  - '%s' -> fd: %d, type: %d\n",
// 			   get_file(f)->name, get_file(f)->fd, get_file(f)->type);
// 		f = f->next;
// 	}
// 	ft_printf_fd(fd, "Out:\n");
// 	f = cmd->out;
// 	while (f)
// 	{
// 		ft_printf_fd(fd, "  - '%s' -> fd: %d, type: %d\n",
// 			   get_file(f)->name, get_file(f)->fd, get_file(f)->type);
// 		f = f->next;
// 	}
// 	ft_printf_fd(fd, "\n\n\n\n");
// 	if (command->next && recursive)
// 	 	ft_print_minishell(command->next, fd, recursive);
// }

int	ft_exe_cmd(t_cmd_lst	*cmd_lst, t_cmd_lst *full)
{ // TODO Is there a better way?
	int	pid;
	t_cmd	*cmd;

	pid = fork();
	if (pid)
		return (pid);
	ft_putendl_fd("Executing...", 1);
	cmd = get_cmd(cmd_lst);
	if (ft_join_input(cmd) == -1)
	{
		// TODO
		return (-1);
	}
	// ft_print_minishell(cmd_lst, 2, 0);
	ft_redirect_io(&cmd->fd_in, &get_file(cmd->out)->fd);
	ft_printf_fd(2, "******************* Executing *******************\n");
	execve(cmd->cmd, cmd->args, NULL);
	ft_free_cmd_lst(full);
	exit(2);
	return (-1);
}

//int	main(int argc, char **argv, char **envp)
int	main(void)
{
	t_cmd_lst	*cmd;

	cmd = ft_cmd1();
	if (!cmd)
		return (1);
	int i = 0;
	pid_t *pids = malloc(sizeof(pid_t) * 2); // TODO check malloc
	t_cmd_lst *ite = cmd;
	while (ite)
	{
		ft_printf("Executing %d\n", i);
		pids[i++] = ft_exe_cmd(ite, cmd);
		ite = ite->next;
	}
	// TODO Close pids
	
	int		result;
	int		status;
	pid_t	waited_pid;
	i = 0;
	while (i < 2) {
		ft_printf("Waiting for %d\n", i);
		waited_pid = waitpid(pids[i], &status, 0);
		if (pids[2 - 1] == waited_pid)
			result = status;
		i++;
	}
	ft_putendl_fd("Execution ended", 1);
	ft_printf("Result: %i\n", result);
	ft_free_cmd_lst(cmd);
	return (result);
}
