/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonza <dangonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 15:44:13 by dangonza          #+#    #+#             */
/*   Updated: 2022/12/07 00:13:52 by dangonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int main(void)
{
    bool didExit;
    t_env *env_list;

    env_list = init_environ();
    (void) env_list;
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
    free_environ(&env_list);
    env_list = NULL;
    system("leaks minishell");
    return (0);
}