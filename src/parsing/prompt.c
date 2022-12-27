/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonza <dangonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 15:44:18 by dangonza          #+#    #+#             */
/*   Updated: 2022/12/08 16:46:27 by dangonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/**
 * @brief Prints a Promt on the screen and let the user type freely
 *        Parses and executes the commands the user wrote.
 * 
 * @param env_list The Environment Variable List for the execution part
 * 
 * @return bool, true if the shell should NOT be exited, false otherwise
*/
t_bool    prompt(t_env **env_list)
{
	char    *prompt;
	char    *line_read;
	int     didExit;

	prompt = get_displayable_prompt(*env_list);
	line_read = readline(prompt);
	free(prompt);
	add_history(line_read);

	execute_line(line_read);

	didExit = line_read == NULL || str_equals(line_read, "exit");
	if (line_read)
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
 * @param env_list The Environment Variable List to read the $HOME variable
 * 
 * @return char* containing the CWD of the user, in a displayable format
*/
char    *get_prompt_cwd(t_env *env_list)
{
	char    *pwd;
	char    *home;
	char    *prompt_cwd;
	size_t  home_len;

	pwd = get_full_cwd();
	home = ft_getenv("HOME", env_list); 
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

/**
 * @brief Gets the final prompt to be displayed on the terminal
 * 
 * @param env_list The Environment Variable List to read the $HOME variable
 * 
 * @return char* containing the final prompt to be displayed on the terminal
*/
char *get_displayable_prompt(t_env *env_list)
{
	char *prompt_before;
	char *prompt_after;
	char *cwd;

	cwd = get_prompt_cwd(env_list);
	prompt_before = ft_strdup(PROMPT_BEFORE);
	prompt_after = ft_strdup(PROMPT_AFTER);
	return (join_three(prompt_before, cwd, prompt_after));
}