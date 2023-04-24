/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonza <dangonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 10:07:27 by jre-gonz          #+#    #+#             */
/*   Updated: 2023/04/24 19:07:57 by dangonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ft_free_array_content(char **arr)
{
	size_t	i;

	if (arr == NULL)
		return ;
	i = 0;
	while (arr[i] != NULL)
	{
		free(arr[i]);
		i++;
	}
}

void	ft_free_cmd(t_cmd *cmd)
{
	if (!cmd)
		return ;
	if (cmd->cmd)
		free(cmd->cmd);
	ft_close_fds(cmd);
	ft_free_array(cmd->args);
	free(cmd);
}

void	ft_close_all_fds(t_cmd_lst *cmd)
{
	ft_lstiter((t_list *) cmd, (void (*)(void *)) ft_close_fds);
}

void	ft_free_cmd_lst(t_cmd_lst *cmd)
{
	ft_lstclear((t_list **) &cmd, (void (*)(void *)) ft_free_cmd);
}
