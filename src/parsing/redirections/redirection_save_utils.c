/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_save_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonza <dangonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 17:21:01 by dangonza          #+#    #+#             */
/*   Updated: 2023/05/01 17:24:52 by dangonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	split_redirection(char **arg, char **redir)
{
	int		index;
	char	*aux;

	index = index_of_outside_quotes(*arg, "<>");
	if (index == -1)
		return ;
	*redir = join_two(*redir, ft_substr(*arg, index, ft_strlen(*arg)));
	aux = ft_substr(*arg, 0, index);
	free(*arg);
	*arg = aux;
}

t_bool	handle_redirection_argument(char **arg, char **redir)
{
	if (ft_hasany("<>", last_char(*redir)))
	{
		if (ft_hasany("<>", *arg[0]))
			return (true);
		*redir = join_two(*redir, *arg);
		*arg = ft_strdup("");
	}
	else if (contains_outside_quotes(*arg, "<>"))
		split_redirection(arg, redir);
	return (false);
}

void	get_next_redirection(char **identifier, char **leftover)
{
	int		idx;
	char	*aux;

	*leftover = NULL;
	if (!*identifier)
		return ;
	idx = index_of_outside_quotes(*identifier, "<>");
	if (idx != -1)
	{
		aux = ft_substr(*identifier, 0, idx);
		*leftover = ft_substr(*identifier, idx, ft_strlen(*identifier));
		free(*identifier);
		*identifier = aux;
	}
}

void	add_redirection_back(t_cmd **cmd, int redir_type, t_file *file)
{
	if (redir_type == TRUNC_FTYPE || redir_type == APPEND_FTYPE)
		ft_lstadd_back(&(*cmd)->out, ft_lstnew(file));
	else if (redir_type == READ_FTYPE || redir_type == HEREDOC_FTYPE)
		ft_lstadd_back(&(*cmd)->in, ft_lstnew(file));
}
