/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonza <dangonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 16:49:50 by dangonza          #+#    #+#             */
/*   Updated: 2023/05/30 17:24:31 by dangonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/**
 * @brief env builtin.
 * 
 * @note usage: pwd
 * 
 * 
 * @param cmd command struct.
 * @param envp Environment List struct.
 * @return int exit code.
 */
int	ft_pwd(t_cmd *cmd, t_env_lst *envp)
{
	char	**argv;
	char	*pwd;

	argv = cmd->args;
	if (argv && argv[0] && argv[1])
	{
		printf("pwd: too many arguments\n");
		return (1);
	}
	pwd = ft_getenv(envp, "PWD");
	printf("%s\n", pwd);
	free(pwd);
	return (0);
}
