/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jre-gonz <jre-gonz@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 11:01:17 by jre-gonz          #+#    #+#             */
/*   Updated: 2023/01/23 11:08:08 by jre-gonz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "debug_minishell.h"

static void	*get(t_list *lst)
{
	if (!lst)
		return (NULL);
	return (lst->content);
}

t_file	*get_file(t_file_lst	*lst)
{
	return ((t_file *) get(lst));
}

t_cmd	*get_cmd(t_cmd_lst *lst)
{
	return ((t_cmd *) get(lst));
}
