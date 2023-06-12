/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jre-gonz <jre-gonz@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 22:06:49 by jre-gonz          #+#    #+#             */
/*   Updated: 2023/06/12 18:45:34 by jre-gonz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

extern int	g_status_code; // TODO linux

/**
 * @brief Checks if the given buffer is the heredoc delimeter.
 * 
 * @param delimeter The string to compare.
 * @param buf The buffer to compare.
 * @return t_bool true if the buffer is the delimeter, false otherwise.
 */
static t_bool	ft_isdelimeter(char *delimeter, char *buf)
{
	int	delim_len;
	int	buf_len;

	if (!delimeter || !buf)
		return (false);
	delim_len = ft_strlen(delimeter);
	buf_len = ft_strlen(buf);
	if (delim_len + 1 != buf_len)
		return (false);
	if (ft_strncmp(delimeter, buf, delim_len))
		return (false);
	if (buf[delim_len] != '\n')
		return (false);
	return (true);
}

/**
 * @brief Ask the user for the heredoc content and store it in a pipe
 * 
 * @param file t_file to store the content.
 * @return t_bool true if success, false if error.
 */
t_bool	ft_handle_here_doc(t_file *file)
{
	int		p[2];
	char	*line;
	int		loop_count;

	if (pipe(p) == -1)
		return (false);
	ft_heredoc_signals();
	loop_count = 0;
	while (g_status_code != 1 || loop_count == 0)
	{
		if (loop_count == 0 && g_status_code == 1)
			ft_store_result_code(0, true);
		ft_putstr_fd(HEREDOC_PROMPT, STDOUT);
		line = get_next_line(STDIN);
		if (!line || ft_isdelimeter(file->name, line))
		{
			if (line)
				free(line);
			break ;
		}
		ft_putstr_fd(line, p[1]);
		free(line);
		loop_count++;
	}
	ft_close_fd(&p[1]);
	file->fd = p[0];
	if (g_status_code != 1)
		return (true);
	return (false);
}
