/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jre-gonz <jre-gonz@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 14:26:37 by dangonza          #+#    #+#             */
/*   Updated: 2023/06/12 19:28:53 by jre-gonz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/**
 * @brief Handle the SIGINT signal in the prompt.
 * @note Prevents the character like ^C from being printed while preserving
 * the minishell prompt.
 * 
 * @param signal Signal to handle.
 */
static void	sig_handler_prompt(int signal)
{
	(void) signal;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

/**
 * @brief Sets the desired signal behavior when the prompt is waiting
 *  for a command.
 */
void	ft_prompt_signals(void)
{
	signal(SIGINT, sig_handler_prompt);
	signal(SIGQUIT, SIG_IGN);
}

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
