/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonza <dangonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 18:45:39 by dangonza          #+#    #+#             */
/*   Updated: 2023/06/06 20:40:59 by dangonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/**
 * @brief Prints a message (normally, a Parse Error Message) on the console,
 *        but only if no other message was printed before. It is similar
 *        to a mutex for printf().
 * 
 * @param str, the String to print
 * @param clear, whether the 'mutex' can be cleared or not (false by default)
 * @note Once a message has been printed, it won't accept any other unless
 *       the function is 'cleared' before.
*/
void	print_parse_error(char *str, t_bool clear)
{
	static t_bool	has_been_printed = false;

	if (str && !has_been_printed)
	{
		printf("%s", str);
		if (last_char(str) != '\n')
			printf("\n");
		has_been_printed = true;
	}
	if (clear)
		has_been_printed = false;
}

/**
 * @brief Auxiliar function for print_parse_error(). It accepts two
 *        strings (e.g.: 'My name is ', 'dangonza'). It joins them and
 * 		  frees them once it has been printed (or not).
 * 
 * @note This function builds the string that will be send to 
 *       print_parse_error(), but it doesn't handle whether it will be printed
 *       or not.
 * 
 * @param msg, first string. It must not be malloc()-ed (or be freed() outside)
 * @param str, second string. it must be malloc()-ed outside.
*/
void	print_parse_error_str(char *msg, char *str)
{
	char	*to_print;

	to_print = join_three(ft_strdup(msg), str, ft_strdup("'\n"));
	print_parse_error(to_print, false);
	free(to_print);
}
