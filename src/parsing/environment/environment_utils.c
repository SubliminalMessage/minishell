/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonza <dangonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 18:29:41 by dangonza          #+#    #+#             */
/*   Updated: 2023/06/07 16:26:54 by dangonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/**
 * @brief given a t_env node, returns if it was created correctly (it is valid)
 *       or not.
 * 
 * @param node, the Node to check
 * 
 * @return t_bool, whether it is valid or not.
 * @note If a Node is NOT valid, it will free it. 
*/
t_bool	is_valid_env_node(t_env *node)
{
	if (!node || !node->key)
	{
		free_env_node(node);
		return (false);
	}
	return (true);
}

/**
 * @brief Given a t_env node, it free()-s it
 * 
 * @param node_raw, the Node to free. It has 'void *' type to be used in
 *        ft_lstclear() functions.
*/
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

/**
 * @brief Auxiliar function to init_env(). If the node to create is 'SHLVL', it
 *        handles appropiately.
 * 
 * @note In Bash, the variable $SHLVL represent the 'depth' of shells you are
 *       in. By default, the value is 1, but if you execute a Shell inside of
 *       another, that value will increase by 1. This function handles this
 *       behaviour.
 * 
 * @return char*, the new value of the SHLVL Variable.
*/
char	*env_shell_level_exception(char *shell_level)
{
	int	shlvl;

	if (shell_level == NULL)
		shlvl = 1;
	else
		shlvl = ft_atoi(shell_level) + 1;
	if (shell_level)
		free(shell_level);
	return (ft_itoa(shlvl));
}

/**
 * @brief Given a Key and a Value, it creates a t_env_lst node.
 * 
 * @param key, the Key value (e.g.: 'USER')
 * @param value, the Key Value (e.g.: 'dangonza')
 * @param visible, if this variable will be visible or not. More info in the
 *        docs of new_env_node().
 * 
 * @return t_env_lst, the node created.
*/
t_env_lst	*new_env_node_splitted(char *key, char *value, t_bool visible)
{
	char		*join;
	t_env_lst	*result;

	if (!value)
		join = key;
	else
		join = join_three(key, ft_strdup("="), ft_strdup(value));
	result = new_env_node(join, visible);
	free(join);
	return (result);
}
