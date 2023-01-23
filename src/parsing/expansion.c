/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonza <dangonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 16:50:23 by dangonza          #+#    #+#             */
/*   Updated: 2023/01/19 13:01:17 by dangonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

// Given a str which starts with a valid token, get it
char	*get_token(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0' && str[i] != ' ' && str[i] != '\'' && str[i] != '"')
		i++;
	return (ft_substr(str, 0, i));
}

char	*expand_str(char *str, t_env *env_list)
{
	int		i;
	t_bool	inside_quotes;
	char	*raw_token;
	char	*env_token;

	inside_quotes = false;
	i = 0;
	while (str[i])
	{
		if (str[i] == '\'')
			inside_quotes = not(inside_quotes);
		if (str[i] == '$' && not(inside_quotes))
		{
			raw_token = get_token(str + i);
			env_token = ft_getenv(raw_token + 1, env_list);
			str = str_replace(str, raw_token, ft_strdup(env_token), 0);
			i += ft_strlen(env_token) - 1;
		}
		i++;
	}
	return (dequote_all(str));
}