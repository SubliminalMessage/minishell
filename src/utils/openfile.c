/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   openfile.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jre-gonz <jre-gonz@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 20:34:25 by jre-gonz          #+#    #+#             */
/*   Updated: 2023/04/18 21:44:22 by jre-gonz         ###   ########.fr       */
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
 * @return t_bool true if the file was opened successfully. false otherwise.
 */
t_bool	ft_openfile(t_file *file)
{
	int	flag;

	flag = ft_getopenflag(file);
	if (flag == INVALID)
		return (false);
	file->fd = open(file->name, flag);
	return (file->fd != INVALID);
}

/**
 * @brief Opens the files in the list.
 * @note The pipe files and the heredocs are already opened.
 * 
 * @param lst List of files.
 * @return t_file* NULL if ok, the file with the error otherwise.
 */
t_file	*ft_openfiles(t_file_lst *lst)
{
	t_file	*file;

	if (!lst)
		return (NULL);
	file = get_file(lst);
	if (file->fd == INVALID && !ft_openfile(file))
		return (file);
	return (ft_openfiles(lst->next));
}

#define NO_FILE_OR_DIR "minishell: %s: No such file or directory" // TODO refactor and move

/**
 * @brief Opens all the files in the command.
 * TODO use perror
 * 
 * @param cmd The command.
 * @return t_bool false if not able to open all, true otherwise.
 */
t_bool	ft_open_all_files(t_cmd *cmd)
{
	t_file	*file;

	file = ft_openfiles(cmd->in);
	if (file)
		return (ft_printf_fd(2, NO_FILE_OR_DIR, file->name), false);
	file = ft_openfiles(cmd->out);
	if (file)
		return (ft_printf_fd(2, NO_FILE_OR_DIR, file->name), false);
	return (true);
}