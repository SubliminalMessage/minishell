/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jre-gonz <jre-gonz@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 21:16:43 by jre-gonz          #+#    #+#             */
/*   Updated: 2023/06/12 22:43:12 by jre-gonz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

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
	if (key && (separator_idx <= 0 || (separator_idx > 0 && value))
		&& !str_equals(key, "_"))
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
				array[j] = array[j + 1];
				array[j + 1] = temp;
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
