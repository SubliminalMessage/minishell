/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonza <dangonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 15:44:04 by dangonza          #+#    #+#             */
/*   Updated: 2023/04/22 00:25:48 by dangonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H

# include <minishell.h>

typedef struct	s_env
{
	struct s_env    *next;
	char	*name;
	char	*value;
	char	*join;
} t_env;


// ------------------------------------

typedef enum e_bool
{
	false,
	true
}	t_bool;

typedef struct s_list t_file_lst;
typedef struct s_list t_cmd_lst;

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
 */
typedef struct s_cmd
{
	char	*cmd;
	char	**args;
	// char	**envp; // TODO
	/**
	 * Input files (linked list).
	 * 
	 * @note The pipe's fd with the input will be on the first position (if existing).
	 * @note All are concatenated into fd_in before execution.
	 */
	t_file_lst	*in;
	/**
	 * File descriptor used as input.
	*/
	int		fd_in;
	/**
	 * Output files (Linked list).
	 * @note The pipe's fd with the output will be on the last position (if existing).
	 * @note The content is sent to the first element of this list.
	 */
	t_file_lst	*out;
}	t_cmd;

#endif
