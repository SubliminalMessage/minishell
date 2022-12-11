/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonza <dangonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 15:44:13 by dangonza          #+#    #+#             */
/*   Updated: 2022/12/11 19:33:56 by dangonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

// Ctrl + C == Signal 2 (SIGINT)
// Ctrl + \ == Signal 3 (SIGQUIT)

// Should not get to the final version of the Minishell
int MINISHELL_DEBUG = 0; // 0 = false, 1 = true ;; 

int main(int argc, char **argv)
{
    t_bool didExit;
    t_env *env_list;

    if (argc == 2 && str_equals(argv[1], "--debug")) // ToDo: Remove this (global variable)
        MINISHELL_DEBUG = 1;
    env_list = init_environ();
    didExit = false;
    while(!didExit)
        didExit = prompt(&env_list);
    printf("exit\n");
    free_environ(&env_list);
    system("leaks minishell"); // ToDo: Remove this (system leaks on main)
    return (0);
}