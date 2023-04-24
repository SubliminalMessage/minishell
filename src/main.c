/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonza <dangonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 15:44:13 by dangonza          #+#    #+#             */
/*   Updated: 2023/04/24 22:59:51 by dangonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	print_cmd(t_cmd *cmd)
{
	printf("\n\n[CMD]:\n");
	if (!cmd)
	{
		printf("\t(null)\n");
		return ;
	}
    printf("\tExec: ·%s·\n", cmd->cmd);
	printf("\tArgs: [");
	int i = 0;
	while (cmd->args[i] && cmd->args[i + 1])
	{
		printf("·%s·, ", cmd->args[i]);
		i++;
	}
	printf("·%s·];\n", cmd->args[i]);

	printf("\tFiles In:  ");
	t_file_lst *node_in = cmd->in;
	while (node_in)
	{
		printf("(%s)-> ", ((t_file *)node_in->content)->name);
		node_in = node_in->next;
	}
	printf("(<null>);\n");

	printf("\tFiles Out: ");
	t_file_lst *node_out = cmd->out;
	while (node_out)
	{
		printf("(%s)-> ", ((t_file *)node_out->content)->name);
		node_out = node_out->next;
	}
	printf("(<null>);\n\n");
}

t_cmd_lst   *parse_command_node(t_env_lst *envp, char *input)
{
    t_cmd   *cmd;
    t_cmd_lst   *node;

    cmd = parse_command(envp, input);
    free(input);
    node = ft_lstnew(cmd);
    if (!cmd || !node)
    {
        print_parse_error(ERROR_MALLOC, false);
        if (cmd)
            ft_free_cmd(cmd);
        if (node)
            free(node);
        return (NULL);
    }
    return (node);
}

int main(void)
{
	char        **input;
	t_env_lst   *envp;
    t_cmd_lst   *cmd_lst;
    t_cmd_lst   *node;

	envp = init_env();
	if (!envp)
		return (1);
	
	while (true)
	{
        cmd_lst = NULL;
		input = get_input();
		if (!input)
			continue;
		int i = 0;
		while (input[i])
		{
            node = parse_command_node(envp, input[i]);
            if (!node)
                break ;
            ft_lstadd_back(&cmd_lst, node);
			//////// DEBUG ////////
			/**/print_cmd(node->content);/**/
			//////// DEBUG ////////
			i++;
		}
		free(input);

        /////////////////////////// DEBUG ///////////////////////////
        t_cmd_lst *lst = cmd_lst;
        int x = 0;
        printf("CMDS: \n");
        while (lst)
        {
            t_cmd *cmd_node = lst->content;
            printf("\t:: [%d] -> ·%s·\n", x, cmd_node->cmd);
            x++;
            lst = lst->next;
        }
        printf("\n\n");
        /////////////////////////// DEBUG ///////////////////////////
        
        //run(cmd_lst); // Does not work :)

        ft_free_cmd_lst(cmd_lst);
	}
	printf("exit\n");

	// CleanUp!
	ft_lstclear(&envp, free_env_node);

	printf("!! Minishell finished without errors !!\n"); /***/ system("leaks -q minishell");
	return (0);
}
