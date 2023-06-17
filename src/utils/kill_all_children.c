/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kill_all_children.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jre-gonz <jre-gonz@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 19:09:03 by jre-gonz          #+#    #+#             */
/*   Updated: 2023/06/15 19:09:17 by jre-gonz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/**
 * @brief Kills all the processes in the given array.
 * 
 * @param pids Array of pids to kill.
 */
void	kill_all_children(pid_t *pids)
{
	int	i;

	i = 0;
	while (pids[i])
		kill(pids[i++], SIGKILL);
	free(pids);
}
