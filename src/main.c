/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonza <dangonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 15:44:13 by dangonza          #+#    #+#             */
/*   Updated: 2023/04/21 19:18:27 by dangonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/*
	t_bool didExit;
	t_env *env_list;

	env_list = init_environ();
	didExit = false;
	while(!didExit)
		didExit = prompt(&env_list);
	printf("exit\n");
	free_environ(&env_list);
	return (0);
*/

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
			printf("[%d]: »%s«\n", i, input[i]);
			free(input[i]);
			i++;
		}
		free(input);
	}
	printf("exit\n");

	(void) argc;
	(void) argv;
	return (0);
}
