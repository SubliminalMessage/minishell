/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonza <dangonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 15:44:18 by dangonza          #+#    #+#             */
/*   Updated: 2022/11/27 01:04:16 by dangonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/**
 * @brief Prints a Promt on the screen and let the user type freely
 * 
 * @return int, 0 if the shell should NOT be exited, 1 otherwise
*/
int    prompt(void)
{
    char    *prompt;
    char    *line_read;
    char    *aux;
    int     didExit;

    prompt = get_prompt_cwd();
    aux = ft_strjoin(WHITE"﴾"PROMPT_CWD"  ", prompt);
    free(prompt);
    prompt = ft_strjoin(aux, WHITE"  ﴿  "PROMPT_ACT"»  "RESET);
    free(aux);
    line_read = readline(prompt);
    free(prompt);

    printf("> '%s (%p)'\n", line_read, &line_read); // Do Something
    add_history(line_read);

    didExit = !ft_strncmp(line_read, "exit", 4);
    free(line_read);
    return (didExit);
}

/**
 * @brief Gets the CurrentWorkingDirectory of the user
 * 
 * @return char* containing the CWD of the user. No memory is wasted.
*/
char *get_full_cwd(void)
{
    char buffer[CWD_SIZE + 1];
    char *pwd;

    pwd = getcwd(buffer, CWD_SIZE);
    buffer[CWD_SIZE] = '\0';
    return (ft_strdup(pwd));
}

/**
 * @brief Gets the CWD in a format displayable in a Prompt. Tries to
 *        minimize the '$HOME' part into '~/'
 * 
 * @return char* containing the CWD of the user, in a displayable format
*/
char    *get_prompt_cwd(void)
{
    char    *pwd;
    char    *home;
    char    *prompt_cwd;
    size_t  home_len;

    pwd = get_full_cwd();
    home = getenv("HOME");
    printf(" >> %p\n", &home);
    if (home == NULL)
        return (pwd);
    prompt_cwd = ft_strnstr(pwd, home, ft_strlen(home));
    if (prompt_cwd == NULL)
        return (pwd);
    home_len = ft_strlen(home);
    prompt_cwd = ft_substr(pwd, home_len, ft_strlen(pwd) - home_len);
    free(pwd);
    pwd = prompt_cwd;
    prompt_cwd = ft_strjoin("~", pwd);
    free(pwd);
    if (ft_strlen(prompt_cwd) == 2)
    {
        free(prompt_cwd);
        return (ft_strdup("~"));
    }
    return (prompt_cwd);
}