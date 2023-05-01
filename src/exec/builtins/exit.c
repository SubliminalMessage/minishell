/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jre-gonz <jre-gonz@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 19:12:27 by jre-gonz          #+#    #+#             */
/*   Updated: 2023/05/01 14:11:02 by jre-gonz         ###   ########.fr       */
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

	ft_putstr_fd(EXIT_MSG, STDOUT);
	if (!cmd->args[1])
		exit_code = 0;
	else if (cmd->args[1] && !cmd->args[2])
	{
		exit_code = 2;
		if (ft_isnbr(cmd->args[1]))
			exit_code = (int) ((char) ft_atoi(cmd->args[1]));
		else
			ft_printf_fd(2, EXIT_ARG_NUM_MSG, cmd->args[1]);
	}
	else
	{
		exit_code = 1;
		ft_printf_fd(2, EXIT_NUM_ARGS_MSG);
	}
	return (exit_code);
}
