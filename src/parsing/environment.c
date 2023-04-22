/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonza <dangonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 16:36:10 by dangonza          #+#    #+#             */
/*   Updated: 2023/04/22 19:18:37 by dangonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_env_lst	*init_env(void)
{
	extern char **environ;
	t_env_lst	*envp;
	t_env_lst	*node;
	int	i;

	i = 0;
	envp = NULL;
	while (environ[i])
	{
		node = new_env_node(environ[i]);
		if (!node)
		{
			ft_lstclear(&envp, free_env_node);
			printf(ERROR_MALLOC);
			return (NULL);
		}
		ft_lstadd_back(&envp, node);
		i++;
	}
	return (envp);
}

char	*env_shell_level_exception(char *shell_level)
{
	int	shlvl;

	shlvl = ft_atoi(shell_level) + 1;
	free(shell_level);
	return (ft_itoa(shlvl));
}

t_env_lst *new_env_node_splitted(char *key, char *value)
{
	char		*join;
	t_env_lst	*result;

	join = join_three(key, ft_strdup("="), value);
	result = new_env_node(join);
	free(join);
	return (result);
}

t_env_lst *new_env_node(char *string)
{
	t_env	*node;
	t_env_lst *node_wrap;
	int		separator_idx;

	if (!string)
		return (NULL);
	node = ft_calloc(1, sizeof(t_env));
	if (!node)
		return (NULL);
	separator_idx = ft_strchr(string, '=') - string;
	node->key = ft_substr(string, 0, separator_idx);
	node->value = ft_substr(string, separator_idx + 1, ft_strlen(string));
	if (str_equals(node->key, "SHLVL"))
		node->value = env_shell_level_exception(node->value);
	if (!is_valid_env_node(node))
		return (NULL);
	node_wrap = ft_lstnew(node);
	if (!node_wrap)
	{
		free_env_node(node);
		return (NULL);
	}
	return (node_wrap);
}

void	free_env_node(void *node_raw)
{
	t_env *node;

	node = (t_env*) node_raw;
	if (!node)
		return ;
	if (node->key)
		free(node->key);
	if (node->value)
		free(node->value);
	free(node);
}

t_bool	is_valid_env_node(t_env *node)
{
	if (!node || !node->key || !node->value)
	{
		free_env_node(node);
		return (false);
	}
	return (true);
}
