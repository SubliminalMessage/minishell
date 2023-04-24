/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonza <dangonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 17:28:47 by dangonza          #+#    #+#             */
/*   Updated: 2023/04/24 17:51:56 by dangonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_bool	is_one_char_token(char *str)
{
	if (str[0] != '$' || str[1] == '\0')
		return (false);
	if (ft_hasany(SINGLE_CHAR_TKN, str[1]))
		return (true);
	return (false);
}

t_bool	is_wrapped_token(char *str)
{
	if (str && str[0] == '$' && str[1] == '{')
		return (true);
	return (false);
}

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

char	*expand_tkn(char *str, t_env_lst *envp, size_t *i)
{
	if (is_wrapped_token(str))
		return (expand_wrapped_tkn(str, envp, i));
	return (expand_normal_tkn(str, envp, i));
}
