/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jre-gonz <jre-gonz@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 09:19:19 by jre-gonz          #+#    #+#             */
/*   Updated: 2023/03/25 23:17:47 by jre-gonz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "debug_minishell.h"

// < Makefile cat | wc -l
static t_cmd_lst	*ft_cmd1()
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
	command->fd_in = INVALID;

	command = ft_calloc(1, sizeof(t_cmd));
	if (!command)
	{
		ft_free_cmd_lst(cmd);
		return (NULL);
	}
	command->cmd = ft_strdup("/usr/bin/wc");
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
	command->fd_in = INVALID;

	// ****************************************
	return (cmd);
}

int	*ft_create_pipes(int amount_cmds)
{
	int	pipes_size;
	int	*fds;
	int	i;

	pipes_size = (amount_cmds - 1) * 2;
	fds = ft_calloc(pipes_size, sizeof(int));
	if (!fds)
		return (NULL);
	i = 0;
	while (i < pipes_size)
	{
		if (pipe(&(fds[i])) != 0)
		{
			while (--i >= 0)
				ft_close_fd(&fds[i]);
			free(fds);
			return (NULL);
		}
		ft_printf_fd(2, "pipe between cmds: %d, %d\n", fds[i], fds[i + 1]);
		i += 2;
	}
	return (fds);
}


t_cmd_lst *make_cmd(void)
{
	// for command in line:

	// get command
	// ? path
	// ? builtin
	// ? ? builtin and args

	// get input files
	// ? here doc

	// get output files
	// ? append

	t_cmd_lst	*cmd;
	cmd = ft_cmd1();

	// --------------------

	// if no input files, stdin
	// if no output files, stdout

	// pipes

	int	*fds = ft_create_pipes(ft_lstsize(cmd));
	if (!fds)
		return (ft_free_cmd_lst(cmd), NULL);

	t_cmd_lst *new;
	t_cmd_lst *tmp = cmd;
	int i = 0;
	while (i < 2 - 1)
	{
		new = ft_lstnew(ft_newpipefd(fds[i * 2 + 1]));
		if (!new)
		{
			i = INVALID;
			break;
		}
		ft_lstadd_back(&get_cmd(tmp)->out, new);

		new = ft_lstnew(ft_newpipefd(fds[i * 2]));
		if (!new)
		{
			i = INVALID;
			break;
		}
		ft_lstadd_back(&get_cmd(tmp->next)->in, new);
		tmp = tmp->next;
		i++;
	}
	free(fds); // The array is no longer needed
	if (i == INVALID)
	{
		ft_free_cmd_lst(cmd);
		return (NULL);
	}

	// TODO what if stdin needed?
	new = ft_lstnew(ft_newpipefd(1));
	if (!new)
	{
		ft_free_cmd_lst(cmd);
		return (NULL);
	}
	get_file(new)->type = STD;
	ft_lstadd_back(&get_cmd(tmp)->out, new);

	return (cmd);
}

// ************************** Execution

//int	main(int argc, char **argv, char **envp)
int	main(void)
{
	int			result;
	t_cmd_lst	*cmd;

	cmd = make_cmd();
	result = run(cmd);
	ft_putendl_fd("Execution ended", 1);
	ft_printf("Result: %i\n", result);
	return (result);
}
