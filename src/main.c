/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonza <dangonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 15:44:13 by dangonza          #+#    #+#             */
/*   Updated: 2023/06/15 16:43:32 by dangonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <termios.h>

int	g_status_code; // TODO linux

void	disable_output(void)
{
	int				x;
	struct termios	termios;

	x = tcgetattr(0, &termios);
	if (x)
	{
		perror("");
		exit(1);
	}
	termios.c_lflag &= ~ECHOCTL;
	x = tcsetattr(0, 0, &termios);
	if (x)
	{
		perror("");
		exit(1);
	}
}

t_cmd_lst	*parse_command_node(t_env_lst *envp, char *input)
{
	t_cmd		*cmd;
	t_cmd_lst	*node;

	cmd = parse_command(envp, input);
	free(input);
	node = ft_lstnew(cmd);
	if (!cmd || !node)
	{
		if (g_status_code != 1)
			print_parse_error(ERROR_MALLOC, false);
		if (cmd)
			ft_free_cmd(cmd);
		if (node)
			free(node);
		return (NULL);
	}
	return (node);
}

int	main(int argc, char **argv, char **environ)
{
	char			**input;
	t_env_lst		*envp;
	t_cmd_lst		*cmd_lst;
	t_cmd_lst		*node;

	(void) argc;
	(void) argv;
	envp = init_env(environ);
	disable_output();
	while (true)
	{
		cmd_lst = NULL;
		input = get_input();
		if (!input)
			continue ;
		int i = 0;
		while (input[i])
		{
			node = parse_command_node(envp, input[i]);
			if (!node)
				break ;
			ft_lstadd_back(&cmd_lst, node);
			i++;
		}
		if (input[i] != NULL)
		{
			free(input);
			ft_free_cmd_lst(cmd_lst);
			continue ;
		}
		free(input);
		ft_store_result_code(0, true);
		run(cmd_lst, &envp);
	}
	return (0);
}
