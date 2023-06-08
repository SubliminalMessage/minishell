/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonza <dangonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 15:44:04 by dangonza          #+#    #+#             */
/*   Updated: 2023/06/08 16:38:01 by dangonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H

# include <minishell.h>

typedef enum e_bool
{
	false,
	true
}	t_bool;

typedef struct s_env
{
	char	*key;
	char	*value;
	t_bool	is_visible;
}	t_env;

typedef struct s_list	t_env_lst;
typedef struct s_list	t_file_lst;
typedef struct s_list	t_cmd_lst;

/**
 * @brief The type of file in a t_file structure.
 * 
 * @note APPEND_FTYPE: Append to the output file.
 * @note TRUNC_FTYPE: Truncate the output file.
 * @note READ_FTYPE: Read from the input file.
 * @note PIPE_FTYPE: Pipe between commands (both in or out).
 * @note STD_FTYPE: stdin, stdout or stderr.
 * @note HEREDOC_FTYPE: Heredoc (<<).
 */
typedef enum e_ftype
{
	APPEND_FTYPE,
	TRUNC_FTYPE,
	READ_FTYPE,
	PIPE_FTYPE,
	STD_FTYPE,
	HEREDOC_FTYPE
}	t_ftype;

/**
 * @brief Structure to store the information of a file.
 * 
 * @note When used in heredoc (<<), name is the keyword to end.
 * @note implemented as a linked list.
 */
typedef struct s_file
{
	char	*name;
	int		fd;
	t_ftype	type;
}			t_file;

/**
 * @brief Structure responsible for storing all the data needed to execute 
 * a command.
 * 
 * @note implemented in a linked list.
 *
 * t_file_ls *in -> Input files (linked list). The whole collection 
 * of fds to consider for the fd_in.
 * 
 * @note If no pipe as input, All are concatenated into fd_in.
 * @note If pipe as input, the last element is used.
 * 
 * t_file_lst *out -> Output files (Linked list).
 * @note The pipe's fd with the output will be on the last position 
 *       (if existing).
 * @note The content is sent to the last element of this list.
 */
typedef struct s_cmd
{
	char		*cmd;
	char		**args;
	t_file_lst	*in;
	t_file_lst	*out;
}	t_cmd;

#endif
