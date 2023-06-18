/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jre-gonz <jre-gonz@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 15:44:13 by dangonza          #+#    #+#             */
/*   Updated: 2023/06/18 22:52:40 by jre-gonz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <termios.h>

static void	disable_output(void)
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

static t_cmd_lst	*parse_command_node(t_env_lst *envp, char *input)
{
	t_cmd		*cmd;
	t_cmd_lst	*node;

	cmd = parse_command(envp, input);
	free(input);
	node = ft_lstnew(cmd);
	if (!cmd || !node)
	{
		if (g_status_code != 1)
			print_parse_error(MINISHELL_ERROR ERROR_MALLOC, false);
		if (cmd)
			ft_free_cmd(cmd);
		if (node)
			free(node);
		return (NULL);
	}
	return (node);
}

static void	minishell(t_env_lst *envp)
{
	int			i;
	char		**input;
	t_cmd_lst	*cmd_lst;
	t_cmd_lst	*node;

	cmd_lst = NULL;
	input = get_input();
	if (!input)
		return ;
	i = 0;
	while (input[i])
	{
		node = parse_command_node(envp, input[i++]);
		if (!node)
			break ;
		ft_lstadd_back(&cmd_lst, node);
	}
	if (input[i] != NULL)
	{
		ft_free_cmd_lst(cmd_lst);
		return (free(input));
	}
	free(input);
	ft_store_result_code(0, true);
	run(cmd_lst, &envp);
}

int	main(int argc, char **argv, char **environ)
{
	t_env_lst		*envp;

	(void) argc;
	(void) argv;
	envp = init_env(environ);
	disable_output();
	while (true)
		minishell(envp);
	return (0);
}
