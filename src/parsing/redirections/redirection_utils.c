/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonza <dangonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 18:15:42 by dangonza          #+#    #+#             */
/*   Updated: 2023/06/04 15:58:46 by dangonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/**
 * @brief Given a string, returns if it is a redirection or not
 * 
 * @param string, the String to check
 * 
 * @return t_bool, whether it is a redirection or not
*/
t_bool	is_redirection(char *string)
{
	if (!string)
		return (false);
	return (string[0] == '>' || string[0] == '<');
}

/**
 * @brief Given a redirection, returns it's type
 * 
 * @param redirection, a String containing the redirection
 * @note redirection can only be '>', '>>', '<' and '<<'.
 * @note the value 'INVALID' should never be reached 
 * 
 * @return int (t_ftype), the redirection type.
*/
int	get_redirection_type(char *redirection)
{
	if (str_equals(redirection, ">"))
		return (TRUNC_FTYPE);
	if (str_equals(redirection, ">>"))
		return (APPEND_FTYPE);
	if (str_equals(redirection, "<"))
		return (READ_FTYPE);
	if (str_equals(redirection, "<<"))
		return (HEREDOC_FTYPE);
	return (INVALID);
}

/**
 * @brief Given a string, representing one argument of the command, returns
 *        if that argument is valid or not.
 * 
 * @param string, the String to check
 * 
 * @return t_bool, whether it is a valid argument or not 
*/
t_bool	is_valid_argument(char *string)
{
	int	idx;

	idx = index_of_outside_quotes(string, ";\\");
	if (idx != -1)
	{
		print_parse_error_str(INV_TKN_MSG" `", ft_chardup(string[idx]));
		return (false);
	}
	return (true);
}

/**
 * @brief Given an identifier and the redirection type, it creates a
 *        redirection file, which will be added to a command later on.
 * 
 * @note Not to be confused with 'ft_newfile()'
 * 
 * @param file, a pointer to the file (where it will be saved)
 * @param identifier, the identifier of the redirection (e.g.: 'end')
 * @param redirection_type, the redirection type, (e.g.: HEREDOC_FTYPE)
 * 
 * @return t_bool, whether the file was created successfully or not.
*/
t_bool	create_file(t_file **file, char *identifier, int redirection_type)
{
	*file = NULL;
	if (redirection_type == HEREDOC_FTYPE)
		*file = ft_new_here_doc(dequote_all(identifier));
	else
		*file = ft_newfile(identifier, redirection_type);
	if (*file)
		return (true);
	return (false);
}
