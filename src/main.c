/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jre-gonz <jre-gonz@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 15:44:13 by dangonza          #+#    #+#             */
/*   Updated: 2023/04/27 21:26:05 by jre-gonz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int g_status_code;

/**
 * @brief If no output file is specified, stdout should be used.
 * @note If no ouput is specified, a new fd representing stdout is created.
 * @note The case of stdin does not need to be checked.
 * 
 * @param cmd Structure containing the command.
 * @return int false if error, true otherwise.
 */
t_bool	ft_check_output(t_cmd_lst *cmd)
{
	t_cmd		*last_cmd;
	t_file_lst	*new_fd;

	last_cmd = get_cmd(ft_lstlast(cmd));
	if (ft_lstsize(last_cmd->out) > 0)
		return (true);
	new_fd = ft_lstnew(ft_newpipefd(STDOUT));
	if (!new_fd)
		return (false);
	get_file(new_fd)->type = STD_FTYPE;
	ft_lstadd_back(&last_cmd->out, new_fd);
	return (true);
}

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
		if (!ft_check_output(cmd_lst))
		{
			printf("ha petao :(!\n");
			continue ;
		}

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
		
		g_status_code = run(cmd_lst); // Does not work if the executabe does not have the correct path :)
		printf("run finished. Result code: %d\n", g_status_code);
	}
	printf("exit\n");

	// CleanUp!
	ft_lstclear(&envp, free_env_node);

	printf("!! Minishell finished without errors !!\n"); /***/ system("leaks -q minishell");
	return (0);
}
