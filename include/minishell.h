#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <libft.h>

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

// Colors:
# define RED "\033[1;31m"
# define GREEN "\033[1;32m"
# define PURPLE "\033[1;35m"
# define YELLOW "\033[1;33m"
# define WHITE "\033[1;37m"
# define BLUE "\033[1;34m"
# define CYAN "\033[1;36m"
# define RESET "\033[0;0m"

// CWD Max String Size
# define CWD_SIZE 1000

// prompt.c
char    *get_full_cwd(void);
char    *get_prompt_cwd(void);
void    prompt(void);

#endif