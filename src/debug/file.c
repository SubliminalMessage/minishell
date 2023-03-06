/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jre-gonz <jre-gonz@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 15:21:27 by jre-gonz          #+#    #+#             */
/*   Updated: 2023/03/06 15:22:34 by jre-gonz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "debug_minishell.h"

t_file	*ft_newfile(char *file, t_ftype type, int opentype)
{
	t_file	*f;

	f = ft_calloc(1, sizeof(t_file));
	if (!f)
		return (NULL);
	f->name = file;
	f->type = type;
	f->fd = open(file, opentype);
	if (f->fd == -1)
	{
		ft_free_file(f);
		return (NULL);
	}
	return (f);
}

t_file	*openfile(char *file)
{
	return (ft_newfile(file, READ, O_RDONLY));
}

t_file	*ft_newpipefd(int fd)
{
	t_file	*f;

	f = ft_calloc(1, sizeof(t_file));
	if (!f)
		return (NULL);
	// name is NULL with calloc
	f->type = PIPE;
	f->fd = fd;
	return (f);
}
