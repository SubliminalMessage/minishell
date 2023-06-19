/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonza <dangonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 19:40:03 by jre-gonz          #+#    #+#             */
/*   Updated: 2023/06/19 14:39:56 by dangonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/**
 * @brief Handle the SIGQUIT signal in a child process.
 * 
 * @param signal Signal to handle.
 */
static void	sig_handler_child_quit(int signal)
{
	(void) signal;
	printf("Quit: 3\n");
	rl_redisplay();
}

/**
 * @brief Defines the desired signal behavior in a child process.
 */
void	ft_child_signals(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, sig_handler_child_quit);
}
