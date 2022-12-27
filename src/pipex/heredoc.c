/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jre-gonz <jre-gonz@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 16:44:16 by jre-gonz          #+#    #+#             */
/*   Updated: 2022/12/27 09:31:46 by jre-gonz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	ft_isdelimeter(char *delimeter, char *buf)
{
	int	delim_len;
	int	buf_len;

	delim_len = ft_strlen(delimeter);
	buf_len = ft_strlen(buf);
	if (delim_len + 1 != buf_len)
		return (0);
	if (ft_strncmp(delimeter, buf, delim_len))
		return (0);
	if (buf[delim_len] != '\n')
		return (0);
	return (1);
}

static void	ft_get_heredoc(char *delim, t_pipex *pipex, int f)
{
	char	*buf;

	while (1)
	{
		write(1, HEREDOC_SHELL, 9);
		buf = get_next_line(STDIN);
		if (!buf)
			ft_free_end(pipex, 1, ERROR_HEREDOC);
		if (ft_isdelimeter(delim, buf))
			break ;
		ft_putstr_fd(buf, f);
		free(buf);
	}
	free(buf);
}

void	ft_heredoc(char *delim, t_pipex *pipex)
{
	int		f;

	f = open(HEREDOC_FILE, O_CREAT | O_WRONLY | O_TRUNC, 0000644);
	if (f <= 0)
		ft_free_end(pipex, 1, ERROR_HEREDOC);
	ft_get_heredoc(delim, pipex, f);
	close(f);
	pipex->f_input = open(HEREDOC_FILE, O_RDONLY);
	if (pipex->f_input == -1)
		ft_free_end(pipex, 1, ERROR_HEREDOC);
}
