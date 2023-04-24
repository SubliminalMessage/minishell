/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonza <dangonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 16:36:10 by dangonza          #+#    #+#             */
/*   Updated: 2023/04/24 18:41:41 by dangonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	init_zero_variable(t_env_lst **envp)
{
	t_bool	did_work;
	char	*underscore;

	underscore = ft_strdup(ft_getenv(*envp, "_"));
	did_work = update_env(envp, ft_strdup("0"), underscore, false);
	if (!did_work)
	{
		ft_lstclear(envp, free_env_node);
		print_parse_error(ERROR_MALLOC, false);
		*envp = NULL;
	}
}

t_env_lst	*init_env(void)
{
	extern char	**environ;
	t_env_lst	*envp;
	t_env_lst	*node;
	int			i;

	i = 0;
	envp = NULL;
	while (environ[i])
	{
		node = new_env_node(environ[i], true);
		if (!node)
		{
			ft_lstclear(&envp, free_env_node);
			print_parse_error(ERROR_MALLOC, false);
			return (NULL);
		}
		ft_lstadd_back(&envp, node);
		i++;
	}
	init_zero_variable(&envp);
	return (envp);
}

t_env_lst	*new_env_node(char *string, t_bool is_visible)
{
	t_env		*node;
	t_env_lst	*node_wrap;
	int			separator_idx;

	if (!string)
		return (NULL);
	node = ft_calloc(1, sizeof(t_env));
	if (!node)
		return (NULL);
	separator_idx = ft_strchr(string, '=') - string;
	node->key = ft_substr(string, 0, separator_idx);
	node->value = ft_substr(string, separator_idx + 1, ft_strlen(string));
	node->is_visible = is_visible;
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
