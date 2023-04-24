/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonza <dangonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 18:29:41 by dangonza          #+#    #+#             */
/*   Updated: 2023/04/24 18:43:55 by dangonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_bool	is_valid_env_node(t_env *node)
{
	if (!node || !node->key || !node->value)
	{
		free_env_node(node);
		return (false);
	}
	return (true);
}

void	free_env_node(void *node_raw)
{
	t_env	*node;

	node = (t_env *) node_raw;
	if (!node)
		return ;
	if (node->key)
		free(node->key);
	if (node->value)
		free(node->value);
	free(node);
}

char	*env_shell_level_exception(char *shell_level)
{
	int	shlvl;

	shlvl = ft_atoi(shell_level) + 1;
	free(shell_level);
	return (ft_itoa(shlvl));
}

t_env_lst	*new_env_node_splitted(char *key, char *value, t_bool visible)
{
	char		*join;
	t_env_lst	*result;

	join = join_three(key, ft_strdup("="), value);
	result = new_env_node(join, visible);
	free(join);
	return (result);
}
