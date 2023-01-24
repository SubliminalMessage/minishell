/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonza <dangonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 12:57:20 by dangonza          #+#    #+#             */
/*   Updated: 2023/01/24 15:45:18 by dangonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/**
 * @brief Given a command name, return either that name is a builtint or not
 * 
 * @param cmd_name, The command name
 * 
 * @return t_bool, either true (if is a builtin), or false (it is not)
*/
t_bool	is_builtin(char *cmd_name)
{
	if (str_equals(cmd_name, "echo"))
		return (true);
	if (str_equals(cmd_name, "pwd"))
		return (true);
	if (str_equals(cmd_name, "cd"))
		return (true);
	return (false);
}

/**
 * @brief Given a builtin name, executes it
 * 
 * @param cmd_name, The builtin name
 * @param argv, The arguments vector (char **) in order to execute that command
*/
void	execute_builtin(char *builtin_name, int argc, char **argv, t_env **env)
{
	if (str_equals(builtin_name, "echo"))
		echo(argc, argv);
	if (str_equals(builtin_name, "pwd"))
		pwd();
	if (str_equals(builtin_name, "cd"))
		cd(argc, argv, env);
}
