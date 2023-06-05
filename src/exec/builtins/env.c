/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonza <dangonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 16:49:50 by dangonza          #+#    #+#             */
/*   Updated: 2023/06/05 19:18:35 by dangonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/**
 * @brief env builtin.
 * 
 * @note usage: env
 * 
 * 
 * @param cmd command struct.
 * @param envp Environment List struct.
 * @return int exit code.
 */
int	ft_env(t_cmd *cmd, t_env_lst *envp, int fd)
{
	char	**argv;
	t_env	*node;

	argv = cmd->args;
	if (argv && argv[0] && argv[1])
	{
		ft_putstr_fd("env: too many arguments\n", STDERR_FILENO);
		return (127);
	}
	while (envp)
	{
		node = (t_env *) envp->content;
		if (node->is_visible && !str_equals(node->value, ""))
			ft_printf_fd(fd, "%s=%s\n", node->key, node->value);
		envp = envp->next;
	}
	return (0);
}
