/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonza <dangonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 18:46:17 by dangonza          #+#    #+#             */
/*   Updated: 2022/12/08 16:49:44 by dangonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/**
 * @brief This function is used to execute the line the user's wrote
 * 
 * @param line The line to be executed (raw, directly from readline)
*/
void execute_line(char *line)
{
    print_cmds(line);
    // ToDo: Execute 
}

/**
 * @deprecated This function is deprecated and is being used as a test function
*/
void   print_cmds(char *raw)
{
    char **cmds;
    char **args;
    int i;
    int j;

    cmds = ft_split_cmds(raw);
    if (!cmds)
        return ;
    i = -1;
    while (*(cmds + ++i))
    {   
        if (**(cmds + i) == '\0')
            printf(" -> '%s'\n", (char *)NULL);
        else
        {
            // ToDo: Parse Builtins and replace them with '\0'. Then run 'clean_nulls()' :)
            args = clean_nulls(ft_split_args(*(cmds + i)));
            printf("-> '%s'\n", *(cmds + i));
            j = -1;
            while (*(args + ++j))
            {
                printf("\t'%s'\n", *(args + j));
                free(*(args + j));
            }
            free(args);
        }
        free(*(cmds + i));
        printf("\n\n");
    }
    free(cmds);
}