/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jre-gonz <jre-gonz@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 10:07:27 by jre-gonz          #+#    #+#             */
/*   Updated: 2023/06/12 18:20:49 by jre-gonz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/**
 * @brief Frees the given array of strings.
 * 
 * @param arr Array of strings to deallocate.
 */
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

/**
 * @brief Frees the given command structure.
 * 
 * @param cmd Command structure to deallocate.
 */
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

/**
 * @brief Closes all the file descriptors in the given command list.
 * 
 * @param cmd Linked list of commands.
 */
void	ft_close_all_fds(t_cmd_lst *cmd)
{
	ft_lstiter((t_list *) cmd, (void (*)(void *)) ft_close_fds);
}

/**
 * @brief Frees the given command list.
 * 
 * @param cmd Linked list of commands.
 */
void	ft_free_cmd_lst(t_cmd_lst *cmd)
{
	ft_lstclear((t_list **) &cmd, (void (*)(void *)) ft_free_cmd);
}
