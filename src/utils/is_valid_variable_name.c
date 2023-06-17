/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_valid_variable_name.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jre-gonz <jre-gonz@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 21:18:11 by jre-gonz          #+#    #+#             */
/*   Updated: 2023/06/12 21:18:24 by jre-gonz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/**
 * @brief given a String, representing a variable name, returns whether that
 *        name is valid or not. This function is used in both ft_export() and
 *        ft_env().
 * 
 * @param str, the String containing the variable name
 * 
 * @return t_bool, whether it is a valid name or not
*/
t_bool	is_valid_variable_name(char *str)
{
	int	i;

	if (!str || !str[0])
		return (false);
	if (!ft_hasany(VALID_TKN_CHARS, str[0]))
		return (false);
	i = 1;
	while (str[i])
	{
		if (!ft_hasany(VALID_TKN_CHARS"0123456789", str[i]))
			return (false);
		i++;
	}
	return (true);
}
