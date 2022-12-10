/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonza <dangonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 15:44:04 by dangonza          #+#    #+#             */
/*   Updated: 2022/12/10 17:11:36 by dangonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H

typedef enum e_bool
{
	false,
	true
}	t_bool;

typedef struct	s_redirs // ToDo: there's work to be done here...
{
	char *in;		// Either "<" or "<<". If NULL, no redirection. Use str_equals() to compare.
	char *out;		// Either ">" or ">>". If NULL, no redirection.
	char *file_in;	// Null by default. If not null, it's the file to read from.
	char *file_out;	// Null by default. If not null, it's the file to write to.
} t_redirs;

typedef struct	s_command
{
	struct s_command	*next;
	char		*exec;
	int			argc;
	char		**argv; // argv[0] is the command name; but if given as a path, should it be the whole path?
	t_redirs	*redirs; // If NULL, no redirs.
}	t_command;

typedef struct	s_env
{
	struct s_env	*next;
	char	*name;
	char	*value;
	char	*join;
} t_env;

#endif