/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonza <dangonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 16:49:50 by dangonza          #+#    #+#             */
/*   Updated: 2023/05/30 17:44:45 by dangonza         ###   ########.fr       */
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
int	ft_env(t_cmd *cmd, t_env_lst *envp)
{
	char	**argv;
	t_env	*node;

	argv = cmd->args;
	if (argv && argv[0] && argv[1])
	{
		printf("env: too many arguments\n");
		return (127);
	}
	while (envp)
	{
		node = (t_env *) envp->content;
		if (node->is_visible && !str_equals(node->value, "")) // TODO: Check if empty 'export'-s appear here or not. (They shouldn't)
			printf("%s=%s\n", node->key, node->value);
		envp = envp->next;
	} // TODO: print $_ at the end of the list ??
	return (0);
}
