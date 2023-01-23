/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonza <dangonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 16:27:28 by dangonza          #+#    #+#             */
/*   Updated: 2023/01/23 12:58:03 by dangonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	echo(int argc, char **argv)
{
	t_bool	print_nl;
	int		i;

	print_nl = true;
	i = 0;
	if (argc >= 2 && str_equals(argv[1], "-n"))
	{
		print_nl = false;
		i = 1;
	}
	if (argv)
	{
		while (argv[++i])
		{
			write(1, argv[i], ft_strlen(argv[i]));
			if (argv[i + 1] != NULL)
				write(1, " ", 1);
		}
	}
	if (print_nl)
		write(1, "\n", 1);
	return (0);
}
