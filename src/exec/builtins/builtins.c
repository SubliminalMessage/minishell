/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jre-gonz <jre-gonz@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 19:05:32 by jre-gonz          #+#    #+#             */
/*   Updated: 2023/04/29 19:25:48 by jre-gonz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	TODO(t_cmd *cmd)
{
	ft_printf_fd(2, "minishell: %s: TODO\n", cmd->cmd);
	ft_printf_fd(2, "  - Not implemented yet\n");
	return (INVALID);
}

int ft_builtins(t_cmd *cmd, t_cmd_lst *full)
{
	int	exit_code;

	exit_code = 0;
	if (cmd->cmd == NULL)
		ft_copyall(STDIN, STDOUT);
	else if (ft_strncmp(cmd->cmd, "echo", 4) == 0)
		exit_code = ft_echo(cmd);
	else if (ft_strcmp(cmd->cmd, "exit") == 0)
		exit_code = ft_exit(cmd);
	else if (ft_strcmp(cmd->cmd, "cd") == 0)
		exit_code = TODO(cmd);
	// 	exit_code = ft_cd(cmd);
	else if (ft_strcmp(cmd->cmd, "pwd") == 0)
		exit_code = TODO(cmd);
	// 	exit_code = ft_pwd(cmd);
	else if (ft_strcmp(cmd->cmd, "export") == 0)
		exit_code = TODO(cmd);
	// 	exit_code = ft_export(cmd);
	else if (ft_strcmp(cmd->cmd, "unset") == 0)
		exit_code = TODO(cmd);
	// 	exit_code = ft_unset(cmd);
	else if (ft_strcmp(cmd->cmd, "env") == 0)
		exit_code = TODO(cmd);
	// 	exit_code = ft_env(cmd);
	else
		return (INVALID);
	ft_free_cmd_lst(full);
	return (exit(exit_code), exit_code);
}
