/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonza <dangonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 19:14:25 by jre-gonz          #+#    #+#             */
/*   Updated: 2023/06/04 00:41:04 by dangonza         ###   ########.fr       */
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
	return (str_equals(flag, "-n"));
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
	t_bool	place_new_line;

	i = 1;
	place_new_line = true;
	if (ft_is_minus_n(cmd->args[i]))
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
