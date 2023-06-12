/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jre-gonz <jre-gonz@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 16:49:50 by dangonza          #+#    #+#             */
/*   Updated: 2023/06/12 20:15:25 by jre-gonz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

#define CD_ERROR "cd: %s: No such file or directory\n"

/**
 * @brief Obtains the path to go to.
 * 
 * @note How it works:
 * - No args? Go home.
 * - At least one arg? Get the first one ([1])
 *  - Is it "-"? Go to OLDPWD.
 *  - Else, go to the path.
 * 
 * @param args 
 * @param envp 
 * @return char* 
 */
static char	*ft_get_wanted_path(char **args, t_env_lst **envp)
{
	if (ft_arrsize(args) == 1)
		return (ft_gethome(*envp));
	else if (ft_arrsize(args) > 1)
	{
		if (str_equals(args[1], "-"))
			return (ft_getenv(*envp, "OLDPWD"));
		else
			return (ft_strdup(args[1]));
	}
	else
		return (ft_strdup(""));
}

/**
 * @brief cd builtin.
 * 
 * @note usage: cd
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
	path = ft_get_wanted_path(cmd->args, envp);
	result = chdir(path);
	if (result != 0)
		ft_printf_fd(STDERR_FILENO, MINISHELL_ERROR CD_ERROR, path);
	free(path);
	update_env(envp, "OLDPWD", current_path, true);
	getcwd(current_path, 4096);
	update_env(envp, "PWD", current_path, true);
	if (result == 0)
		return (0);
	return (1);
}
