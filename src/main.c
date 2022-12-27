/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonza <dangonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 15:44:13 by dangonza          #+#    #+#             */
/*   Updated: 2022/12/27 11:47:47 by jre-gonz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

// Ctrl + C == Signal 2 (SIGINT)
// Ctrl + \ == Signal 3 (SIGQUIT)

// TODO: Should not get to the final version of the Minishell
t_bool g_minishell_debug = false;

void	check_leaks(void)
{
	system("leaks -q minishell"); // TODO: Remove this (system leaks on main)
}

int main(int argc, char **argv)
{
	t_bool didExit;
	t_env *env_list;

	if (argc == 2 && str_equals(argv[1], "--debug")) // TODO: Remove this (global variable)
		g_minishell_debug = true;
	if (g_minishell_debug)
		atexit(check_leaks);
	env_list = init_environ();
	didExit = false;
	while(!didExit)
		didExit = prompt(&env_list);
	printf("exit\n");
	free_environ(&env_list);
	return (0);
}
