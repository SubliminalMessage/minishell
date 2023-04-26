/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonza <dangonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 18:15:42 by dangonza          #+#    #+#             */
/*   Updated: 2023/04/25 21:17:31 by dangonza         ###   ########.fr       */
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
	if (contains_outside_quotes(string, ';'))
		return (false);
	if (contains_outside_quotes(string, '\\'))
		return (false);
	return (true);
}

/**
 * @brief Given an identifier and the redirection type, it creates a
 *        redirection file, which will be added to a command later on.
 * 
 * @note Not to be confused with 'ft_newfile()'
 * 
 * @param identifier, the identifier of the redirection (e.g.: 'end')
 * @param redirection_type, the redirection type, (e.g.: HEREDOC_FTYPE)
 * 
 * @return t_file*, the file created.
*/
t_file	*create_file(char *identifier, int redirection_type)
{
	if (redirection_type == HEREDOC_FTYPE)
		return (ft_new_here_doc(dequote(identifier)));
	return (ft_newfile(identifier, redirection_type));
}

/**
 * @brief Given a string and a character, checks if that character is present
 *        in the string, but outside quotes.
 * 
 * @brief str, the String to check
 * @brief c, the Char to look for
 * 
 * @return t_bool, whether the character is present and outside quotes, or not
*/
t_bool	contains_outside_quotes(char *str, char c)
{
	char	in_quote;
	int		i;

	if (c == '\'' || c == '"')
		return (false);
	in_quote = '\0';
	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
		{
			if (str[i] == in_quote)
				in_quote = '\0';
			else if (in_quote == '\0')
				in_quote = str[i];
		}
		if (str[i] == c && in_quote == '\0')
		{
			print_parse_error_str(INV_TKN_MSG" `", ft_chardup(c));
			return (true);
		}
		i++;
	}
	return (false);
}
