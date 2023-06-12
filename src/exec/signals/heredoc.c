/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jre-gonz <jre-gonz@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 19:40:06 by jre-gonz          #+#    #+#             */
/*   Updated: 2023/06/12 19:41:03 by jre-gonz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/**
 * @brief Handle the SIGINT signal in the heredoc.
 * 
 * @param signal Signal to handle.
 */
static void	sig_handler_heredoc_int(int signal)
{
	(void) signal;
	ft_store_result_code(1, true);
	ioctl(STDIN_FILENO, TIOCSTI, "\n");
}

/**
 * @brief Defines the desired signal behavior when the heredoc is working.
 */
void	ft_heredoc_signals(void)
{
	signal(SIGINT, sig_handler_heredoc_int);
	signal(SIGQUIT, SIG_IGN);
}
