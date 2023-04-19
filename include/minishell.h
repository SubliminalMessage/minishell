/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jre-gonz <jre-gonz@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 15:44:08 by dangonza          #+#    #+#             */
/*   Updated: 2023/04/19 22:34:44 by jre-gonz         ###   ########.fr       */
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

// Colors: https://www.darklaunch.com/print-terminal-colors.html
# define RED "\033[1;31m"
# define GREEN "\033[1;32m"
# define PURPLE "\033[1;35m"
# define YELLOW "\033[1;33m"
# define WHITE "\033[1;37m"
# define BLUE "\033[1;34m"
# define CYAN "\033[1;36m"
# define RESET "\033[0;0m"

# define PROMPT_CWD "\033[38;5;169m"
# define PROMPT_ACT "\033[38;5;24m"
# define PROMPT_RESET "\033[1;0m"

/**
 * @brief Max length of the pwd in the prompt. If bigger,
 * the prompt is reduced (if possible).
 */
# define PROMPT_MAX_FULL_LEN 15
# define PROMPT_BEFORE WHITE"﴾  "PROMPT_CWD
# define PROMPT_AFTER WHITE"  ﴿  "PROMPT_ACT"»  "RESET

# define NO_FILE_OR_DIR "minishell: %s: No such file or directory" // TODO refactor with style from minishell
# define HEREDOC_PROMPT "heredoc> " // TODO refactor with style from minishell

// CWD Max String Size
# define CWD_SIZE 1000

// All the functions
// TODO: Group them by file
char    *get_full_cwd(void);
char    *get_prompt_cwd(t_env *env_list);
char    *get_displayable_prompt(t_env *env_list);
t_bool	prompt(t_env **env_list);
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

#endif
