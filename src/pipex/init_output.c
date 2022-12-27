/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_output.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jre-gonz <jre-gonz@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 21:42:26 by jre-gonz          #+#    #+#             */
/*   Updated: 2022/12/27 09:32:17 by jre-gonz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/**
 * @brief Having in mind heredoc, it readies the output file to be used.
 * 
 * @param pipex Structure that contains the pipex info.
 * @param path Path to the output file.
 */
void	ft_init_output(t_pipex *pipex, char *path)
{
	pipex->f_output = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0000644);
	if (pipex->f_output == -1)
		ft_end_error_file(1, pipex, path);
}
