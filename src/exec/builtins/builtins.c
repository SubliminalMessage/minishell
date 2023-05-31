/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonza <dangonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 19:05:32 by jre-gonz          #+#    #+#             */
/*   Updated: 2023/05/31 21:19:19 by dangonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	TODO(t_cmd *cmd)
{
	ft_printf_fd(2, "minishell: %s: TODO\n", cmd->cmd);
	ft_printf_fd(2, "  - Not implemented yet\n");
	return (INVALID);
}

static t_bool	str_equal_cmd(char *a, char *b)
{
	char	*str_a;
	char	*str_b;
	t_bool	return_value;

	str_a = ft_strdup(a);
	str_b = ft_strdup(b);
	if (str_a)
		ft_strtoupper(str_a);
	if (str_b)
		ft_strtoupper(str_b);
	return_value = str_equals(str_a, str_b);
	if (str_a)
		free(str_a);
	if (str_b)
		free(str_b);
	return (return_value);
}

/**
 * @brief Executes all the builtins that modifies (writes) the envp list before
 *        creating fork processes. This only happens if there is only ONE
 *        command to execute. This execution also DO NOT PRINT anything on
 *        screen. This is done once the builtin is executed on the
 *        child process.
 * 
 * @param cmd The cmd to execute
 * @param envp, The envp list to modify
 * 
 * @note In order to not-print anything on screen (errors), a print flag is 
 *       send to each one of the builtins. More info on each of the builtins.
 * 
 * @note This execution is mandatory to be made on the parent process, because
 *       the child process creates a copy of the envp, and any modification of
 *       it won't affect the original one. Thus, this modifications are made
 *       'locally', but do not persist between commands. The fastest solution
 *       is to make these modification on the parent (a.k.a.: this function).
*/
void	execute_write_builtin(t_cmd *cmd, t_env_lst **envp)
{
	printf("Called execute write\n");
	if (str_equal_cmd(cmd->cmd, "CD"))
		//ft_cd(cmd, envp);
		printf("Not implemented (cd)\n");
	else if (str_equal_cmd(cmd->cmd, "EXPORT"))
		ft_export(cmd, envp, false);
	else if (str_equal_cmd(cmd->cmd, "UNSET"))
		//ft_unset(cmd, envp);
		printf("Not implemented (unset)\n");
}

/**
 * @brief Checks if the command is a builtin and executes it.
 * @note If the command is not a builtin, it does nothing.
 * @note If the command is a builtin, it frees the cmd_lst and exits.
 * 
 * @param cmd command to check.
 * @param full list of all commands.
 */
void	ft_builtins(t_cmd *cmd, t_cmd_lst *full, t_env_lst **envp)
{
	int	exit_code;

	exit_code = 0;
	if (cmd->cmd == NULL)
		ft_copyall(STDIN, STDOUT);
	else if (str_equal_cmd(cmd->cmd, "ECHO")) // Done
		exit_code = ft_echo(cmd);
	else if (str_equal_cmd(cmd->cmd, "EXIT")) // Done
		exit_code = ft_exit(cmd);
	else if (str_equal_cmd(cmd->cmd, "CD"))
		exit_code = TODO(cmd);
	// 	exit_code = ft_cd(cmd);
	else if (str_equal_cmd(cmd->cmd, "PWD")) // Done
		exit_code = ft_pwd(cmd, *envp);
	else if (str_equal_cmd(cmd->cmd, "EXPORT")) // WIP
	 	exit_code = ft_export(cmd, envp, true);
	else if (str_equal_cmd(cmd->cmd, "UNSET"))
		exit_code = TODO(cmd);
	// 	exit_code = ft_unset(cmd);
	else if (str_equal_cmd(cmd->cmd, "ENV"))
		exit_code = ft_env(cmd, *envp);
	else
		return ;
		ft_free_cmd_lst(full);
		exit(exit_code);
}
