/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jre-gonz <jre-gonz@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 16:49:50 by dangonza          #+#    #+#             */
/*   Updated: 2023/06/12 22:09:32 by jre-gonz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/**
 * @brief Given a key and a value, updates the Env. List with that data. This
 *       is an util function for ft_export()
 * 
 * @param envp, the Env. List to edit with a new key-value
 * @param key, the Variable name (e.g.: USER)
 * @param value, the Value (e.g.: dangonza)
 * 
*/
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

/**
 * @brief Given a string representing a key-value env. variable,
 *        parses it and handles the errors (if any). If everything
 *        went OK, updates that Key with the Value.
 * 
 * @param string, the Key-Value (e.g.: USER=dangonza)
 * @param envp, the Env. List to edit
 * 
 * @return int, 1 if something failed. 0 otherwise
*/
static int	ft_export_update(char *string, t_env_lst **envp)
{
	int		separator_idx;
	char	*key;
	char	*value;

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

/**
 * @brief Given a Key-Value representation of a variable, prints it the way
 *        export command does in bash.
 * 
 * @param variable, the Key-Value representation of the 
 *        variable (e.g.: USER=dangonza)
 * @param fd, the fd to print to
 * @param envp, the Env. List to read from
 *
*/
static void	ft_export_print_variable(char *variable, int fd, t_env_lst *envp)
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

/**
 * @brief Given an array of the variables (sorted, please), loops through them
 *        and prints them in order.
 * 
 * @param array_raw, the array to print.
 * @param fd, the fd to print to
 * @param envp, the Env. List to read from
*/
static void	ft_export_print(char ***array_raw, int fd, t_env_lst *envp)
{
	int		i;
	char	**array;
	int		arr_size;

	array = *array_raw;
	arr_size = ft_arrsize(array);
	i = -1;
	while (++i < arr_size)
		ft_export_print_variable(array[i], fd, envp);
	free(array);
}

/**
 * @brief Given two strings, compared them. Function used in sorting the
 *        ft_export() array of variables
 * 
 * @param a, the first string
 * @param b, the second string
 * 
 * @return int representing which one is 'smaller'
*/
static int	ft_export_compare_strs(char *a, char *b)
{
	int		separator_idx;
	int		result;
	char	*key_a;
	char	*key_b;

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

/**
 * @brief Given an Env. List and a fd, sorts the Env. Variables and
 *        prints them in order into the fd
 * 
 * @param envp, the Env. List
 * @param fd, the fd to print to
 * 
*/
static void	ft_export_sort_and_print(t_env_lst *envp, int fd)
{
	char	*temp;
	char	**array;
	int		arr_size;
	int		i;
	int		j;

	array = build_envp(envp, true);
	if (!array)
		return ;
	arr_size = ft_arrsize(array);
	i = -1;
	while (++i < arr_size)
	{
		j = -1;
		while (++j < (arr_size - 1 - i))
		{
			if (ft_export_compare_strs(array[j], array[j + 1]) > 0)
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
int	ft_export(t_cmd *cmd, t_env_lst **envp, int fd) // TODO already in file
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
