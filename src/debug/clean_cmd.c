/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jre-gonz <jre-gonz@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 10:07:27 by jre-gonz          #+#    #+#             */
/*   Updated: 2023/01/19 10:52:16 by jre-gonz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "debug_minishell.h"

void	ft_free_cmd(t_cmd	*cmd)
{
	if (!cmd)
		return ;
	// TODO
	free(cmd);
}

void	ft_free_cmd_lst(t_cmd_lst	*cmd)
{
	ft_lstclear((t_list**) &cmd, (void (*)(void *)) ft_free_cmd);
}
