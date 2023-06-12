/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   value_is_null.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jre-gonz <jre-gonz@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 21:23:37 by jre-gonz          #+#    #+#             */
/*   Updated: 2023/06/12 21:23:45 by jre-gonz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/**
 * @brief Given a Key and an Env. List, returns whether the value
 *        is NULL, or not. Empty strings ("") are not considered NULL.
 * 
 * @param key, the key to search
 * @param envp, the Env. List to search into
 * 
 * @return t_bool, whether the value of that key is null or not. If not found,
 *         return true.
*/
t_bool	value_is_null(char *key, t_env_lst *envp)
{
	t_env	*node;

	if (!key)
		return (true);
	while (envp)
	{
		node = envp->content;
		if (!str_equals(key, node->key))
		{
			envp = envp->next;
			continue ;
		}
		if (node->value)
			return (false);
		return (true);
	}
	return (true);
}
