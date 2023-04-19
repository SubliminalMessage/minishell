/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jre-gonz <jre-gonz@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 15:44:04 by dangonza          #+#    #+#             */
/*   Updated: 2023/04/19 22:31:06 by jre-gonz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H

# include <minishell.h>

// ! TODO Remove when new version is implemented
typedef struct	s_redirs // TODO: there's work to be done here...
{
	char *in;		// Either "<" or "<<". If NULL, no redirection. Use str_equals() to compare.
	char *out;		// Either ">" or ">>". If NULL, no redirection.
	char *file_in;	// Null by default. If not null, it's the file to read from.
	char *file_out;	// Null by default. If not null, it's the file to write to.
} t_redirs;

// ! TODO Remove when new version is implemented
typedef struct	s_command
{
	struct s_command	*next;
	char		*exec;
	char		**argv; // argv[0] is the command; but if given as a path, should it be the whole path?
	t_redirs	*redirs; // If NULL, no redirs.
}	t_command;

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
