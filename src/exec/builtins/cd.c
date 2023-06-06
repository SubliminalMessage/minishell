/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonza <dangonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 16:49:50 by dangonza          #+#    #+#             */
/*   Updated: 2023/06/05 19:19:59 by dangonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
/**
 * @brief cd builtin.
 * 
 * @note usage: cd
 * 
 * 
 * @param cmd command struct.
 * @param envp Environment List struct.
 * @return int exit code.
 */
int	ft_cd(t_cmd *cmd, t_env_lst **envp)
{
	char	*path;
	char	current_path[4096];
	int		result;

	getcwd(current_path, 4096);
	if (ft_arrsize(cmd->args) == 1) // No args, go to home
		path = ft_gethome(*envp);
	else if (ft_arrsize(cmd->args) > 1) // At least one path. Get the first one ([1])
		if (str_equals(cmd->args[1], "-"))
			path = ft_getenv(*envp, "OLDPWD");
		else
			path = ft_strdup(cmd->args[1]);
	else
		path = ft_strdup("");
	result = chdir(path);
	if (result != 0)
		ft_printf_fd(STDERR_FILENO, "minishell: cd: %s: No such file or directory\n", path);
	free(path);
	update_env(envp, "OLDPWD", current_path, true);
	getcwd(current_path, 4096);
	update_env(envp, "PWD", current_path, true);
	if (result == 0)
		return (0);
	return (1);
}
