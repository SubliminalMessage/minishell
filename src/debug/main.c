/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jre-gonz <jre-gonz@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 09:19:19 by jre-gonz          #+#    #+#             */
/*   Updated: 2023/03/26 22:57:42 by jre-gonz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "debug_minishell.h"

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

int	ft_add_pipes(t_cmd_lst *cmd, int *fds)
{
	int			i;
	int			cmd_amount;
	t_cmd_lst	*new;
	t_cmd_lst	*tmp;

	i = 0;
	cmd_amount = ft_lstsize(cmd);
	tmp = cmd;
	while (i < cmd_amount - 1)
	{
		new = ft_lstnew(ft_newpipefd(fds[i * 2 + 1]));
		if (!new)
			return (free(fds), INVALID);
		ft_lstadd_back(&get_cmd(tmp)->out, new);

		new = ft_lstnew(ft_newpipefd(fds[i * 2]));
		if (!new)
			return (free(fds), INVALID);
		ft_lstadd_back(&get_cmd(tmp->next)->in, new);
		tmp = tmp->next;
		i++;
	}
	return (free(fds), i);
}

/**
 * @brief If no output file is specified, stdout should be used.
 * @note The case of stdin does not need to be checked.
 * 
 * @param cmd Structure containing the command.
 * @return int false if error, true otherwise.
 */
t_bool	ft_check_output(t_cmd_lst *cmd)
{
	t_cmd		*last_cmd;
	t_file_lst	*new_fd;

	last_cmd = get_cmd(ft_lstlast(cmd));
	if (ft_lstsize(last_cmd->out) > 0)
		return (true);
	new_fd = ft_lstnew(ft_newpipefd(STDOUT));
	if (!new_fd)
		return (false);
	get_file(new_fd)->type = STD_FTYPE;
	ft_lstadd_back(&last_cmd->out, new_fd);
	return (true);
}

// cat Makefile| wc < Makefile -l
// abc < fjaskldfjla << end < aaaaa | < noexists abc > output | cat > end
// < Makefile cat | wc -l

t_cmd_lst *ft_create_cmd(void)
{
	t_cmd_lst	*cmd;
	t_cmd		*command;

	// for command in line:

	// get command
	command = ft_calloc(1, sizeof(t_cmd));
	if (!command)
		return (NULL);
	command->fd_in = INVALID;
	command->args = ft_split("cat", ' ');
	command->cmd = ft_strjoin("/bin/", command->args[0]); // TODO should be done later
	if (!command->cmd || !command->args)
		return (ft_free_cmd(command), NULL);
	cmd = ft_lstnew(command);
	if (!cmd)
		return (ft_free_cmd(command), NULL);

	command = ft_calloc(1, sizeof(t_cmd));
	if (!command)
		return (ft_free_cmd_lst(cmd), NULL);
	command->fd_in = INVALID;
	command->args = ft_split("wc -l", ' ');
	command->cmd = ft_strjoin("/usr/bin/", command->args[0]); // TODO should be done later
	if (!command->cmd || !command->args)
		return (ft_free_cmd(command), ft_free_cmd_lst(cmd), NULL);
	ft_lstadd_back(&cmd, ft_lstnew(command));
	if (ft_lstsize(cmd) == 1)
		return (ft_free_cmd(command), ft_free_cmd_lst(cmd), NULL);

	// get input files
	// ? here doc
	command = get_cmd(cmd);
	command->in = ft_lstnew(ft_newfile(ft_strdup("pepe"), READ_FTYPE)); // TODO leaks
	if (!command->in || !get_file(command->in))
	{
		ft_free_cmd_lst(cmd);
		return (NULL);
	}
	command->fd_in = INVALID;

	// get output files
	// ? append

	// --------------------
	// TODOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO
	// command = get_cmd(cmd);
	// ft_openfile(get_file(command->in));

	// --------------------
	int	*fds = ft_create_pipes(ft_lstsize(cmd));
	if (!fds || ft_add_pipes(cmd, fds) == INVALID)
		return (ft_free_cmd_lst(cmd), NULL);
	if (ft_check_output(cmd) == false)
		return (ft_free_cmd_lst(cmd), NULL);
	return (cmd);
}

// ************************** Execution

//int	main(int argc, char **argv, char **envp)
int	main(void)
{
	int			result;
	t_cmd_lst	*cmd;

	cmd = ft_create_cmd();
	result = run(cmd);
	ft_putendl_fd("Execution ended", 1);
	ft_printf("Result: %i\n", result);
	return (result);
}
