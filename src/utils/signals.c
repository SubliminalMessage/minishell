/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonza <dangonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 14:18:04 by dangonza          #+#    #+#             */
/*   Updated: 2023/05/02 14:45:14 by dangonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

// TODO: Move this file into it's own folder (?) src/signals/signal_XYZ.c (??)

#define DEL_SIG "\b\b\033[K" // TODO: Move to .h file

void	handle_readline_signal(int signal)
{
	//printf("Handled signal (%d)\n", signal);
	if (signal == SIGINT)
	{
		// Remove ^C
		//printf("%s\n", DEL_SIG);
		/*printf("\n");
		rl_on_new_line();
		//rl_replace_line("", 0);
		rl_line_buffer = "";
		//rl_redisplay();
		write(0, "minishell >", 12);*/
	}
}

void	setup_readline_signals(void)
{
	printf("Called!\n");
	signal(SIGINT, handle_readline_signal); // Ctrl + C
}
