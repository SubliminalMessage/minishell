/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonza <dangonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 15:44:08 by dangonza          #+#    #+#             */
/*   Updated: 2023/05/29 19:19:31 by dangonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <libft.h>
// # include <libc.h> // TODO In mac, this may be needed

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>

# include <fcntl.h> // Open, close
# include <sys/wait.h> // fork, WEXITSTATUS
# include <sys/stat.h> // stat
 #include <signal.h> // kill

// Custom headers

# include <libft.h>
# include <structures.h>

// Global Variable
int	g_status_code;

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
/*
# define RED "\033[1;31m"
# define GREEN "\033[1;32m"
# define PURPLE "\033[1;35m"
# define YELLOW "\033[1;33m"
# define WHITE "\033[1;37m"
# define BLUE "\033[1;34m"
# define CYAN "\033[1;36m"
# define RESET "\033[0;0m"
*/

// TKN => Valid Token Characters. Norminette issues :(
# define TKN "abcdefghijklmnopqrstuvwxyz_ABCDEFGHIJKLMNOPQRSTUVWXY0123456789"
# define VALID_TKN_CHARS TKN
// $_ is not considered SingleCharToken, because '$_a' is a valid one
# define SINGLE_CHAR_TKN "$?-#*@!0123456789" 

// TODO: Refactor DEFINES with style from minishell
# define INV_TKN_MSG "minishell: syntax error near unexpected token"
# define BAD_SUBST "minishell: bad substitution\n"
# define ERROR_MALLOC "minishell: a call to malloc() did fail :(\n"
# define NO_FILE_OR_DIR "minishell: %s: No such file or directory"
# define HEREDOC_PROMPT "heredoc> "
# define RL_PROMPT "minishell > "
# define IS_DIR_MSG "minishell: %s: Is a directory\n"
# define PERMISSION_DENIED_MSG "minishell: %s: Permission denied\n"
# define EXIT_MSG "exit\n"
# define EXIT_ARG_NUM_MSG "exit: %s: numeric argument required\n"
# define EXIT_NUM_ARGS_MSG "exit: too many arguments\n"
# define CMD_NOT_FOUND_MSG "minishell: %s: command not found\n"

// CWD Max String Size
//# define CWD_SIZE 1000
# define DEL_SIG "\b\b\033[K"

void	rl_replace_line(const char *text, int clear_undo);
void	set_readline_signals(void);
void	set_heredoc_signals(void);

// All the functions
// ----------------- parsing directory -----------------

// environment/environment_utils.c
t_bool		is_valid_env_node(t_env *node);
void		free_env_node(void *node_raw);
char		*env_shell_level_exception(char *shell_level);
t_env_lst	*new_env_node_splitted(char *key, char *value, t_bool visible);

// environment/environment.c
void		init_zero_variable(t_env_lst **envp);
t_env_lst	*init_env(char **environ);
t_env_lst	*new_env_node(char *string, t_bool is_visible);

// expansion/command_expansion.c
char		*expand(char *str, t_env_lst *env);
char		*expand_arg(char **str_ptr, t_env_lst *envp);
t_bool		expand_file_list(t_file_lst **lst_ptr, t_env_lst *envp);
t_bool		expand_cmd(t_cmd **cmd_ptr, t_env_lst *envp);

// expansion/handle_quotes.c
char		*dequote(char *str);
char		*get_next_quote(char *str, size_t *idx);

// expansion/token_expansion.c
char		*expand_normal_tkn(char *str, t_env_lst *envp, size_t *i);
char		*expand_wrapped_tkn(char *str, t_env_lst *envp, size_t *i);
char		*expand_custom_tkn(char *str, t_env_lst *envp, size_t *i);

// expansion/token_utils.c
t_bool		is_one_char_token(char *str);
t_bool		is_wrapped_token(char *str);
char		*handle_numeric_tkn(char *str, size_t *idx);
char		*expand_tkn(char *str, t_env_lst *envp, size_t *idx);

