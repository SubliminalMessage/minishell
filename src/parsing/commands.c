/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonza <dangonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 18:46:17 by dangonza          #+#    #+#             */
/*   Updated: 2022/12/10 19:51:03 by dangonza         ###   ########.fr       */
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
    char **raw_cmds;
    t_command *cmd_list;
    
    // 0. Split the line into commands
    raw_cmds = ft_split_quote_conscious(line, '|');
    if (!raw_cmds)
        return ;
    
    // 1. Parse the splitted line into commands
    cmd_list = parse_commands(raw_cmds);
    print_cmds(cmd_list);

    // 2. Check everything is fine      
    if (cmd_list == NULL)
        return ;

    // 3. Execute the commands
    // ToDo: Execute commands
    
    // 4. Clean up
    free_cmd(&cmd_list);
}

t_command   *parse_commands(char **cmds)
{
    t_command *cmd_list;
    t_command *new;
    char **args;
    int i;

    i = -1;
    cmd_list = NULL;
    while (*(cmds + ++i))
    {   
        if (**(cmds + i) == '\0')
            break ;
        // ToDo: Parse Redirecctions and replace them with '\0'. Then run 'clean_nulls()' :)
        args = clean_nulls(ft_split_quote_conscious(*(cmds + i), ' '));
        new = new_cmd(args);
        ft_cmdadd_back(&cmd_list, new);
    }
    if (cmds[i] != NULL)
    {
        printf(RED"  »  "RESET"Parse error near '|'\n\n"); // ToDo: Move this to an error function
        free_cmd(&cmd_list); // This, internally, does cmd_list = NULL, so no problem when returning it
    }
    free_str_array(cmds);
    return (cmd_list);
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

    cmd = malloc(sizeof(t_command));
    if (!cmd)
        return (NULL);
    cmd->next = NULL;
    cmd->argv = args;
    if (args == NULL)
    {
        cmd->exec = NULL;
        return (cmd);
    }
    cmd->exec = args[0];
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
        printf("pointer => %p\n\n", next_elem);
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
        i = -1;
        while (next->argv[++i] != NULL)
            free(next->argv[i]);
        free(next->argv);
        //free(next->redir);
        temp = next;
        next = next->next;
        free(temp);
    }
    *list = NULL;
}