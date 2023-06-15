/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_save_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonza <dangonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 17:21:01 by dangonza          #+#    #+#             */
/*   Updated: 2023/06/15 16:44:56 by dangonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/**
 * @brief Given a string with a redirection in it, splits the non-redirection
 *        from the redirection part and saves them both.
 * 
 * @param arg, the String containing both parts (e.g.: 'echo>>out')
 * @param redir, the String where the redirection part should be saved
 * 
 * @note arg will contain the non-redirection part (e.g.: 'echo') and
 *       redir will contain the rest of the string (e.g.: '>>out')
*/
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

/**
 * @brief Given an argument, joins it to the redirection 'string' if
 *        a redirection is detected inside of that argument.
 * 
 * @param arg, double pointer to the argument
 * @param redir, double pointer to the string where the redirections are saved
 * 
 * @note If the last character of 'redir' is either '>' or '<', it means the
 *       whole argument must be used. If this argument starts with '>' or '<',
 *       it means the arguments are not valid!
 * @note If the last character of 'redir' is NOT '>' nor '<', it means
 *      there might not be any other redirection. So, in this case,
 *      we look for a redirection using 'contains_outside_quotes()', and
 *      if there are a redirection, we split it using 'split_redirection()'.
 * 
 * @return t_bool, whether if the argument IS NOT VALID or not.
*/
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

/**
 * @brief Given an 'identifier' that contains 0 to N redirections,
 *        returns the start of the next one.
 * 
 * @param identifier, double pointer to the String containing 0 to N redirs.
 *        This variable will contain the Next Redirection
 * @param leftover, double pointer to where the leftover (if any) should be
 *        saved.
 * 
 * @note identifier could be something like 'file', or it could be like
 *       'file>file2>file3>file4', and everything in between. The idea
 *       is that identifier will end up with 'file', and leftover
 *       will end up with the rest ('>file2>file3>file4 in the last example).
*/
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

/**
 * @brief Auxiliar function of 'save_redirection_double()'. Given a redirection
 *        type, and a file, adds it back to the proper t_file_lst of a command.
 * 
 * @param cmd, the Command where the redirection should be saved to.
 * @param redir_type, the redirecion type (e_ftype)
 * @param file, the file to add back.
*/
void	add_redirection_back(t_cmd **cmd, int redir_type, t_file *file)
{
	if (redir_type == TRUNC_FTYPE || redir_type == APPEND_FTYPE)
		ft_lstadd_back(&(*cmd)->out, ft_lstnew(file));
	else if (redir_type == READ_FTYPE || redir_type == HEREDOC_FTYPE)
		ft_lstadd_back(&(*cmd)->in, ft_lstnew(file));
}
