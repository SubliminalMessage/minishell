/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_result.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jre-gonz <jre-gonz@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 11:17:14 by jre-gonz          #+#    #+#             */
/*   Updated: 2023/04/29 23:12:50 by jre-gonz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/**
 * @brief Wait for all pids and return the result of the last one.
 * @note The array of pids is freed.
 * @note The array must be NULL terminated.
 * @note There is no need to check the error in waitpid. It will only fail if
 * we have already waited for the pid or it is invalid, which is not the case.
 * 
 * @param pids Array of pids to wait for.
 * @return int Exit status of the last pid.
 */
// TODO: echo "hey there!" | cat | cat | wc -> 0 but 113 found
int	ft_wait_result(int *pids)
{
	int		i;
	int		result;
	int		status;
	pid_t	waited_pid;

	i = 0;
	while (pids[i])
	{
		// ft_printf_fd(2, "Waiting for pid %d (i = %d)\n", pids[i], i); // TODO debug
		waited_pid = waitpid(pids[i], &status, 0);
		if (pids[i] == waited_pid && pids[i + 1] == 0)
			result = status;
		i++;
	}
	free(pids);
	return (WEXITSTATUS(result));
}
