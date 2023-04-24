/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonza <dangonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 18:45:39 by dangonza          #+#    #+#             */
/*   Updated: 2023/04/24 18:49:26 by dangonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	print_parse_error_str(char *msg, char *str)
{
	char	*to_print;

	to_print = join_three(ft_strdup(msg), str, ft_strdup("'\n"));
	print_parse_error(to_print, false);
	free(to_print);
}

void	print_parse_error(char *str, t_bool clear)
{
	static t_bool	has_been_printed = false;

	if (str && !has_been_printed)
	{
		printf("%s\n", str);
		has_been_printed = true;
	}
	if (clear)
		has_been_printed = false;
}
