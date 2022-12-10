/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonza <dangonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 15:44:13 by dangonza          #+#    #+#             */
/*   Updated: 2022/12/10 18:42:06 by dangonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

// Ctrl + C == Signal 2 (SIGINT)
// Ctrl + \ == Signal 3 (SIGQUIT)

int MINISHELL_DEBUG = 0;

int main(int argc, char **argv)
{
    t_bool didExit;
    t_env *env_list;

    if (argc == 2 && str_equals(argv[1], "--debug"))
        MINISHELL_DEBUG = 1;
    env_list = init_environ();
    didExit = false;
    while(!didExit)
    {
        didExit = prompt(&env_list);

        // t_env *node = env_list;
        // while (node != NULL)
        // {
        //     printf("%s\n", node->join);
        //     node = node->next;
        // }

        // if (!didExit) system("leaks minishell");
    }
    printf("exit\n");
    free_environ(&env_list);
    env_list = NULL;
    system("leaks minishell");
    return (0);
}