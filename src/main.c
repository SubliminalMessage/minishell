/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonza <dangonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 15:44:13 by dangonza          #+#    #+#             */
/*   Updated: 2023/05/29 19:12:30 by dangonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	print_file(void *file_void)
{
	t_file *file;

	// file = get_file((t_file_lst *) file_lst);
	file = (t_file *) file_void;
	if (file->type == STD_FTYPE)
		printf("(stdin/stdout)-> ");
	else if (file->type == HEREDOC_FTYPE)
		printf("(heredoc: %s)-> ", file->name);
	else
		printf("(%s)-> ", file->name);
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
	ft_lstiter(cmd->in, print_file);
	printf("(<null>);\n");

	printf("\tFiles Out: ");
	ft_lstiter(cmd->out, print_file);
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

int main(int argc, char **argv, char **environ)
{
	char        **input;
	t_env_lst   *envp;
    t_cmd_lst   *cmd_lst;
    t_cmd_lst   *node;

	(void) argc;
	(void) argv;
	envp = init_env(environ);
	if (!envp)
		return (1);
	
	// Test
	set_readline_signals();
	///////
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
			i++;
		}
		free(input);

		/////////////////////////// DEBUG ///////////////////////////

		ft_lstiter(cmd_lst, (void (*)(void *)) print_cmd);
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

		run(cmd_lst, envp);
		printf("run finished. Result code: %s\n", ft_getenv(envp, "?"));
	}
	printf("exit\n");

	// CleanUp!
	ft_lstclear(&envp, free_env_node);

	printf("!! Minishell finished without errors !!\n"); /***/ system("leaks -q minishell");
	return (0);
}
