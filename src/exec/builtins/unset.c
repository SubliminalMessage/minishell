/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonza <dangonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 16:49:50 by dangonza          #+#    #+#             */
/*   Updated: 2023/06/08 23:09:31 by dangonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/**
 * @brief given an env. list and a key, unsets the key from the env. list
 * 
 * @param envp, the Env. List
 * @param key, the Variable Name to unset
 * 
 * @return t_bool, whether the action where done correctly or not
*/
t_bool	ft_unset_variable(t_env_lst **envp, char *key)
{
	t_env *node;
	t_env_lst *previous_node;
	t_env_lst *lst;

	if (!is_valid_variable_name(key))
	{
		ft_printf_fd(STDERR, "minishell: unset: `%s': not a valid identifier\n", key);
		return (false);
	}
	lst = *envp;
	node = NULL;
	previous_node = lst;
	while (lst)
	{
		node = lst->content;
		if (node && str_equals(node->key, key))
		{
			previous_node->next = lst->next;
			free_env_node(node);
			free(lst);
			break ;
		}
		previous_node = lst;
		lst = lst->next;
	}
	return (true);
}

/**
 * @brief unset builtin.
 * 
 * @note usage: unset
 * 
 * @param cmd command struct.
 * @param envp Environment List struct.
 * @return int exit code.
 */
int	ft_unset(t_cmd *cmd, t_env_lst **envp)
{
	int		argc;
	int		i;
	t_bool	did_anyone_fail;

	did_anyone_fail = false;
	argc = ft_arrsize(cmd->args);
	i = 1;
	while (i < argc)
	{
		if (!ft_unset_variable(envp, cmd->args[i]))
			did_anyone_fail = true;
		i++;
	}
	if (did_anyone_fail)
		return (1);
	return (0);
}
