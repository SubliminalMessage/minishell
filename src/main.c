/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonza <dangonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 15:44:13 by dangonza          #+#    #+#             */
/*   Updated: 2022/11/27 00:55:06 by dangonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int main(void)
{
    extern char **environ;
    int didExit;

    //int i = -1;
    // while (environ[++i])
    // {
    //     printf("%s\n", environ[i]);
    // }
    didExit = 0;
    while(!didExit)
    {
        didExit = prompt();
    }
    //system("leaks minishell");
    return (0);
}