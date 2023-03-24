/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   leaks_fds_check.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jre-gonz <jre-gonz@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 11:02:20 by jre-gonz          #+#    #+#             */
/*   Updated: 2023/03/24 11:40:25 by jre-gonz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "debug_minishell.h"
#include <stdio.h> // TODO debug
#define FD_DEBUG 2

static void	system_exec(char *cmdtemplate)
{
	FILE* fp = popen(cmdtemplate, "r");
	if (fp == NULL) {
		ft_printf_fd(FD_DEBUG, "Error opening command %s\n", cmdtemplate);
		return ;
	}
	char output[1024];
	size_t n = fread(output, 1, sizeof(output), fp);
	output[n] = '\0';
	ft_printf_fd(FD_DEBUG, output);
}

void	exit_checks(void)
{
	char cmdtemplate[1024];
	ft_printf_fd(FD_DEBUG, "\n\n******************************************\n");
	ft_printf_fd(FD_DEBUG, "Open fds:\n");
	sprintf(cmdtemplate, "lsof -p %d | grep CHR", getpid());
	system_exec(cmdtemplate);
	ft_printf_fd(FD_DEBUG, "\nLeaks:\n");
	sprintf(cmdtemplate, "leaks %d", getpid());
	system_exec(cmdtemplate);
	ft_printf_fd(FD_DEBUG, "******************************************\n");
}
