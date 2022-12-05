/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonza <dangonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 15:44:08 by dangonza          #+#    #+#             */
/*   Updated: 2022/12/01 22:21:21 by dangonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <libft.h>

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

#include <structures.h>

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

# define PROMPT_BEFORE WHITE"﴾"PROMPT_CWD"  "
# define PROMPT_AFTER WHITE"  ﴿  "PROMPT_ACT"»  "RESET

// CWD Max String Size
# define CWD_SIZE 1000

// prompt.c
char    *get_full_cwd(void);
char    *get_prompt_cwd(void);
char    *get_displayable_prompt(void);
bool	prompt(void);

// handle_str.c
bool strEquals(char* a, char* b);
char *join_three(char *a, char *b, char *c);

char	**ft_split_cmds(const char *s);
void   print_cmds(char *raw);
void execute_line(char *line);

#endif