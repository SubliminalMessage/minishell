/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jre-gonz <jre-gonz@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 22:41:41 by jre-gonz          #+#    #+#             */
/*   Updated: 2023/05/01 21:48:36 by jre-gonz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/**
 * @brief Creates the pipes needed for the commands.
 * 
 * @param amount_cmds Amount of commands.
 * @return int* Array of pipes (read, write, read...) or NULL if error.
 */
static int	*ft_create_pipes(int amount_cmds)
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
		i += 2;
	}
	return (fds);
}

/**
 * @brief Links the commands with the given pipes.
 * 
 * @param cmd Command list.
 * @return t_bool false if error, true otherwise.
 */
t_bool	ft_add_pipes(t_cmd_lst *cmd)
{
	int			i;
	int			cmd_amount;
	int			*pipes;
	t_cmd_lst	*new;
	t_cmd_lst	*tmp;


	i = 0;
	cmd_amount = ft_lstsize(cmd);
	pipes = ft_create_pipes(cmd_amount);
	if (!pipes)
		return (false);
	tmp = cmd;
	while (i < cmd_amount - 1)
	{
		new = ft_lstnew(ft_newpipefd(pipes[i * 2 + 1]));
		if (!new)
			return (free(pipes), false);
		ft_lstadd_back(&get_cmd(tmp)->out, new);

		new = ft_lstnew(ft_newpipefd(pipes[i * 2]));
		if (!new)
			return (free(pipes), false);
		// ft_lstadd_back(&get_cmd(tmp->next)->in, new);
		ft_lstadd_front(&get_cmd(tmp->next)->in, new);
		tmp = tmp->next;
		i++;
	}
	return (free(pipes), true);
}