// input/handle_input.c
char		**get_input(void);
t_bool		is_valid_input(char *line_read);
t_cmd		*parse_command(t_env_lst *envp, char *cmd_line);

// input/input_utils.c
void		print_parse_error(char *str, t_bool clear);
void		print_parse_error_str(char *msg, char *str);

// redirections/redirection_utils.c
t_bool		is_redirection(char *string);
int			get_redirection_type(char *redirection);
t_bool		is_valid_argument(char *string);
t_bool		create_file(t_file **file, char *identifier, int redirection_type);
t_bool		contains_outside_quotes(char *str, char *c);
int			index_of_outside_quotes(char *str, char *c);

// redirections/redirections.c
t_bool		fill_redirections(t_cmd **cmd);
t_bool		save_redirection(t_cmd **cmd, char **first_arg, char **second_arg);
t_bool		save_redirection_single_arg(t_cmd **cmd, char *redir);
t_bool		save_redirection_double(t_cmd **cmd, char *redir, char *identifier);

// ----------------- exec directory -----------------

// builtins/exit.c
int			ft_exit(t_cmd *cmd);

// builtins/echo.c
int			ft_echo(t_cmd *cmd);

// builtins/builtins.c
void		ft_builtins(t_cmd *cmd, t_cmd_lst *full);

t_bool	ft_check_output(t_cmd_lst *cmd); // TODO find place

// exe_cmd.c
int			ft_exe_cmd(t_cmd_lst *cmd_lst, t_cmd_lst *full, t_env_lst *envp);

// get_path.c
t_bool		ft_get_path(t_cmd *cmd, t_env_lst *envp);

// heredoc.c
t_bool		ft_handle_here_doc(t_file *file);

// openfile.c
t_bool		ft_openfile(t_file *file);
t_file		*ft_openfiles(t_file_lst *lst);
t_bool		ft_open_all_files(t_cmd *cmd);

// pipes.c
t_bool	ft_add_pipes(t_cmd_lst *cmd);

// ready_input.c
t_bool		ft_ready_input(t_cmd *cmd);

// run.c
void		run(t_cmd_lst *cmd, t_env_lst *envp);

// wait_result.c
int			ft_wait_result(int *pids);

// ----------------- utils directory -----------------

// clean/cmds.c
void		ft_free_array_content(char **arr);
void		ft_free_cmd(t_cmd *cmd);
void		ft_close_all_fds(t_cmd_lst *cmd);
void		ft_free_cmd_lst(t_cmd_lst *cmd);

// clean/files.c
void		ft_close_fd(int *fd);
void		ft_free_file(t_file *file);
void		ft_close_fds(t_cmd *cmd);

// copy_all.c
int			ft_copyall(int rfd, int wfd);

// env_variables.c
char		*ft_getenv(t_env_lst *envp, char *key);
t_bool		update_env(t_env_lst **env, char *key, char *value, t_bool vsbl);
char		**build_envp(t_env_lst *envp);

// file.c
t_file		*ft_newpipefd(int fd);
t_file		*ft_newfile(char *file, t_ftype type);
t_file		*ft_new_here_doc(char *delimiter);

// get.c
t_file		*get_file(t_file_lst	*lst);
t_cmd		*get_cmd(t_cmd_lst *lst);

// handle_str.c
t_bool		str_equals(char *a, char *b);
char		*ft_strtrim_free(char *str, char *set);
char		**clean_nulls(char **str);
void		free_str_array(char **array);

// spit_quote_conscious.c
char		**ft_split_quote_conscious(const char *s, char split_char);

// str_utils.c
char		*join_two(char *a, char *b);
char		*join_three(char *a, char *b, char *c);
char		*ft_chardup(const char c);
char		last_char(char *str);

// todo

void	split_redirection(char **arg, char **redir);
t_bool	handle_redirection_argument(char **arg, char **redir);
void	get_next_redirection(char **identifier, char **leftover);
void	add_redirection_back(t_cmd **cmd, int redir_type, t_file *file);


#endif
