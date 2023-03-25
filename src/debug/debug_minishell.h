/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_minishell.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jre-gonz <jre-gonz@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 08:10:11 by jre-gonz          #+#    #+#             */
/*   Updated: 2023/03/25 20:32:39 by jre-gonz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEBUG_MINISHELL_H
# define DEBUG_MINISHELL_H

# include "libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h> // Open, close
# include <sys/wait.h> // fork, WEXITSTATUS

typedef enum e_bool
{
	false,
	true
}	t_bool;

# define INVALID -1

typedef struct s_list t_file_lst;
typedef struct s_list t_cmd_lst;

/**
 * @brief The type of file in a t_file structure.
 */
typedef enum e_ftype
{
	APPEND_FTYPE,
	TRUNC_FTYPE,
	READ,
	PIPE,
	STD // stdin, stdout, stderr
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

// Clean
void	ft_close_fd(int *fd);
void	ft_free_file(t_file	*file);
void	ft_free_cmd(t_cmd	*cmd);
void	ft_close_all_fds(t_cmd_lst	*cmd);
void	ft_free_cmd_lst(t_cmd_lst	*cmd);

// get
t_file	*get_file(t_file_lst	*lst);
t_cmd	*get_cmd(t_cmd_lst	*lst);

// file
t_file	*ft_newfile(char *file, t_ftype type, int opentype);
t_file	*openfile(char *file);
t_file	*ft_newpipefd(int fd);

// wait_result.c
int	ft_wait_result(int *pids);

// join_input.c
int	ft_join_input(t_cmd	*cmd);

// exe_cmd.c
int	ft_exe_cmd(t_cmd_lst	*cmd_lst, t_cmd_lst *full);

// copy_all.c
int	ft_copyall(int rfd, int wfd);

// run.c
int	run(t_cmd_lst *cmd);

#endif
