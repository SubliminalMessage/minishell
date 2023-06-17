/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_home.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jre-gonz <jre-gonz@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 19:01:58 by jre-gonz          #+#    #+#             */
/*   Updated: 2023/06/15 19:02:34 by jre-gonz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/**
 * @brief Util function. Does the same thing as ft_chardup(), but occupies less
 *        than the original. Norminette issues :(
*/
static char	*chdup(char c)
{
	return (ft_chardup(c));
}

/**
 * @brief Given an Env. List, tries to build the $HOME value out of $0.
 *        This function is used when the $HOME variable is not set. It acts
 *        like a fallback value.
 * 
 * @param envp, the Env. List
 * 
 * @return char*, the fallback value for $HOME (if found)
*/
char	*build_home(t_env_lst *envp)
{
	char	*zero;
	char	*result;
	char	**split;
	int		i;

	zero = ft_getenv(envp, "0");
	if (!zero)
		return (ft_strdup(""));
	split = ft_split(zero, '/');
	free(zero);
	if (!split || !split[0] || !split[1] || !str_equals(split[0], "Users"))
		result = NULL;
	else
		result = join_three(chdup('/'), ft_strdup(split[0]), chdup('/'));
	if (result)
		result = join_three(result, ft_strdup(split[1]), chdup('/'));
	i = -1;
	while (split && split[++i])
		free(split[i]);
	if (split)
		free(split);
	if (result)
		return (result);
	return (ft_strdup(""));
}
