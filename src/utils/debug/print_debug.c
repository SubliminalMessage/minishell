/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_debug.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonza <dangonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 17:02:53 by dangonza          #+#    #+#             */
/*   Updated: 2023/01/24 15:27:47 by dangonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*    This file is not meant to get into the final version of the Minishell   */

#include <minishell.h>

#define QUOTE_COLOR "\033[38;5;58m"
#define STR_COLOR "\033[38;5;130m"
#define NUM_COLOR "\033[38;5;115m"
#define CURLY_COLOR "\033[38;5;58m"
#define COLON_COLOR "\033[38;5;235m"
#define ARR_COLOR "\033[38;5;170m"
#define KEY_COLOR "\033[38;5;26m"
#define COMMA_COLOR "\033[38;5;58m"
#define NULL_COLOR "\033[38;5;53m"

#ifndef DEBUG
#define DEBUG 0
#endif

void    print_quotes(char *str)
{
    /*
        »String«
    */
   printf(QUOTE_COLOR"▹"STR_COLOR"%s"QUOTE_COLOR"◃", str);
}

void print_str_arr(char **arr)
{
    /*
        [ "Hello", "World" ]
    */
    int total = 0;
    printf(ARR_COLOR"[ "RESET);
    while (*arr != NULL)
    {
        total++;
        print_quotes(*arr);
        arr++;
        if (*arr != NULL)
            printf(COMMA_COLOR", "RESET);
    }
    printf(ARR_COLOR" ]"RESET);
    printf(CURLY_COLOR" ("NUM_COLOR"%d"CURLY_COLOR")", total);
}

void   print_cmds(t_command *cmd_list)
{
    t_command *cmd;

    cmd = cmd_list;
    while (cmd)
    {
        print_single_cmd(cmd);
        cmd = cmd->next;
    }
}

void    print_single_cmd(t_command *cmd)
{
    /*
    {
        exec: "echo",
        argc: 3,
        argv: [ "echo", "Hello", "World" ],
        redir: NULL
    }
    */
    extern int MINISHELL_DEBUG;
    if(!MINISHELL_DEBUG)
        return ;
    printf(CURLY_COLOR"{\n"RESET);
    if (cmd->exec == NULL)
    {
        printf(NULL_COLOR"    NULL\n");
    }
    else
    {
        printf(KEY_COLOR"    exec"COLON_COLOR": "); 
            print_quotes(cmd->exec);
            printf(COMMA_COLOR",\n"RESET);
        printf(KEY_COLOR"    argv"COLON_COLOR": "); 
            print_str_arr(cmd->argv);
            printf(COMMA_COLOR",\n"RESET);
        printf(KEY_COLOR"    redirs"COLON_COLOR": "); 
            printf(NULL_COLOR"NULL\n");
        printf(KEY_COLOR"    next"COLON_COLOR": ");
        if (cmd->next != NULL)
            printf(NULL_COLOR"%p\n", cmd->next);
        else
            printf(NULL_COLOR"NULL\n");
    }
    printf(CURLY_COLOR"}\n"RESET);
}
