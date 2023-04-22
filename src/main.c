/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonza <dangonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 15:44:13 by dangonza          #+#    #+#             */
/*   Updated: 2023/04/22 16:42:36 by dangonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int main(void)
{
	char **input;
	t_env_lst *envp;
	extern char		**environ;

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
			t_cmd *cmd = parse_command(input[i]); // TODO: Do something with this!
			free(input[i]);
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
