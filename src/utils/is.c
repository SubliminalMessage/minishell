/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jre-gonz <jre-gonz@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 18:52:09 by jre-gonz          #+#    #+#             */
/*   Updated: 2023/06/15 18:52:40 by jre-gonz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/**
 * @brief Given a character, returns whether that char is a '\0' or any of
 *        the characters in the set.
 * 
 * @param c, the character
 * 
 * @return whether it is a space or not
*/
t_bool	is(char *set, char c)
{
	if (!c)
		return (true);
	while (*set)
		if (*set++ == c)
			return (true);
	return (false);
}
