/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   openfile.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jre-gonz <jre-gonz@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 20:34:25 by jre-gonz          #+#    #+#             */
/*   Updated: 2023/04/19 22:51:31 by jre-gonz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/**
 * @brief Opens a t_file.
 * 
 * @param file The file to open.
 * @return t_bool true if the file was opened successfully. false otherwise.
 */
t_bool	ft_openfile(t_file *file)
{
	if (!file || file->fd != INVALID)
		return (false);
	if (file->type == READ_FTYPE)
		file->fd = open(file->name, O_RDONLY);
	else if (file->type == TRUNC_FTYPE)
		file->fd = open(file->name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (file->type == APPEND_FTYPE)
		file->fd = open(file->name, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		return (false);
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