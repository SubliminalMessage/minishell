/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonza <dangonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 17:28:47 by dangonza          #+#    #+#             */
/*   Updated: 2023/04/25 00:07:37 by dangonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/**
 * @brief given a String representing the start of a Variable, returns whether
 *        if that 'token' has Length One (e.g.: '$0', '$#', '$?', ... ) or not.
 * 
 * @param str, the String to be checked
 * @note str is not the token itself. It is a string starting with a token.
 *       (e.g.: '$USER is so cool!')
 * 
 * @return t_bool, whether it's a One-Char-Token Variable or not
*/
t_bool	is_one_char_token(char *str)
{
	if (str[0] != '$' || str[1] == '\0')
		return (false);
	if (ft_hasany(SINGLE_CHAR_TKN, str[1]))
		return (true);
	return (false);
}

/**
 * @brief given a String representing the start of a Variable, returns whether
 *        if that 'token' is wrapped (e.g.: '${USER}') or not.
 * 
 * @param str, the String to be checked
 * @note str is not the token itself. It is a string starting with a token.
 *       (e.g.: '${USER} is so cool!')
 * 
 * @return t_bool, whether it is wrapped or not.
 * @note This does not check if it's well wrapped or not. This function will
 *       return true if str is '${{USER}}', or '${UnclosedWrap'. But that's OK!
*/
t_bool	is_wrapped_token(char *str)
{
	if (str && str[0] == '$' && str[1] == '{')
		return (true);
	return (false);
}

/**
 * @brief given a Token, handles it correctly if its a numeric one (e.g.: $125)
 * @note This 'Token' had been previously wrapped (e.g.: ${125} -> $125).
 * 
 * @param str, the Token to check
 * @param idx, the index of the original string, to skip the characters
 *       we're about to remove (if any). It's just to ensure correct behaviour!
 * 
 * @return char*, a new Token representing the correct value of the original
 *         Token. If it is not a Numeric Token (e.g.: '$USER'), nothing will
 *         change. 
 * 
 * @note If the Numeric Token represents a 0 (e.g.: ${000000000}), it will be
 *       replaced by '$0'.
 * 
 * @note If the Numeric Token doesn't represents a 0 (e.g.: ${01250}), it will
 *       be replaced by '$1'. If we were to be in a Script, this wouldn't be
 *       correct, but because we aren't, this behaviour works fine!
*/
char	*handle_numeric_tkn(char *str, size_t *idx)
{
	size_t	num;
	size_t	len;

	if (!str)
		return (str);
	len = ft_strlen(str + 1);
	if (len <= 1 || !ft_hasany("0123456789", str[1]))
		return (str);
	num = ft_atoi(str + 1);
	free(str);
	*idx += len - 2;
	if (num == 0)
		return (ft_strdup("$0"));
	return (ft_strdup("$1"));
}

/**
 * @brief Given a string containing a Env. Variable and the Env. Variable List,
 *        it expands the Token and returns the value expanded.
 * 
 * @param str, the String to be checked
 * @note str is not the token itself. It is a string starting with a token.
 *       (e.g.: '$USER is so cool!')
 * @param envp, the Environment Variable List.
 * @param idx, the index of the original string, to skip the characters
 *       we're about to remove. It's just to ensure correct behaviour!
 * 
 * @return char*, the token expanded, ready to be replaced with the un-expanded
 *         version.
*/
char	*expand_tkn(char *str, t_env_lst *envp, size_t *idx)
{
	if (is_wrapped_token(str))
		return (expand_wrapped_tkn(str, envp, idx));
	return (expand_normal_tkn(str, envp, idx));
}
