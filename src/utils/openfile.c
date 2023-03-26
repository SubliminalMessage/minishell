/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   openfile.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jre-gonz <jre-gonz@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 20:34:25 by jre-gonz          #+#    #+#             */
/*   Updated: 2023/03/26 20:41:59 by jre-gonz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "debug_minishell.h"

/**
 * @brief Obtains the flag to open a t_file.
 * @note The file must be a valid-not-opened file.
 * @note If the file should not be opened, it is considered invalid.
 * 
 * @param file The file to open.
 * @return int INVALID if the file is invalid or the flag to open the file.
 */
static int	ft_getopenflag(t_file *file)
{
	if (!file || file->fd != INVALID)
		return (INVALID);
	if (file->type == READ_FTYPE)
		return (O_RDONLY);
	if (file->type == TRUNC_FTYPE)
		return (O_WRONLY | O_CREAT | O_TRUNC);
	if (file->type == APPEND_FTYPE)
		return (O_WRONLY | O_CREAT | O_APPEND);
	return (INVALID);
}

/**
 * @brief Opens a t_file.
 * 
 * @param file The file to open.
 * @return t_bool TRUE if the file was opened successfully. FALSE otherwise.
 */
t_bool	ft_openfile(t_file *file)
{
	int	flag;

	flag = ft_getopenflag(file);
	if (flag == INVALID)
		return (FALSE);
	file->fd = open(file, flag);
	return (file->fd != INVALID);
}