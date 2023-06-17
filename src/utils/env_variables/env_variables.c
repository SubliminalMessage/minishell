/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_variables.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jre-gonz <jre-gonz@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 16:48:56 by dangonza          #+#    #+#             */
/*   Updated: 2023/06/15 19:02:28 by jre-gonz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

extern int	g_status_code; // TODO linux

/**
 * @brief Returns the path stored in $HOME. If the value is not set, tries
 *        to recover it from $0.
 * 
 * @param envp, the Env. List to read from
 * 
 * @return char*, the content of $HOME, or its fallback value
*/
char	*ft_gethome(t_env_lst *envp)
{
	char	*home;

	home = ft_getenv(envp, "HOME");
	if (!str_equals(home, ""))
		return (home);
	free(home);
	return (build_home(envp));
}

/**
 * @brief Acts exactly like getenv(), but it takes the variables from a
 *        t_env_lst structure.
 * 
 * @param envp, the Env. Var. List where the Variable is going to be searched
 * @param key, the Name of the Variable (e.g.: 'USER')
 * 
 * @return char*, the value of the variable. Empty string if not found.
 * @note The return string DOES NOT HAVE TO BE ft_strdup() right after calling
 *       the function. The caller MUST free() this return value.
*/
char	*ft_getenv(t_env_lst *envp, char *key)
{
	t_env		*node;

	if (str_equals(key, "?"))
		return (ft_itoa(g_status_code));
	while (envp)
	{
		node = envp->content;
		if (node && str_equals(node->key, key))
		{
			if (node->value)
				return (ft_strdup(node->value));
			else
				return (ft_strdup(""));
		}
		envp = envp->next;
	}
	return (ft_strdup(""));
}

/**
 * @brief Given a Key and a Value, updates the variable (or creates it)
 *        with the new value.
 * 
 * @param env, double pointer to the Env. Var. List to update the var from
 * @param key, the name of the variable (e.g.: 'USER')
 * @param value, the value of that variable (e.g.: 'dangonza').
 * @param vsbl, if the variable is visible or not. More on this on the docs
 *        of the function new_env_node()
 * 
 * @note Please, do not malloc() neither key nor value. Or, if you do so,
 *       be sure to free it afterwards.
 * 
 * @return t_bool, whether if everything went OK or not.
*/
t_bool	update_env(t_env_lst **env, char *key, char *value, t_bool vsbl)
{
	t_env_lst	*lst;
	t_env_lst	*new_node;
	t_env		*node;

	if (!env || !key)
		return (false);
	lst = *env;
	while (lst)
	{
		node = lst->content;
		lst = lst->next;
		if (!node || !str_equals(node->key, key))
			continue ;
		if (value)
			value = ft_strdup(value);
		if (node->value)
			free(node->value);
		node->value = value;
		return (true);
	}
	new_node = new_env_node_splitted(ft_strdup(key), value, vsbl);
	if (!new_node)
		return (false);
	ft_lstadd_back(env, new_node);
	return (true);
}

/**
 * @brief Norminette issues. Util function for build_envp().
 *        Constructs the Key-Value of a node.
 * 
 * @param n, the node
 * 
 * @return char *, a string of the Key-Value representation
*/
static char	*ft_getmatrix_value(t_env *n)
{
	char	*equal;

	equal = ft_strdup("=");
	if (!n->value)
		return (join_two(ft_strdup(n->key), equal));
	return (join_three(ft_strdup(n->key), equal, ft_strdup(n->value)));
}

/**
 * @brief Given a Env. Var. List, builds a char** to use in execve()
 * 
 * @param envp, the Env. Var. List
 * 
 * @return char**, the String Array containing the Variables
*/
char	**build_envp(t_env_lst *envp, t_bool persist_nulls)
{
	int		size;
	int		i;
	t_env	*node;
	char	**matrix;

	size = ft_lstsize(envp);
	matrix = ft_calloc(size + 1, sizeof(char *));
	if (!matrix)
		return (NULL);
	i = -1;
	while (envp)
	{
		node = envp->content;
		envp = envp->next;
		if (!node || !node->is_visible || (!node->value && !persist_nulls))
			continue ;
		matrix[++i] = ft_getmatrix_value(node);
		if (!matrix[i])
		{
			free_str_array(matrix);
			return (NULL);
		}
	}
	return (matrix);
}
