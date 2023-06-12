/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jre-gonz <jre-gonz@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 19:40:03 by jre-gonz          #+#    #+#             */
/*   Updated: 2023/06/12 19:40:45 by jre-gonz         ###   ########.fr       */
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
