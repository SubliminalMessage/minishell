/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonza <dangonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 15:44:04 by dangonza          #+#    #+#             */
/*   Updated: 2023/01/11 15:24:38 by jre-gonz         ###   ########.fr       */
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

typedef t_list t_file_lst;
typedef t_list t_cmd_lst;
// typedef t_list t__lst;

/**
 * @brief Structure to store the information of a file.
 * 
 * @note When used in heredoc (<<), name is the keyword to end.
 * @note implemented in a linked list.
 */
typedef struct s_file
{
	char	*name;
	int		fd;
	t_bool	append;
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
	t_file	*in;
	/**
	 * File descriptor used as input.
	*/
	int		fd_in;
	/**
	 * Output files (Linked list).
	 * @note The pipe's fd with the output will be on the last position (if existing).
	 * @note The content is sent to the first element of this list.
	 */
	t_file	*out;
}	t_cmd;

#endif
