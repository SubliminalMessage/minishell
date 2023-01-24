/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonza <dangonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 14:50:40 by dangonza          #+#    #+#             */
/*   Updated: 2023/01/24 15:44:05 by dangonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	pwd(void)
{
	char *pwd;

    pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		printf("pwd: error retrieving current directory\n");
		return (1);
	}
	printf("%s\n", pwd);
	free(pwd);
    return (0);
}
