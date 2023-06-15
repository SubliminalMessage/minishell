/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_result_code.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jre-gonz <jre-gonz@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 19:12:50 by jre-gonz          #+#    #+#             */
/*   Updated: 2023/06/15 19:22:47 by jre-gonz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

extern int	g_status_code; // TODO linux

/**
 * @brief Stores a result code into the global 'g_status_code'.
 * 
 * @note The result_code will only be stored if the previous code
 *       is exactly 0, or if the 'force' argument is true.
 * 
 * @param result_code, the code to store
 * @param force, whether the 'protection logic' must be ignored or not
*/
void	ft_store_result_code(int result_code, t_bool force)
{
	if (g_status_code == 0 || force)
		g_status_code = result_code;
}
