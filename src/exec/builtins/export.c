/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonza <dangonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 16:49:50 by dangonza          #+#    #+#             */
/*   Updated: 2023/05/31 21:19:07 by dangonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ft_arrsize(char **array)
{
	int	i;

	if (!array || !(*array))
		return (0);
	i = 0;
	while (array[i])
		i++;
	return (i);
}

t_bool	is_valid_env_key(char *str) // TODO: Actually build this function
{
	if (str)
		return (true);
	return (false);
}

static int	ft_export_update(char *string, t_env_lst **envp, t_bool print)
{
	int separator_idx;
	char *key;
	char *value;

	separator_idx = ft_strchr(string, '=') - string;
	key = ft_substr(string, 0, separator_idx);
	if (!is_valid_env_key(key))
	{
		free(key);
		if (print)
			printf("Invalid identifier. // TODO: Change message pls");
		return (1);
	}
	value = ft_substr(string, separator_idx + 1, ft_strlen(string));
	if (!key || !value)
		printf("%s; // TODO: Change message. Print optionally ??\n", ERROR_MALLOC);
	else
		update_env(envp, key, value, true);
	if (key)
		free(key);
	if (value)
		free(value);
	return (0);
}

/**
 * @brief env builtin.
 * 
 * @note usage: export [KEY[=VALUE] ... ]
 * 
 * 
 * @param cmd command struct.
 * @param envp Environment List struct.
 * @return int exit code.
 */
int	ft_export(t_cmd *cmd, t_env_lst **envp, t_bool print_errors)
{
	int		argc;
	int		idx;

	argc = ft_arrsize(cmd->args);
	if (argc == 1)
	{
		// Print sorted; Export into another function
		printf("Not implemented (export sorted)\n");
	}
	else if (argc > 1)
	{
		idx = 1;
		while (cmd->args[idx])
		{
			ft_export_update(cmd->args[idx], envp, print_errors);
			idx++;
		}
	}
	return (0);
}
