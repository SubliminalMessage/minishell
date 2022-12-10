/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonza <dangonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 18:46:17 by dangonza          #+#    #+#             */
/*   Updated: 2022/12/10 18:36:20 by dangonza         ###   ########.fr       */
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
    t_command *cmd_list;
    t_command *new;
    int i;

    cmds = ft_split_quote_conscious(raw, '|');
    if (!cmds)
        return ;
    i = -1;
    while (*(cmds + ++i))
    {   
        if (**(cmds + i) == '\0')
            new = new_cmd(NULL);
        else
        {
            // ToDo: Parse Builtins and replace them with '\0'. Then run 'clean_nulls()' :)
            args = clean_nulls(ft_split_quote_conscious(*(cmds + i), ' '));
            new = new_cmd(args);
        }
        ft_cmdadd_back(&cmd_list, new);
        print_cmd(new);
        free(*(cmds + i));
    }
    free(cmds);
}

/**
 * @brief This function creates a new command struct, from a string
 * 
 * @param str The string that represents the command
 * 
 * @return t_command* with the new command's info
*/
t_command *new_cmd(char **args)
{
    t_command *cmd;
    int arg_count;

    cmd = malloc(sizeof(t_command));
    if (!cmd)
        return (NULL);
    if (args == NULL)
    {
        cmd->exec = NULL;
        cmd->argc = 0;
        cmd->argv = NULL;
        cmd->next = NULL;
        return (cmd);
    }
    arg_count = 0;
    while (*(args + arg_count))
        arg_count++;
    cmd->exec = args[0];
    cmd->argc = arg_count;
    cmd->argv = args;
    cmd->next = NULL;
    return (cmd);
}

void	ft_cmdadd_back(t_command **lst, t_command *new)
{
	t_command	*next_elem;

	if (*lst == NULL)
		*lst = new;
	else
	{
		next_elem = *lst;
		while (next_elem->next != NULL)
			next_elem = next_elem->next;
		next_elem->next = new;
	}
}

void free_cmd(t_command **list)
{
    t_command	*next;
    t_command	*temp;
    int         i;

    next = *list;
    i = 0;
    while (next != NULL)
    {
        i = 0;
        while (i < next->argc)
        {
            free(next->argv[i]);
            i++;
        }
        free(next->argv);
        //free(next->redir);
        temp = next;
        next = next->next;
        free(temp);
    }
    *list = NULL;
}