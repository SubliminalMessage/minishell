/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jre-gonz <jre-gonz@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 09:19:19 by jre-gonz          #+#    #+#             */
/*   Updated: 2023/01/23 12:27:34 by jre-gonz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "debug_minishell.h"

t_file	*ft_newfile(char *file, t_ftype type, int opentype)
{
	t_file	*f;

	f = ft_calloc(1, sizeof(t_file));
	if (!f)
		return (NULL);
	f->name = file;
	f->type = type;
	f->fd = open(file, opentype);
	if (f->fd == -1)
	{
		ft_free_file(f);
		return (NULL);
	}
	return (f);
}

t_file	*openfile(char *file)
{
	return (ft_newfile(file, READ, O_RDONLY));
}

t_file	*ft_newpipefd(int fd)
{
	t_file	*f;

	f = ft_calloc(1, sizeof(t_file));
	if (!f)
		return (NULL);
	// name is NULL with calloc
	f->type = PIPE;
	f->fd = fd;
	return (f);
}

// < Makefile cat | wc -l
t_cmd_lst	*ft_cmd1()
{
	t_cmd_lst	*cmd;
	t_cmd		*command;

	command = ft_calloc(1, sizeof(t_cmd));
	if (!command)
		return (NULL);
	command->cmd = ft_strdup("/bin/cat"); // TODO malloc error
	
	cmd = ft_lstnew(command);
	if (!cmd)
	{
		ft_free_cmd(command);
		return (NULL);
	}

	t_file *makef = openfile(ft_strdup("Makefile")); // TODO Malloc error
	command->in = ft_lstnew(makef);

	command = ft_calloc(1, sizeof(t_cmd));
	if (!command)
	{
		ft_free_cmd_lst(cmd);
		return (NULL);
	}
	command->cmd = ft_strdup("/bin/wc"); // TODO malloc error
	command->args = ft_split("wc -l", ' '); // TODO malloc error
	ft_lstadd_back(&cmd, ft_lstnew(command));

	// ****************************************

	int	*fds = ft_calloc((2 - 1) * 2, sizeof(int));
	int	i = 0;
	while (i < 2 - 1)
	{
		pipe(&(fds[2 * i]));
		// if (pipe(&(fds[2 * i])) != 0)
			// TODO
		i++;
	}

	t_cmd_lst *new;
	t_cmd_lst *tmp = cmd;
	i = 0;
	while (i < 2 - 1)
	{
		new = ft_lstnew(ft_newpipefd(fds[i * 2]));
		// TODO malloc error
		ft_lstadd_back(&get_cmd(tmp)->out, new);
		new = ft_lstnew(ft_newpipefd(fds[i * 2 + 1]));
		// TODO malloc error
		ft_lstadd_back(&get_cmd(tmp->next)->in, new);
		tmp = tmp->next;
		i++;
	}
	free(fds); // The array is no longer needed
	// stdin?

	new = ft_lstnew(ft_newpipefd(1));
	// TODO malloc error
	ft_lstadd_back(&get_cmd(tmp)->out, new);

	return (cmd);
}

// ************************** Execution
int	ft_exe_cmd(t_cmd_lst	*cmd, t_cmd_lst *full)
{ // TODO Is there a better way?
	int	pid;

	pid = fork();
	if (pid)
		return (pid);
	cmd++;
	// TODO redirect pipes
	// TODO close pipes
	// TODO exec
	ft_free_cmd_lst(full);
	exit(2);
	return (-1);
}

int	main(void)
{
	t_cmd_lst	*cmd;

	cmd = ft_cmd1();
	if (!cmd)
		return (1);
	ft_putendl_fd("Executing...", 1);
	int	pid1 = ft_exe_cmd(cmd, cmd);
	int	pid2 = ft_exe_cmd(cmd->next, cmd);
	// TODO Close pids
	
	int result;
	waitpid(pid1, NULL, 0);
	waitpid(pid2, &result, 0); // TODO get correct result
	ft_putendl_fd("Execution ended", 1);
	ft_printf("Result: %i\n", result);
	ft_free_cmd_lst(cmd);
	return (result);
}
