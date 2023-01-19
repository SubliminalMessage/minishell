/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jre-gonz <jre-gonz@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 09:19:19 by jre-gonz          #+#    #+#             */
/*   Updated: 2023/01/19 10:01:32 by jre-gonz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "debug_minishell.h"

// < Makefile cat | wc -l
t_cmd_lst	*ft_cmd1()
{
	t_cmd_lst	*cmd;

	cmd = malloc(sizeof(t_cmd_lst));
	if (!cmd)
		return (NULL);
	return (cmd);
}

void	free_cmd(t_cmd	*cmd)
{
	if (!cmd)
		return ;
	// TODO
	free(cmd);
}

int	main(void)
{
	t_cmd_lst	*cmd;

	cmd = ft_cmd1();
	if (!cmd)
		return (1);
	ft_putendl_fd("Executing...", 1);
	// TODO execute
	ft_putendl_fd("Execution ended", 1);
	ft_lstclear((t_list**) &cmd, (void (*)(void *)) free_cmd);
	return (0);
}
