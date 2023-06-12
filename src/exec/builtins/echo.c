/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jre-gonz <jre-gonz@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 19:14:25 by jre-gonz          #+#    #+#             */
/*   Updated: 2023/06/12 21:13:15 by jre-gonz         ###   ########.fr       */
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
	while (flag[i] == 'n')
		i++;
	return (flag[i] == '\0');
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
	int		i;
	t_bool	place_new_line;

	i = 1;
	place_new_line = true;
	while (ft_is_minus_n(cmd->args[i]))
	{
		place_new_line = false;
		i++;
	}
	while (cmd->args[i] && cmd->args[i + 1])
	{
		ft_putstr_fd(cmd->args[i++], STDOUT);
		ft_putchar_fd(' ', STDOUT);
	}
	if (cmd->args[i])
		ft_putstr_fd(cmd->args[i], STDOUT);
	if (place_new_line)
		ft_putchar_fd('\n', STDOUT);
	return (0);
}
