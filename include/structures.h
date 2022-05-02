/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonza <dangonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 15:44:04 by dangonza          #+#    #+#             */
/*   Updated: 2022/05/02 15:51:31 by dangonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H

typedef enum { false, true } bool;

typedef struct	s_command
{
	s_command	*next; // Next command (linked list);
	char		*raw; // Raw input
	char		*cmd; // Command with path
	char		**args; // Arguments of that command
	bool		has_heredoc; // Does the command need an input from heredoc?
	char		*heredoc; // If has_heredoc == true; Heredoc input;
	// [···]
}	t_command;

#endif