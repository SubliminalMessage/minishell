/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonza <dangonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 14:26:37 by dangonza          #+#    #+#             */
/*   Updated: 2023/06/04 15:19:00 by dangonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	sig_handler_prompt(int signal)
{
	(void) signal;
	printf("\n"); // Move to new line
	rl_on_new_line(); // Update Readline
	rl_replace_line("", 0); // Clear user's input
	rl_redisplay(); // Print the prompt again
	g_status_code = 1; // TODO: Modify via function (to keep track of it for debug) <??
}

void	ft_prompt_signals(void)
{
	signal(SIGINT, sig_handler_prompt);
	signal(SIGQUIT, SIG_IGN);
}
