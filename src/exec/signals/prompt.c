/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jre-gonz <jre-gonz@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 19:39:59 by jre-gonz          #+#    #+#             */
/*   Updated: 2023/06/12 19:42:11 by jre-gonz         ###   ########.fr       */
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
