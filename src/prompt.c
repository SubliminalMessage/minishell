#include <minishell.h>
/*

    Prompt structure:
    ➜ (Current Working Directory) (User input)

*/

void    prompt(void)
{
    char    *prompt = get_prompt_cwd();
    //printf("%s➜  %s%s %s", GREEN, CYAN, cwd, RESET);
    readline(prompt);
    free(prompt);
}

char *get_full_cwd(void)
{
    char buffer[CWD_SIZE + 1];
    char *pwd;

    pwd = getcwd(buffer, CWD_SIZE);
    buffer[CWD_SIZE] = '\0';
    return (pwd);
}

char    *get_prompt_cwd()
{
    char    *pwd;
    char    *home;
    char    *prompt_cwd;
    size_t  home_len;

    pwd = get_full_cwd();
    home = getenv("HOME");
    if (home == NULL)
        return (pwd);
    prompt_cwd = ft_strnstr(pwd, home, ft_strlen(home));
    if (prompt_cwd == NULL)
        return (pwd);

    //printf("Home: %s\nPwd: %s\nPrompt_CWD: %s\n", home, pwd, prompt_cwd);

    home_len = ft_strlen(home);
    pwd = ft_substr(pwd, home_len, ft_strlen(pwd) - home_len);
    prompt_cwd = ft_strjoin("~", pwd);
    free(pwd);
    return (prompt_cwd);
}