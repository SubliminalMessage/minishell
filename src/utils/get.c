/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jre-gonz <jre-gonz@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 11:01:17 by jre-gonz          #+#    #+#             */
/*   Updated: 2023/03/26 16:24:25 by jre-gonz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "debug_minishell.h" // TODO Use minimishell.h

/**
 * @brief Get the content of the list.
 * 
 * @param lst the list element.
 * @return void* the content.
 */
static void	*get(t_list *lst)
{
	if (!lst)
		return (NULL);
	return (lst->content);
}

/**
 * @brief Get the file object from the list.
 * 
 * @param lst the list element.
 * @return t_file* the file struct.
 */
t_file	*get_file(t_file_lst	*lst)
{
	return ((t_file *) get(lst));
}

/**
 * @brief Get the cmd object from the list.
 * 
 * @param lst the list element.
 * @return t_cmd* the cmd struct.
 */
t_cmd	*get_cmd(t_cmd_lst *lst)
{
	return ((t_cmd *) get(lst));
}
