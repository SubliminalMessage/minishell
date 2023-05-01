/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jre-gonz <jre-gonz@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 19:14:25 by jre-gonz          #+#    #+#             */
/*   Updated: 2023/05/01 15:16:27 by jre-gonz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/**
 * @brief Checks if the given flag is -n.
 * 
 * @note In the original bash implementation, the flag can be repeated
 * as many times as the user wants.
 * Therefore, `echo -n -nnnnnn -n hey` is the same as `echo -n hey`.
 * 
 * @param flag 
 * @return t_bool 
 */
t_bool	ft_is_minus_n(char *flag)
{
	int	i;

	if (!flag || ft_strncmp(flag, "-n", 2) != 0)
		return (false);
	i = 2;
	while (flag[i])
	{
		if (flag[i++] != 'n')
			return (false);
	}
	return (true);
}

/**
 * @brief echo builtin.
 * 
 * @note usage: echo [-n] [string ...]
 * 
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
	while (ft_is_minus_n(cmd->args[i]))
	{
		n = false;
		i++;
	}
	while (cmd->args[i] && cmd->args[i + 1])
	{
		ft_putstr_fd(cmd->args[i++], STDOUT);
		ft_putchar_fd(' ', STDOUT);
	}
	if (cmd->args[i])
		ft_putstr_fd(cmd->args[i], STDOUT);
	if (n)
		ft_putchar_fd('\n', STDOUT);
	return (0);
}
