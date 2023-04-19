/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_minishell.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jre-gonz <jre-gonz@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 08:10:11 by jre-gonz          #+#    #+#             */
/*   Updated: 2023/04/19 22:35:23 by jre-gonz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEBUG_MINISHELL_H
# define DEBUG_MINISHELL_H


# include <minishell.h>

# define INVALID -1

// Clean_cmd.c
void	ft_close_fd(int *fd);
void	ft_free_file(t_file	*file);
void	ft_free_cmd(t_cmd	*cmd);
void	ft_close_all_fds(t_cmd_lst	*cmd);
void	ft_free_cmd_lst(t_cmd_lst	*cmd);

// get
t_file	*get_file(t_file_lst	*lst);
t_cmd	*get_cmd(t_cmd_lst	*lst);

// file
t_file	*ft_newpipefd(int fd);
t_file	*ft_newfile(char *file, t_ftype type);
t_file	*ft_new_here_doc(char *delimiter);

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

// openfile.c
t_bool	ft_openfile(t_file *file);
t_file	*ft_openfiles(t_file_lst *lst);
t_bool	ft_open_all_files(t_cmd *cmd);

// heredoc.c
t_bool	ft_handle_here_doc(t_file *file);

#endif
