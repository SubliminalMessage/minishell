/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonza <dangonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 16:49:50 by dangonza          #+#    #+#             */
/*   Updated: 2023/06/01 19:36:04 by dangonza         ###   ########.fr       */
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


void	ft_export_print_variable(char *variable)
{
	char	*key;
	char	*value;
	int		separator_idx;

	if (!variable)
		return ;
	separator_idx = ft_strchr(variable, '=') - variable;
	key = ft_substr(variable, 0, separator_idx);
	value = ft_substr(variable, separator_idx + 1, ft_strlen(variable));
	if (key && value)
	{
		if (str_equals(value, ""))
			printf("declare -x %s\n", key); // TODO: If no value, just print the key without ="" (At least OLDPWD)
		else
			printf("declare -x %s=\"%s\"\n", key, value); // TODO: If no value, just print the key without ="" (At least OLDPWD)
	}
	if (key)
		free(key);
	if (value)
		free(value);
	free(variable);
}
void	ft_export_print(char ***array_raw)
{
	int	i;
	char	**array;
	int		arr_size;
	
	array = *array_raw;
	arr_size = ft_arrsize(array);
	i = -1;
	while (++i < arr_size)
		ft_export_print_variable(array[i]);
	free(array);
}

int	ft_export_compare_strs(char *a, char *b)
{
	int	separator_idx;
	int	result;
	char *key_a;
	char *key_b;

	if (!a || !b)
		return (ft_strcmp(a, b));

	separator_idx = ft_strchr(a, '=') - a;
	key_a = ft_substr(a, 0, separator_idx);
	separator_idx = ft_strchr(b, '=') - b;
	key_b = ft_substr(b, 0, separator_idx);
	if (!key_a && !key_b)
		result = ft_strcmp(key_a, key_b);
	else
		result = ft_strcmp(a, b);
	if (key_a)
		free(key_a);
	if (key_b)
		free(key_b);
	return (result);
}

void	ft_export_sort_and_print(t_env_lst *envp)
{
	static char	*temp = NULL;
	char	**array;
	int		arr_size;
	int		i;
	int		j;

	array = build_envp(envp);
	if (!array)
		return ; // TODO: handle this, i guess?
	arr_size = ft_arrsize(array);
	i = -1;
	while (++i < arr_size)
	{
		j = -1;
		while (++j < (arr_size - 1 - i))
		{
			if (ft_export_compare_strs(array[j], array[j+1]) > 0)
			{
				temp = array[j];
				array[j] = array[j+1];
				array[j+1] = temp;
			}
		}
	}
	ft_export_print(&array);
}

/**
 * @brief env builtin.
 * 
 * @note usage: export [KEY[=VALUE] ... ]
 * 
 * 
 * @param cmd command struct.
 * @param envp Environment List struct.
 * @return int exit code
 */
int	ft_export(t_cmd *cmd, t_env_lst **envp, t_bool do_print)
{
	int		argc;
	int		idx;

	argc = ft_arrsize(cmd->args);
	printf("Export argc => %d\n", argc);
	if (argc == 1 && do_print)
	{
		ft_export_sort_and_print(*envp);
	}
	else if (argc > 1)
	{
		idx = 0;
		while (cmd->args[++idx])
			ft_export_update(cmd->args[idx], envp, do_print);
	}
	return (0);
}
