/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jre-gonz <jre-gonz@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 19:05:32 by jre-gonz          #+#    #+#             */
/*   Updated: 2023/04/29 19:05:47 by jre-gonz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

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

int ft_exit(t_cmd *cmd)
{
	int	exit_code;

	// TODO if no pipes, FULL exit
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
	// else if (ft_strcmp(cmd->cmd, "cd") == 0)
	// 	exit_code = ft_cd(cmd);
	// else if (ft_strcmp(cmd->cmd, "pwd") == 0)
	// 	exit_code = ft_pwd(cmd);
	// else if (ft_strcmp(cmd->cmd, "export") == 0)
	// 	exit_code = ft_export(cmd);
	// else if (ft_strcmp(cmd->cmd, "unset") == 0)
	// 	exit_code = ft_unset(cmd);
	// else if (ft_strcmp(cmd->cmd, "env") == 0)
	// 	exit_code = ft_env(cmd);
	else
		return (0);
	ft_free_cmd_lst(full);
	exit(exit_code);
	return (INVALID);
}
