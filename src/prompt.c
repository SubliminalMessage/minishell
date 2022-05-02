/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonza <dangonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 15:44:18 by dangonza          #+#    #+#             */
/*   Updated: 2022/05/02 16:44:43 by dangonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/*

    Prompt structure:
    ➜ (Current Working Directory) (User input)

*/

void    prompt(void)
{
    char    *prompt;
    char    *line_read;
    char    *aux;


    aux = ft_strjoin(GREEN"➜  "CYAN, get_prompt_cwd());
    prompt = ft_strjoin(aux, " "RESET);
    free(aux);
    line_read = readline(prompt);
    free(prompt);
    // Do something
    printf("> '%s'\n", line_read);
    ///////////////
    free(line_read);
}

char *get_full_cwd(void)
{
    char buffer[CWD_SIZE + 1];
    char *pwd;

    pwd = getcwd(buffer, CWD_SIZE);
    buffer[CWD_SIZE] = '\0';
    //printf("full cwd: '%s'\n", pwd);
    return (ft_strdup(pwd));
}

char    *get_prompt_cwd(void)
{
    char    *pwd;
    char    *home;
    char    *prompt_cwd;
    size_t  home_len;

    pwd = get_full_cwd();
    //printf("PWD found: '%s'\n", pwd);
    home = getenv("HOME");
    if (home == NULL)
        return (pwd);
    prompt_cwd = ft_strnstr(pwd, home, ft_strlen(home));
    if (prompt_cwd == NULL)
        return (pwd);

    //printf("Home: %s\nPwd: %s\nPrompt_CWD: %s\n", home, pwd, prompt_cwd);

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
    //free(pwd);
    return (prompt_cwd);
}