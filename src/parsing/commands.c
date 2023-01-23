/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonza <dangonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 18:46:17 by dangonza          #+#    #+#             */
/*   Updated: 2023/01/23 13:46:27 by dangonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/**
 * @brief Expands the Environment variables of every single ARGV
 * 
 * @param **cmd, the list of commands
 * @param *env_list, the list of environment variables of the Minishell
*/
void	expand_arguments(t_command **cmd, t_env *env_list)
{
	t_command *node;
	char *str;
	int index;

	if (!cmd || !(*cmd) || !(*cmd)->argv)
		return ;
	node = *cmd;
	while (node)
	{
		index = -1;
		str = NULL;
		while (str || index == -1)
		{
			index++;
			str = node->argv[index];
			if (!str)
				break ;
			node->argv[index] = expand_str(str, env_list);
		}
		node = node->next;
	}
}

/**
 * @brief This function is used to execute the line the user's wrote
 * 
 * @param line The line to be executed (raw, directly from readline)
*/
void execute_line(char *line, t_env **env_list)
{
    char **raw_cmds;
    t_command *cmd_list;
    
    // 0. Split the line into commands
    raw_cmds = ft_split_quote_conscious(line, '|');
    if (!raw_cmds)
        return ;
    
    // 1.1. Parse the splitted line into commands
    cmd_list = parse_commands(raw_cmds);

    // 1.2. Parse the redirections
    // Todo: parse_redirections(&cmd_list);

    // 1.3. Expand the variables
    // TODO: expand_variables(&cmd_list);
	expand_arguments(&cmd_list, *env_list);
    print_cmds(cmd_list);

    // 2. Check everything is fine      
    if (cmd_list == NULL)
        return ;

    // 3. Execute the commands
    // TODO: Execute commands
    
    // 4. Clean up
    free_cmd(&cmd_list);
}

t_command   *parse_commands(char **cmds)
{
    t_command *cmd_list;
    char **args;
    int i;

    i = -1;
    cmd_list = NULL;
    while (*(cmds + ++i))
    {   
        if (**(cmds + i) == '\0')
            break ;
        args = clean_nulls(ft_split_quote_conscious(*(cmds + i), ' '));
        ft_cmdadd_back(&cmd_list, new_cmd(args));
    }
    if (cmds[i] != NULL)
    {
        printf(RED"  »  "RESET"Parse error near '|'\n\n"); // TODO: Move this to an error function
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
    cmd->exec = NULL;
    cmd->argv = args;
    if (args != NULL)
        cmd->exec =  ft_strdup(args[0]);
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
        i = -1;
        while (next->argv[++i] != NULL)
            free(next->argv[i]);
        free(next->argv);
		free(next->exec);
        //free_redir(&next->redir);
        temp = next;
        next = next->next;
        free(temp);
    }
    *list = NULL;
}
