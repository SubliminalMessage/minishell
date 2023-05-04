/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonza <dangonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2023/05/04 18:18:46 by dangonza         ###   ########.fr       */
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
