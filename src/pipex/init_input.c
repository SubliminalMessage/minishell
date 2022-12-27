/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jre-gonz <jre-gonz@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 21:38:04 by jre-gonz          #+#    #+#             */
/*   Updated: 2022/12/27 09:31:59 by jre-gonz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/**
 * @brief Analyzes if here_doc is needed and readies the input file.
 * 
 * @param pipex Structure that contains the pipex info.
 * @param argv Command line arguments.
 */
void	ft_init_input(t_pipex *pipex, int *argc, char ***argv)
{
	pipex->heredoc = ft_strncmp((*argv)[1], HEREDOC, ft_strlen(HEREDOC)) == 0;
	if (pipex->heredoc)
	{
		ft_heredoc((*argv)[2], pipex);
		(*argv)++;
		*argc = *argc - 1;
		pipex->cmd_count--;
	}
	else
	{
		pipex->f_input = open((*argv)[1], O_RDONLY);
		if (pipex->f_input == -1)
			ft_end_error_file(0, pipex, (*argv)[1]);
	}
}
