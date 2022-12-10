/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonza <dangonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 17:03:48 by dangonza          #+#    #+#             */
/*   Updated: 2022/12/10 19:41:41 by dangonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*    This file is not meant to get into the final version of the Minishell   */

#ifndef DEBUG_H
# define DEBUG_H

#include <structures.h>

void    print_quotes(char *str);
void    print_single_cmd(t_command *cmd);
void   print_cmds(t_command *cmd_list);

#endif