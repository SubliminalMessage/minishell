/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_booleans.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonza <dangonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 15:47:39 by dangonza          #+#    #+#             */
/*   Updated: 2023/01/23 13:31:35 by dangonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <structures.h>

/**
 * @brief Executes the not (!) operation to a boolean. Return the result
 * 
 * @param b, the boolean to which execute the NOT operation
 * 
 * @return t_bool, the result boolean
*/
t_bool	not(t_bool b)
{
	if (b == true)
		return (false);
	return (true);
}
