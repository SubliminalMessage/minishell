/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonza <dangonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 15:44:18 by dangonza          #+#    #+#             */
/*   Updated: 2023/01/24 15:32:29 by dangonza         ###   ########.fr       */
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
    char    *line_read;
    int     didExit;

    line_read = readline(DISPLAYABLE_PROMPT);
    add_history(line_read);

    execute_line(line_read, env_list);

    didExit = line_read == NULL || str_equals(line_read, "exit");
    if (line_read)
        free(line_read);
    return (didExit);
}
