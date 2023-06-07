/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonza <dangonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 16:49:50 by dangonza          #+#    #+#             */
/*   Updated: 2023/06/07 16:44:16 by dangonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_bool is_valid_variable_name(char *str)
{
	int	i;

	if (!str || !str[0])
		return (false);
	if (!ft_hasany(VALID_TKN_CHARS, str[0]))
		return (false);
	i = 1;
	while (str[i])
	{
		if (!ft_hasany(VALID_TKN_CHARS"0123456789", str[i]))
			return (false);
		i++;
	}
	return (true);
}

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

static void	ft_export_update_env(t_env_lst **envp, char *key, char *value)
{
	char	*old_value;

	if (!key)
		return ;
	old_value = ft_getenv(*envp, key);
	if (!old_value)
		return ;
	if (str_equals(old_value, ""))
		update_env(envp, key, value, true);
	else if (value && !str_equals(value, ""))
		update_env(envp, key, value, true);
	if (old_value)
		free(old_value);
}

static int	ft_export_update(char *string, t_env_lst **envp)
{
	int separator_idx;
	char *key;
	char *value;

	separator_idx = ft_strchr(string, '=') - string;
	key = ft_substr(string, 0, separator_idx);
	if (!is_valid_variable_name(key))
	{
		ft_printf_fd(STDERR_FILENO, "minishell: export: `%s': not a valid identifier\n", key);
		free(key);
		return (1);
	}
	if (separator_idx <= 0)
		value = NULL;
	else
		value = ft_substr(string, separator_idx + 1, ft_strlen(string));
	if (!key || (!value && separator_idx > 0))
		return (1);
	else
		ft_export_update_env(envp, key, value);
	if (key)
		free(key);
	if (value)
		free(value);
	return (0);
}

static t_bool value_is_null(char *key, t_env_lst *envp)
{
	t_env *node;

	if (!key)
		return (true);
	while (envp)
	{
		node = envp->content;
		if (!str_equals(key, node->key))
		{
			envp = envp->next;
			continue ;
		}
		if (node->value)
			return (false);
		return (true);
	}
	return (true);
}

void	ft_export_print_variable(char *variable, int fd, t_env_lst *envp)
{
	char	*key;
	char	*value;
	int		separator_idx;

	if (!variable)
		return ;
	separator_idx = ft_strchr(variable, '=') - variable;
	key = ft_substr(variable, 0, separator_idx);
	if (separator_idx <= 0)
		value = NULL;
	else
		value = ft_substr(variable, separator_idx + 1, ft_strlen(variable));
	if (key && (separator_idx <= 0 || (separator_idx > 0 && value)) && !str_equals(key, "_"))
	{
		ft_printf_fd(fd, "declare -x %s", key);
		if (value && (!str_equals(value, "") || !value_is_null(key, envp)))
			ft_printf_fd(fd, "=\"%s\"", value);
		ft_printf_fd(fd, "\n");
	}
	if (key)
		free(key);
	if (value)
		free(value);
	free(variable);
}
void	ft_export_print(char ***array_raw, int fd, t_env_lst *envp)
{
	int	i;
	char	**array;
	int		arr_size;
	
	array = *array_raw;
	arr_size = ft_arrsize(array);
	i = -1;
	while (++i < arr_size)
		ft_export_print_variable(array[i], fd, envp);
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

void	ft_export_sort_and_print(t_env_lst *envp, int fd)
{
	char	*temp;
	char	**array;
	int		arr_size;
	int		i;
	int		j;

	array = build_envp(envp, true);
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
	ft_export_print(&array, fd, envp);
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
int	ft_export(t_cmd *cmd, t_env_lst **envp, int fd)
{
	int		argc;
	int		idx;
	int		num_fails;

	argc = ft_arrsize(cmd->args);
	num_fails = 0;
	if (argc == 1)
	{
		ft_export_sort_and_print(*envp, fd);
	}
	else if (argc > 1)
	{
		idx = 0;
		while (cmd->args[++idx])
			num_fails += ft_export_update(cmd->args[idx], envp);
	}
	if (num_fails == 0)
		return (0);
	return (1);
}
