/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonza <dangonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 15:44:08 by dangonza          #+#    #+#             */
/*   Updated: 2023/04/21 18:45:34 by dangonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <debug.h> // TODO This is not meant to get into the final version of the Minishell

# include <unistd.h>
# include <stdlib.h>
# include <libft.h>
// # include <libc.h> // TODO In mac, this may be needed

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

# include <fcntl.h> // Open, close
# include <sys/wait.h> // fork, WEXITSTATUS


// Custom headers

# include <libft.h>
# include <structures.h>

// Custom defines

# define STDIN 0
# define STDOUT 1
# define STDERR 2

/**
 * @brief The value of something not valid.
 * @note This is helpful in cases where 0 is a valid value.
 * @note Used mainly to denote a non-existing file descriptor.
 */
# define INVALID -1

// Colors: https://www.darklaunch.com/print-terminal-colors.html
# define RED "\033[1;31m"
# define GREEN "\033[1;32m"
# define PURPLE "\033[1;35m"
# define YELLOW "\033[1;33m"
# define WHITE "\033[1;37m"
# define BLUE "\033[1;34m"
# define CYAN "\033[1;36m"
# define RESET "\033[0;0m"


# define INVALID_TOKEN "minishell: syntax error near unexpected token `%c'\n" // TODO refactor with style from minishell
# define ERROR_MALLOC "minishell: a call to malloc() did fail :(\n"
# define NO_FILE_OR_DIR "minishell: %s: No such file or directory" // TODO refactor with style from minishell
# define HEREDOC_PROMPT "heredoc> " // TODO refactor with style from minishell

// CWD Max String Size
# define CWD_SIZE 1000

// All the functions
// ----------------- ?? directory -----------------
// TODO: Group them by file
char	**get_input(void);
t_bool is_valid_input(char *line_read);
t_bool str_equals(char* a, char* b);
char *join_three(char *a, char *b, char *c);
char	**ft_split_quote_conscious(const char *s, char split_char);
char **clean_nulls(char **str);
void execute_line(char *line);
t_env   *new_env(char *str);
void	ft_envadd_back(t_env **lst, t_env *new);
void    free_environ(t_env **env_list);
t_env   *init_environ(void);
void    update_env(t_env **list, char *name, char *new_value);
char    *ft_getenv(char *name, t_env *list);
char *ft_strtrim_free(char *str, char *set);
char	*ft_chardup(const char c);
void	ft_cmdadd_back(t_command **lst, t_command *new);
void free_cmd(t_command **list);
t_command *new_cmd(char **args);
t_command   *parse_commands(char **cmds);
void    free_str_array(char **array);

// ----------------- exec directory -----------------

// exe_cmd.c
int	ft_exe_cmd(t_cmd_lst	*cmd_lst, t_cmd_lst *full);

// heredoc.c
t_bool	ft_handle_here_doc(t_file *file);

// join_input.c
int	ft_join_input(t_cmd	*cmd);

// openfile.c
t_bool	ft_openfile(t_file *file);
t_file	*ft_openfiles(t_file_lst *lst);
t_bool	ft_open_all_files(t_cmd *cmd);

// pipes.c
int		*ft_create_pipes(int amount_cmds);
t_bool	ft_add_pipes(t_cmd_lst *cmd, int *fds);

// run.c
int	run(t_cmd_lst *cmd);

// wait_result.c
int	ft_wait_result(int *pids);

// ----------------- utils directory -----------------
// TODO

// Clean_cmd.c
void	ft_close_fd(int *fd);
void	ft_free_file(t_file	*file);
void	ft_free_cmd(t_cmd	*cmd);
void	ft_close_all_fds(t_cmd_lst	*cmd);
void	ft_free_cmd_lst(t_cmd_lst	*cmd);

// copy_all.c
int	ft_copyall(int rfd, int wfd);

// file.c
t_file	*ft_newpipefd(int fd);
t_file	*ft_newfile(char *file, t_ftype type);
t_file	*ft_new_here_doc(char *delimiter);

// get.c
t_file	*get_file(t_file_lst	*lst);
t_cmd	*get_cmd(t_cmd_lst	*lst);

#endif
