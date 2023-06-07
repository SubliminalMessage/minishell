/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonza <dangonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 19:05:32 by jre-gonz          #+#    #+#             */
/*   Updated: 2023/06/07 12:53:24 by dangonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int get_out_file(t_cmd_lst *cmd)
{
	t_file *file;

	file = get_file(ft_lstlast(get_cmd(cmd)->out));
	if (!file)
		return (STDOUT_FILENO);
	return (file->fd);
}

/**
 * @brief Executes all the builtins that modifies (writes) the envp list before
 *        creating fork processes. This only happens if there is only ONE
 *        command to execute.
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
void	execute_write_builtin(t_cmd_lst *cmd, t_env_lst **envp)
{
	int	exit_code;
	int	out_fd;

	exit_code = 0;
	if (!ft_open_all_files(get_cmd(cmd)))
	{ // TODO: not sure if this is correct
		write(get_file(ft_lstlast(get_cmd(cmd)->out))->fd, "", 1);
		close_fds_free(cmd);
		return ;
	}
	out_fd = get_out_file(cmd);
	if (str_equals(get_cmd(cmd)->cmd, "cd"))
		exit_code = ft_cd(get_cmd(cmd), envp);
	else if (str_equals(get_cmd(cmd)->cmd, "export"))
		exit_code = ft_export(get_cmd(cmd), envp, out_fd);
	else if (str_equals(get_cmd(cmd)->cmd, "unset"))
		exit_code = ft_unset(get_cmd(cmd), envp);
	else if (str_equals(get_cmd(cmd)->cmd, "exit"))
		close_free_exit(cmd, ft_exit(get_cmd(cmd), true));
	close_fds_free(cmd);
	ft_store_result_code(exit_code, false);
}

/**
 * @brief Checks if the command is a builtin and executes it.
 * @note If the command is not a builtin, it does nothing.
 * @note If the command is a builtin, it frees the cmd_lst and exits.
 * 
 * @param cmd command to check.
 * @param full list of all commands.
 */
void	ft_builtins(t_cmd_lst *cmd_lst, t_cmd_lst *full, t_env_lst **envp)
{
	int	exit_code;
	int	fd_out;
	t_cmd *cmd;

	cmd = get_cmd(cmd_lst);
	fd_out = get_out_file(cmd_lst);
	exit_code = 0;
	if (cmd->cmd == NULL)
		ft_copyall(STDIN, STDOUT);
	else if (str_equals(cmd->cmd, "echo"))
		exit_code = ft_echo(cmd);
	else if (str_equals(cmd->cmd, "exit"))
		exit_code = ft_exit(cmd, false);
	else if (str_equals(cmd->cmd, "cd"))
	 	exit_code = ft_cd(cmd, envp);
	else if (str_equals(cmd->cmd, "pwd"))
		exit_code = ft_pwd(cmd, *envp);
	else if (str_equals(cmd->cmd, "export")) // TODO: No-ENV Minishell exceptions
	 	exit_code = ft_export(cmd, envp, fd_out);
	else if (str_equals(cmd->cmd, "unset"))
	 	exit_code = ft_unset(cmd, envp);
	else if (str_equals(cmd->cmd, "env"))
		exit_code = ft_env(cmd, *envp, fd_out);
	else
		return ;
	ft_free_cmd_lst(full);
	exit(exit_code);
}
