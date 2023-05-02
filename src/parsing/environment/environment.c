/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonza <dangonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 16:36:10 by dangonza          #+#    #+#             */
/*   Updated: 2023/05/29 19:13:07 by dangonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/**
 * @brief Init the Zero Variable '$0' at the start of the minishell.
 * 
 * @note In bash, '$0' prints the executable it's running on ('bash'). In
 *       order to replicate this behaviour, we 'read' the variable $_, whose
 *       content at the start of the Shell is the Absolute Path to
 *       the Minishell.
 * 
 * @param envp, the Env. Var. List, for both reading and writing to.
*/
void	init_zero_variable(t_env_lst **envp)
{
	t_bool	did_work;
	char	*underscore;

	underscore = ft_getenv(*envp, "_");
	did_work = update_env(envp, "0", underscore, false);
	free(underscore);
	if (!did_work)
	{
		ft_lstclear(envp, free_env_node);
		print_parse_error(ERROR_MALLOC, false);
		*envp = NULL;
	}
}

/**
 * @brief Initializes the t_env_lst that will be used all through the Shell
 *        to expand Variables and such.
 * 
 * @param environ, the Environment List from the main()
 * 
 * @return t_env_lst, the List created. NULL if something failed.
*/
t_env_lst	*init_env(char **environ)
{
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

/**
 * @brief Given a String in the form 'KEY=VALUE', transforms it into a
 *       t_env_lst, that will be appended to the corresponding Env. List.
 * 
 * @param string, the String that will be transformed.
 * @param is_visible, to set the visibility of a variable.
 * @note is_visible should be 'true' by default. If a variable has 'false' as
 *       it's visibility, it will only be possible to 'read' and 'write' the
 *       variable (just like any other), but other functions like build_env()
 *       will ignore them.
 * 
 * @return t_env_lst, the node created.
*/
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
