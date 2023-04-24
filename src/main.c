/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonza <dangonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 15:44:13 by dangonza          #+#    #+#             */
/*   Updated: 2023/04/24 15:07:09 by dangonza         ###   ########.fr       */
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

int main(void)
{
	char **input;
	t_env_lst *envp;

	envp = init_env();
	if (!envp)
		return (1);
		
	while (true)
	{
		input = get_input();
		if (!input)
			continue;
		int i = 0;
		while (input[i])
		{
			t_cmd *cmd = parse_command(envp, input[i]); // TODO: Do something with this!
			free(input[i]);
			//////// DEBUG ////////
			/**/print_cmd(cmd);/**/
			//////// DEBUG ////////
			ft_free_cmd(cmd);
			i++;
		}
		free(input);
	}
	printf("exit\n");

	// CleanUp!
	ft_lstclear(&envp, free_env_node);

	printf("!! Minishell finished without errors !!\n"); /***/ system("leaks -q minishell");
	return (0);
}
