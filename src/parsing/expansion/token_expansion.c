/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_expansion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonza <dangonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 17:44:22 by dangonza          #+#    #+#             */
/*   Updated: 2023/04/24 17:55:47 by dangonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

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
