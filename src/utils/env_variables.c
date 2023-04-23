/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_variables.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonza <dangonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 16:48:56 by dangonza          #+#    #+#             */
/*   Updated: 2023/04/23 17:44:44 by dangonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char *ft_getenv(t_env_lst *envp, char *key)
{
	t_env	*node;

	while (envp)
	{
		node = envp->content;
		if (node && str_equals(node->key, key))
			return (node->value);
		envp = envp->next;
	}
	// TODO: Handle exceptions such as '$$' or '$?'
	// ($_) https://unix.stackexchange.com/questions/280453/understand-the-meaning-of
	return ("");
}

t_bool	update_env(t_env_lst **envp, char *key, char *value, t_bool visible)
{
	t_env_lst	*lst;
	t_env_lst	*new_node;
	t_env		*node;

	if (!envp || !*envp || !key || !value)
		return (false);
	lst = *envp;
	while (lst)
	{
		node = lst->content;
		lst = lst->next;
		if (!node || !str_equals(node->key, key))
			continue ;
		free(node->value);
		free(key);
		node->value = value;
		return (true);
	}
	new_node = new_env_node_splitted(key, value, visible);
	if (!new_node)
		return (false);
	ft_lstadd_back(envp, new_node);
	return (true);
}

char **build_envp(t_env_lst *envp)
{
	int	size;
	int i;
	t_env	*node;
	char	**matrix;

	size = ft_lstsize(envp);
	matrix = ft_calloc(size + 1, sizeof(char *));
	if (!matrix)
		return (NULL);
	i = -1;
	while (envp && ++i < size)
	{
		node = envp->content;
		envp = envp->next;
		if (!node || !node->is_visible)
			continue ;
		matrix[i] = join_three(ft_strdup(node->key), ft_strdup("="), ft_strdup(node->value));
		if (!matrix[i])
		{
			free_str_array(matrix);
			return (NULL);
		}
	}
	return (matrix);
}
