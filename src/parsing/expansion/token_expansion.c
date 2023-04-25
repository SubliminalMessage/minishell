/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_expansion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonza <dangonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 17:44:22 by dangonza          #+#    #+#             */
/*   Updated: 2023/04/25 15:41:28 by dangonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/**
 * @brief given a String representing the start of a Variable (Token) that
 *        is NOT wrapped (e.g.: $USER), returns the token in its expanded
 *        form.
 * 
 * @param str, the String that contains the Token to expand
 * @note str is not the token itself. It is a string starting with a token.
 *       (e.g.: '$USER is so cool!')
 * @param envp, the Env. Var. List. Will be used to expand the token
 * @param i, the index of the original string, to skip the characters
 *        we're about to remove. It's just to ensure correct behaviour!
 * 
 * @return char*, the original String, but with the Token already expanded
*/
char	*expand_normal_tkn(char *str, t_env_lst *envp, size_t *i)
{
	size_t	tkn_len;
	char	*variable;
	char	*token;
	char	*result;

	if (!str || str[0] != '$')
		return (NULL);
	tkn_len = 0;
	if (is_one_char_token(str))
		return (expand_custom_tkn(str, envp, i));
	while (str[tkn_len + 1])
	{
		if (!ft_hasany(VALID_TKN_CHARS, str[tkn_len + 1]))
			break ;
		tkn_len++;
	}
	if (tkn_len == 0)
		return (ft_strdup(str));
	token = ft_substr(str, 1, tkn_len);
	variable = ft_strdup(ft_getenv(envp, token));
	*i += ft_strlen(variable);
	result = join_two(variable, ft_substr(str, tkn_len + 1, ft_strlen(str)));
	free(token);
	return (result);
}

/**
 * @brief given a String representing the start of a Variable (Token) that
 *        IS wrapped (e.g.: ${USER}), returns the token in its expanded
 *        form. Note that this function uses expand_normal_tkn() internally.
 * 
 * @param str, the String that contains the Token to expand
 * @note str is not the token itself. It is a string starting with a token.
 *       (e.g.: '${USER} is so cool!')
 * @param envp, the Env. Var. List. Will be used to expand the token
 * @param i,the index of the original string, to skip the characters
 *        we're about to remove. It's just to ensure correct behaviour!
 * 
 * @return char*, the original String, but with the Token already expanded
*/
char	*expand_wrapped_tkn(char *str, t_env_lst *envp, size_t *i)
{
	char	*tkn;
	char	*aux;
	size_t	idx;

	idx = 2;
	while (str[idx] != '\0' && str[idx] != '}')
	{
		if (!ft_hasany(VALID_TKN_CHARS, str[idx]))
			break ;
		idx++;
	}
	if (str[idx] != '}')
	{
		print_parse_error(BAD_SUBST, false);
		return (NULL);
	}
	aux = ft_substr(str, 2, idx - 2);
	*i += 2;
	tkn = handle_numeric_tkn(join_two(ft_strdup("$"), aux), i);
	aux = expand_normal_tkn(tkn, envp, i);
	free(tkn);
	tkn = aux;
	aux = ft_substr(str, idx + 1, ft_strlen(str));
	return (join_two(tkn, aux));
}

/**
 * @brief given a String representing the start of a Variable (Token) whose
 *        value is (normally) not saved in a Env. Variable (e.g.: $#, $0),
 *        expands it and returns the result!
 * 
 * @param str, the String that contains the Token to expand
 * @note str is not the token itself. It is a string starting with a token.
 *       (e.g.: "I have $# friends :')!")
 * @param envp, the Env. Var. List. Will be used to expand the token
 * @note envp, is used for those variables who are stored in the Env. List
 *       (such as '$0', although hidden), or those whose content will be
 *       handled in the ft_getenv() function (such as '$?')
 * @param i,the index of the original string, to skip the characters
 *        we're about to remove. It's just to ensure correct behaviour!
 * 
 * @return char*, the original String, but with the Token already expanded
*/
char	*expand_custom_tkn(char *str, t_env_lst *envp, size_t *i)
{
	char	*token;
	char	*result;
	char	*variable;

	*i += 2;
	result = ft_substr(str, 2, ft_strlen(str));
	token = ft_chardup(str[1]);
	if (str_equals(token, "-"))
		variable = ft_strdup("himBH");
	else if (str_equals(token, "#"))
		variable = ft_strdup("0");
	else
		variable = ft_strdup(ft_getenv(envp, token));
	free(token);
	if (!result || !variable)
	{
		if (result)
			free(result);
		if (variable)
			free(variable);
		return (NULL);
	}
	return (join_two(variable, result));
}
