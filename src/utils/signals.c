/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonza <dangonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 16:58:17 by dangonza          #+#    #+#             */
/*   Updated: 2023/05/04 17:53:58 by dangonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

// TODO: Move this file into a better folder ??

void static	handle_readline_signal(int signal)
{
	if (signal == SIGINT) // Ctrl + C
	{
		printf(DEL_SIG""RL_PROMPT"%s\n", rl_line_buffer);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_status_code = 1;
	}
}

// Ctrl + C => 2 (INT)
// Ctrl + \ => 3 (QUIT)
// Ctrl + D => Does not exist (handled in Readline)
void	set_readline_signals(void)
{
	signal(SIGINT, handle_readline_signal);
	signal(SIGQUIT, SIG_IGN); // Ignore
}
