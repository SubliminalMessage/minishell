/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonza <dangonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 18:46:17 by dangonza          #+#    #+#             */
/*   Updated: 2022/12/07 19:33:29 by dangonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void execute_line(char *line)
{
    print_cmds(line);
    // ToDo: Execute 
}

 void   print_cmds(char *raw)
 {
    char **cmds;
    int i;

    cmds = ft_split_cmds(raw);
    if (!cmds)
        return ;
    i = -1;
    while (*(cmds + ++i))
    {   
        if (**(cmds + i) == '\0')
            printf(" -> '%s'\n", (char *)NULL);
        else
            printf("-> '%s'\n", *(cmds + i));
        free(*(cmds + i));
    }
    free(cmds);
 }