/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_minishell.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jre-gonz <jre-gonz@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 08:10:11 by jre-gonz          #+#    #+#             */
/*   Updated: 2023/01/19 09:20:48 by jre-gonz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEBUG_MINISHELL_H
# define DEBUG_MINISHELL_H

# include "libft.h"
# include <stdlib.h>

typedef struct s_list t_file_lst;
typedef struct s_list t_cmd_lst;

/**
 * @brief The type of file in a t_file structure.
 */
typedef enum e_ftype
{
	APPEND_FTYPE,
	TRUNC_FTYPE,
}	t_ftype;

/**
 * @brief Structure to store the information of a file.
 * 
 * @note When used in heredoc (<<), name is the keyword to end.
 * @note implemented as a linked list.
 */
typedef struct s_file
{
	struct s_file	*next;
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
	// char	*cmd; // TODO
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
