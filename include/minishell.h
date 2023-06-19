/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonza <dangonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 15:44:08 by dangonza          #+#    #+#             */
/*   Updated: 2023/06/19 15:44:22 by dangonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h> 
# include <sys/wait.h>
# include <sys/stat.h>
# include <signal.h>

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
# define GREEN "\033[1;32m"
# define YELLOW "\033[1;33m"
# define WHITE "\033[1;37m"
# define CYAN "\033[1;36m"
*/
# define RED "\033[1;31m"
# define BLUE "\033[1;34m"
# define PURPLE "\033[1;35m"
# define RESET "\033[0;0m"

// TKN => Valid Token Characters. Norminette issues :(
# define TKN "abcdefghijklmnopqrstuvwxyz_ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789"
# define VALID_TKN_CHARS TKN
# define SINGLE_CHAR_TKN "$?-#*@!0123456789" 

# define RL_PROMPT "\033[1;35mminishell > \033[0;0m"
# define HEREDOC_PROMPT "\033[1;34mheredoc> \033[0;0m"
# define MINISHELL_ERROR "\033[1;31mminishell: \033[0;0m"

# define UNSET_INVALID "unset: '%s': not a valid identifier\n"
# define INV_TKN_MSG "syntax error near unexpected token"
# define BAD_SUBST "bad substitution\n"
# define ERROR_MALLOC "a call to malloc() did fail :(\n"
# define NO_FILE_OR_DIR "%s: No such file or directory\n"
# define IS_DIR_MSG "%s: Is a directory\n"
# define PERMISSION_DENIED_MSG "%s: Permission denied\n"
# define EXIT_MSG "exit\n"
# define EXIT_ARG_NUM_MSG "exit: %s: numeric argument required\n"
# define EXIT_NUM_ARGS_MSG "exit: too many arguments\n"
# define CMD_NOT_FOUND_MSG "%s: command not found\n"

// main.c
int			main(int argc, char **argv, char **environ);

// readline
void		rl_replace_line(const char *text, int clear_undo);

// ----------------- exec directory -----------------
// wait_result.c
int			ft_wait_result(int *pids);

// openfile.c
t_bool		ft_openfile(t_file *file);
t_file		*ft_openfiles(t_file_lst *lst);
t_bool		ft_open_all_files(t_cmd *cmd);

// run.c
void		close_fds_free(t_cmd_lst *cmd);
void		close_free_exit(t_cmd_lst *cmd, int exit_code);
t_bool		is_write_builtin(char *cmd);
void		run(t_cmd_lst *cmd, t_env_lst **envp);

// heredoc.c
t_bool		ft_handle_here_doc(t_file *file);

// get_path.c
t_bool		ft_get_path(t_cmd *cmd, t_env_lst *envp);

// builtins/exit.c
int			ft_exit(t_cmd *cmd, t_bool is_only_cmd);

// builtins/cd.c
int			ft_cd(t_cmd *cmd, t_env_lst **envp);

// builtins/unset.c
t_bool		ft_unset_variable(t_env_lst **envp, char *key);
int			ft_unset(t_cmd *cmd, t_env_lst **envp);

// builtins/export/export.c
int			ft_export(t_cmd *cmd, t_env_lst **envp, int fd);

// builtins/export/export_update.c
int			ft_export_update(char *string, t_env_lst **envp);

// builtins/echo.c
t_bool		ft_is_minus_n(char *flag);
int			ft_echo(t_cmd *cmd);

// builtins/env.c
int			ft_env(t_cmd *cmd, t_env_lst *envp, int fd);

// builtins/pwd.c
int			ft_pwd(t_cmd *cmd, t_env_lst *envp);

// builtins/builtins.c
int			get_out_file(t_cmd_lst *cmd);
void		execute_write_builtin(t_cmd_lst *cmd, t_env_lst **envp);
void		ft_builtins(t_cmd_lst *cmd_lst, t_cmd_lst *full, t_env_lst **envp);

// exe_cmd.c
int			ft_exe_cmd(t_cmd_lst *cmd_lst, t_cmd_lst *full, t_env_lst **envp);

// signals/prompt.c
void		ft_prompt_signals(void);

// signals/heredoc.c
void		ft_heredoc_signals(void);

// signals/child.c
void		ft_child_signals(void);

// pipes.c
t_bool		ft_add_pipes(t_cmd_lst *cmd);

// store_result_code.c
void		ft_store_result_code(int result_code, t_bool force);

// ----------------- parsing directory -----------------
// redirections/redirection_quote_utils.c
t_bool		contains_outside_quotes(char *str, char *c);
int			index_of_outside_quotes(char *str, char *c);

// redirections/redirection_save_utils.c
void		split_redirection(char **arg, char **redir);
t_bool		handle_redirection_argument(char **arg, char **redir);
void		get_next_redirection(char **identifier, char **leftover);
void		add_redirection_back(t_cmd **cmd, int redir_type, t_file *file);

