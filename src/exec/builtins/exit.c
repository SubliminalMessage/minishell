/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jre-gonz <jre-gonz@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 19:12:27 by jre-gonz          #+#    #+#             */
/*   Updated: 2023/04/29 19:31:02 by jre-gonz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/**
 * @brief exit builtin
 * @note usage: exit [exit_code]
 * 
 * @param cmd command struct
 * @return int exit code
 */
int	ft_exit(t_cmd *cmd)
{
	int	exit_code;

	ft_putstr_fd("exit\n", STDOUT); // TODO refactor msg
	exit_code = 0;
	if (!cmd->args[1])
		exit_code = 0;
	else if (cmd->args[1] && !cmd->args[2])
	{
		exit_code = 2;
		if (ft_isnbr(cmd->args[1]))
			exit_code = (int) ((char) ft_atoi(cmd->args[1]));
		else
			ft_printf_fd(2, "exit: %s: numeric argument required\n", cmd->args[1]); // TODO refactor msg. perror?
	}
	else
	{
		ft_printf_fd(2, "exit: too many arguments\n"); // TODO refactor. perror?
		exit_code = 1;
	}
	return (exit_code);
}
