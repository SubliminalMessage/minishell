/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jre-gonz <jre-gonz@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 19:14:25 by jre-gonz          #+#    #+#             */
/*   Updated: 2023/04/29 19:20:20 by jre-gonz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/**
 * @brief echo builtin.
 * 
 * @note usage: echo [-n] [string ...]
 * 
 * TODO -nnnnnnnnnnn should be implemented?
 * - If the -n option is present, it works like in bash.
 * - Adding the logic to handle it is not worth it without any more flags.
 * 
 * @param cmd command struct.
 * @return int exit code.
 */
int	ft_echo(t_cmd *cmd)
{
	int	i;
	t_bool	n;

	i = 1;
	n = true;
	if (cmd->args[i] && ft_strcmp(cmd->args[i], "-n") == 0)
	{
		n = false;
		i++;
	}
	while (cmd->args[i])
	{
		ft_putstr_fd(cmd->args[i], STDOUT);
		if (cmd->args[i + 1])
			ft_putchar_fd(' ', STDOUT);
		i++;
	}
	if (n)
		ft_putchar_fd('\n', STDOUT);
	return (0);
}