// redirections/redirection_utils.c
t_bool		is_redirection(char *string);
int			get_redirection_type(char *redirection);
t_bool		is_valid_argument(char *string);
t_bool		create_file(t_file **file, char *identifier, int redirection_type);

// redirections/redirections.c
t_bool		fill_redirections(t_cmd **cmd);
t_bool		save_and_clear_single_arg(t_cmd **cmd,
				char *redir, size_t redir_end);
t_bool		save_redirection_single_arg(t_cmd **cmd, char *redir);
t_bool		save_redirection_double(t_cmd **cmd, char *redir, char *identf);

// environment/environment_utils.c
t_bool		is_valid_env_node(t_env *node);
void		free_env_node(void *node_raw);
char		*env_shell_level_exception(char *shell_level);
t_env_lst	*new_env_node_splitted(char *key, char *value, t_bool visible);

// environment/environment.c
void		init_zero_variable(t_env_lst **envp);
void		init_default_variables(t_env_lst **envp);
t_env_lst	*init_env(char **environ);
t_env_lst	*new_env_node(char *string, t_bool is_visible);

// input/input_utils.c
void		print_parse_error(char *str, t_bool clear);
void		print_parse_error_str(char *msg, char *str);

// input/handle_input.c
char		**get_input(void);
t_bool		is_valid_input(char *line_read);
t_cmd		*parse_command(t_env_lst *envp, char *cmd_line);

// input/handle_main_command.c
char		**add_array_front(char **array, char *element);
char		*get_main_command(char ***arguments, t_bool is_quoted);

// expansion/token_utils.c
t_bool		is_one_char_token(char *str);
t_bool		is_wrapped_token(char *str);
char		*handle_numeric_tkn(char *str, size_t *idx);
char		*expand_tkn(char *str, t_env_lst *envp, size_t *idx);

// expansion/command_expansion.c
char		*exp_home(char *str, t_env_lst *env);
char		*expand(char *str, t_env_lst *env);
char		*expand_arg(char **str_ptr, t_env_lst *envp);
t_bool		expand_file_list(t_file_lst **lst_ptr, t_env_lst *envp);
t_bool		expand_cmd(t_cmd **cmd_ptr, t_env_lst *envp);

// expansion/token_expansion.c
char		*expand_normal_tkn(char *str, t_env_lst *envp, size_t *i);
char		*expand_wrapped_tkn(char *str, t_env_lst *envp, size_t *i);
char		*expand_custom_tkn(char *str, t_env_lst *envp, size_t *i);

// expansion/handle_quotes.c
char		*dequote_all(char *str);
char		*dequote(char *str);
char		*get_next_quote(char *str, size_t *idx);

// ----------------- utils directory -----------------
// copy_all.c
int			ft_copyall(int rfd, int wfd);

// handle_str.c
t_bool		str_equals(char *a, char *b);
char		*ft_strtrim_free(char *str, char *set);
char		**clean_nulls(char **str);
void		free_str_array(char **array);

// str_utils.c
char		*join_two(char *a, char *b);
char		*join_three(char *a, char *b, char *c);
char		*ft_chardup(const char c);
char		last_char(char *str);

// kill_all_children.c
void		kill_all_children(pid_t *pids);

// is_valid_variable_name.c
t_bool		is_valid_variable_name(char *str);

// file.c
t_file		*ft_newpipefd(int fd);
t_file		*ft_newfile(char *file, t_ftype type);
t_file		*ft_new_here_doc(char *delimiter);

// split_quote_conscious.c
char		**ft_split_quote_conscious(const char *s, char split_char);

// env_variables/build_home.c
char		*build_home(t_env_lst *envp);

// env_variables/env_variables.c
char		*ft_gethome(t_env_lst *envp);
char		*ft_getenv(t_env_lst *envp, char *key);
t_bool		update_env(t_env_lst **env, char *key, char *value, t_bool vsbl);
char		**build_envp(t_env_lst *envp, t_bool persist_nulls);

// value_is_null.c
t_bool		value_is_null(char *key, t_env_lst *envp);

// arrsize.c
int			ft_arrsize(char **array);

// is.c
t_bool		is(char *set, char c);

// clean/files.c
void		ft_close_fd(int *fd);
void		ft_free_file(t_file *file);
void		ft_close_fds(t_cmd *cmd);

// clean/cmds.c
void		ft_free_array_content(char **arr);
void		ft_free_cmd(t_cmd *cmd);
void		ft_close_all_fds(t_cmd_lst *cmd);
void		ft_free_cmd_lst(t_cmd_lst *cmd);

// get.c
t_file		*get_file(t_file_lst	*lst);
t_cmd		*get_cmd(t_cmd_lst *lst);

#endif
