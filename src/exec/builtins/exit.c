/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonza <dangonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 19:12:27 by jre-gonz          #+#    #+#             */
/*   Updated: 2023/06/07 22:51:04 by dangonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/**
 * @brief Util function. Same as ft_isalpha(), but applied to strings.
 * 
 * @param str, the String to check
 * 
 * @return t_bool, whether the string is alpha or not
*/
static t_bool	ft_str_is_alpha(char *str)
{
	int i;

	if (!str)
		return (false);
	i = -1;
	while (str[++i])
	{
		if (ft_isalpha(str[i]))
			return (true);
	}
	return (false);
}

/**
 * @brief Simple version of Atoi (without negatives), but applied to ULL
 *        (unsiged long long)
 * 
 * @param str, The string whose content is a number
 * 
 * @return unsigned long long, the number
*/
static unsigned long long ft_atoull(char *str)
{
	unsigned long long value;
	int i;

	value = 0;
	i = 0;
	while (str[i])
	{
		value = value * 10 + str[i] - '0';
		i++;
	}
	return (value);
}

/**
 * @brief Given a string containing the exit value, converts it
 *        into the 'correct' one, returns it. If any error happens
 *        in the process, the error message is also printed.
 * 
 * @param str, the string containing the exit value
 * 
 * @param int, the exit value (from 0 to 255)
*/
static int	ft_exit_get_value(char *str)
{
	unsigned long long value;
	int is_negative;

	is_negative = 0;
	if (str && str[0] == '-')
		is_negative++;
	if (!str || ft_strlen(str) > 20 || ft_str_is_alpha(str + is_negative))
	{
		ft_printf_fd(2, EXIT_ARG_NUM_MSG, str);
		return (255);
	}
	value = ft_atoull(str + is_negative);
	if (is_negative == 1)
		value *= -1; // Should be safe. The max number should be LONGLONG_MAX * 10. And it fits.
	if ((value > 9223372036854775807ULL && is_negative == 0) || (value > 9223372036854775808ULL && is_negative == 1))
	{
		ft_printf_fd(2, EXIT_ARG_NUM_MSG, str);
		return (255);
	}
	if (is_negative == 1)
		return (256 - (value % 256));
	return (value % 256);
}

/**
 * @brief exit builtin
 * @note usage: exit [exit_code]
 * 
 * @param cmd command struct
 * @param is_only_cmd whether the command is executed as a single
 *        command, or inside pipes. The latter do not print any 'exit'
 *        message.
 * 
 * @return int exit code
 */
int	ft_exit(t_cmd *cmd, t_bool is_only_cmd)
{
	int exit_code;

	if (is_only_cmd)
		ft_putstr_fd(EXIT_MSG, STDOUT);
	if (!cmd->args[1])
		exit_code = 0;
	else if (cmd->args[1] && !cmd->args[2])
		exit_code = ft_exit_get_value(cmd->args[1]);
	else
	{
		exit_code = 1;
		ft_printf_fd(2, EXIT_NUM_ARGS_MSG);
	}
	return (exit_code);
}
