/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonza <dangonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 15:44:13 by dangonza          #+#    #+#             */
/*   Updated: 2023/04/22 01:37:14 by dangonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int main(int argc, char **argv)
{
	char **input;

	while (true)
	{
		input = get_input();
		if (!input)
			continue;
		int i = 0;
		while (input[i])
		{
			t_cmd *cmd = parse_command(input[i]); // TODO: Do something with this!
			free(input[i]);
			ft_free_cmd(cmd);
			i++;
		}
		free(input);
	}
	printf("exit\n");

	(void) argc;
	(void) argv;
	return (0);
}
