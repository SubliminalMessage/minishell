/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jre-gonz <jre-gonz@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 15:21:27 by jre-gonz          #+#    #+#             */
/*   Updated: 2023/04/19 22:19:31 by jre-gonz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "debug_minishell.h"

/**
 * @brief Allocates and initializes a new t_file.
 * 
 * @param file
 * @param fd
 * @param type
 * @return t_file* The new t_file or NULL if an error occurred.
 */
static t_file	*ft_newtfile(char *file, int fd, t_ftype type)
{
	t_file	*f;

	f = ft_calloc(1, sizeof(t_file));
	if (!f)
		return (NULL);
	f->name = file;
	f->fd = fd;
	f->type = type;
	return (f);
}

/**
 * @brief Creates a new t_file to represent an end of a pipe.
 * @note The name is always NULL.
 * 
 * @param fd The file descriptor of the existing pipe.
 * @return t_file* The new t_file.
 */
t_file	*ft_newpipefd(int fd)
{
	return (ft_newtfile(NULL, fd, PIPE_FTYPE));
}

/**
 * @brief Creates a new t_file to represent a file.
 * @note The file is not opened. ft_openfile must be called to do so.
 * @note The name is freed if error.
 * 
 * @param file The name of the file.
 * @param type The type of the t_file.
 * @return t_file* NULL if error or name is NULL. The new t_file otherwise.
 */
t_file	*ft_newfile(char *file, t_ftype type)
{
	t_file	*f;

	if (!file)
		return (NULL);
	f = ft_newtfile(file, INVALID, type);
	if (f == NULL)
		free(file);
	return (f);
}

/**
 * @brief Creates a new t_file to represent a here_doc.
 * 
 * @param delimiter The delimiter of the here_doc.
 * @return t_file* NULL if error or name is NULL. The new t_file otherwise.
 */
t_file	*ft_new_here_doc(char *delimiter)
{
	t_file	*f;

	if (!delimiter)
		return (NULL);
	f = ft_newfile(delimiter, HEREDOC_FTYPE);
	if (f == NULL)
		free(delimiter);
	if (!ft_handle_here_doc(f))
		return (ft_free_file(f), NULL);
	return (f);
}
