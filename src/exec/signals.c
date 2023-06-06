/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonza <dangonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 14:26:37 by dangonza          #+#    #+#             */
/*   Updated: 2023/06/06 17:14:36 by dangonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	sig_handler_prompt(int signal)
{
	(void) signal;
	printf("\n"); // Move to new line
	rl_on_new_line(); // Update Readline
	rl_replace_line("", 0); // Clear user's input
	rl_redisplay(); // Print the prompt again
}

void	ft_prompt_signals(void)
{
	signal(SIGINT, sig_handler_prompt);
	signal(SIGQUIT, SIG_IGN);
}

static void	sig_handler_child_quit(int signal)
{
	(void) signal;
	printf("Quit: 3\n");
	rl_redisplay();
}

void	ft_child_signals(void)
{
	signal(SIGINT, SIG_DFL); // TODO: cat + ^C -> $?: 130
	signal(SIGQUIT, sig_handler_child_quit);
}

static void	sig_handler_heredoc_int(int signal)
{
	(void) signal;
	ft_store_result_code(1);
	ioctl(STDIN_FILENO, TIOCSTI, "\n");
}

void	ft_heredoc_signals(void)
{
	signal(SIGINT, sig_handler_heredoc_int);
	signal(SIGQUIT, SIG_IGN);
}
