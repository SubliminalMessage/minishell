/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_pipex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jre-gonz <jre-gonz@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 15:50:54 by jre-gonz          #+#    #+#             */
/*   Updated: 2022/12/27 09:32:37 by jre-gonz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/**
 * @brief Inits the pipex structure with default values.
 * It also defines the amount of cmds given by input.
 * This allows the code to end the exectution at any time usign free_end.
 *
 * @param pipex Structure that contains the pipex info.
 * @param cmd_count amount of commands to execute.
 */
static void	ft_init_structure(t_pipex *pipex, int cmd_count)
{
	pipex->f_input = -1;
	pipex->f_output = -1;
	pipex->cmds = NULL;
	pipex->env_paths = NULL;
	pipex->cmd_count = cmd_count;
	pipex->cmd_idx = 0;
	pipex->fds = NULL;
	pipex->cmd_args = NULL;
	pipex->cmd_full = NULL;
	pipex->pid = NULL;
}

/**
 * @brief Inits the pipex struct with the given argv and envp.
 * 
 * @param pipex Structure that contains the pipex info.
 * @param argc Argc variable from the main function.
 * @param argv Argv  variable from the main function.
 * @param envp Envp variable from the main function.
 */
void	ft_init_pipex(t_pipex *pipex, int argc, char **argv, char **envp)
{
	pipex->envp = envp;
	ft_init_structure(pipex, argc - 3);
	ft_init_output(pipex, argv[argc - 1]);
	ft_init_input(pipex, &argc, &argv);
	ft_init_pipes(pipex);
	pipex->pid = malloc(sizeof(int) * pipex->cmd_count);
	if (!pipex->pid)
		ft_free_end(pipex, 1, ERROR_MALLOC);
	pipex->cmds = argv + 2;
	pipex->env_paths = ft_get_path_array(envp);
	if (!pipex->env_paths)
	{
		pipex->env_paths = malloc(sizeof(char *));
		if (!pipex->env_paths)
			ft_free_end(pipex, 1, ERROR_MALLOC);
		pipex->env_paths[0] = NULL;
	}
}
