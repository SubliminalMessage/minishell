/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jre-gonz <jre-gonz@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 10:54:36 by jre-gonz          #+#    #+#             */
/*   Updated: 2022/12/27 09:29:26 by jre-gonz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/**
 * @brief Checks that the given arguments are valid.
 * Also detects if heredoc present (1 if heredoc, 0 else).
 * min cases:
 *   no here_doc: pipex file.in cmd1 cmd2 outfile -> argc == 5
 *      here_doc: pipex heredoc end cmd1 cmd2 outfile -> argc == 6
 * @param argc Argc from the main function.
 * @param argv Argv from the main function.
 * @returns 1 if valid, 0 otherwise. 
 */
int	ft_check_arg(int argc, char **argv, int *heredoc)
{
	if (argc < 5)
		return (0);
	*heredoc = 0;
	if (!ft_strncmp(argv[1], HEREDOC, ft_strlen(HEREDOC)))
	{
		*heredoc = 1;
		if (argc < 6)
			return (0);
	}
	return (1);
}
