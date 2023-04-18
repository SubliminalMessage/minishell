/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jre-gonz <jre-gonz@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 22:06:49 by jre-gonz          #+#    #+#             */
/*   Updated: 2023/04/18 22:34:31 by jre-gonz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "debug_minishell.h"

t_bool	ft_isdelimeter(char *delimeter, char *buf)
{
	int	delim_len;
	int	buf_len;

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

t_bool	ft_handle_here_doc(t_file *file)
{
	int		p[2];
	char	*line;

	if (pipe(p) == -1)
		return (false);
	ft_printf_fd(2, "Here doc pipe: %d, %d\n", p[0], p[1]);
	ft_printf_fd(2, "heredoc end: '%s'\n", file->name);
	while (true)
	{
		ft_putstr_fd("heredoc> ", STDOUT);
		line = get_next_line(STDIN); // TODO ft_
		// TODO leaks
		if (!line)
			return (false); // TODO handle error
		if (ft_isdelimeter(file->name, line))
		{
			free(line);
			break ;
		}
		ft_putendl_fd(line, p[1]);
		free(line);
	}
	ft_close_fd(&p[1]);
	file->fd = p[0];
	return (true);
}

t_bool	ft_handle_here_doc_lst(t_cmd_lst *cmd_lst)
{ // TODO remove and add heredoc directly when creating a file
	t_cmd_lst	*cmd;
	t_cmd		*c;
	t_file_lst	*file;
	t_file		*f;

	cmd = cmd_lst;
	while (cmd)
	{
		c = get_cmd(cmd);
		file = c->in;
		while (file)
		{
			f = get_file(file);
			if (f->type == HEREDOC_FTYPE)
			{
				if (!ft_handle_here_doc(f))
					return (false);
			}
			file = file->next;
		}
		cmd = cmd->next;
	}


	return (true);
}