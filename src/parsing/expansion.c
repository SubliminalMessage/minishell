/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonza <dangonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 00:23:19 by dangonza          #+#    #+#             */
/*   Updated: 2023/04/23 19:44:28 by dangonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*dequote(char *str)
{
	size_t	s_len;
	t_bool	is_unclosed;
	char	quote;
	char	*dequoted;

	if (!str)
		return (NULL);
	quote = str[0];
	s_len = ft_strlen(str);
	is_unclosed = (quote == '\'' || quote == '\"') && str[s_len - 1] != quote;
	if ((s_len == 1 && (quote == '\'' || quote == '"')) || is_unclosed)
	{
		printf(INVALID_TOKEN_CHR, str[0]);
		free(str);
		return (NULL);
	}
	if (quote != '\'' && quote != '"')
		return (str);
	dequoted = ft_substr(str, 1, s_len - 2);
	free(str);
	return (dequoted);
}

char	*get_next_quote(char *str, size_t *idx)
{
	char	quote;
	size_t	quote_idx;
	char	*quoted_str;
	
	if (!str)
		return (NULL);
	quote = '\0';
	if (str[0] == '\'' || str[0] == '"')
		quote = str[0];
	quote_idx = 1;
	while (str[quote_idx])
	{
		if (str[quote_idx] == '\'' || str[quote_idx] == '"')
			if (quote == '\0' || str[quote_idx] == quote)
				break ;
		quote_idx++;
	}
	if (quote != '\'' && quote != '"')
		quote_idx--;
	quoted_str = ft_substr(str, 0, quote_idx + 1);
	*idx += quote_idx + 1;
	return (quoted_str);
}

char *join_two(char *a, char *b)
{
	char *final;

	if (!a || !b)
	{
		if (a)
			free(a);
		if (b)
			free(b);
		return (NULL);
	}
	final = ft_strjoin(a, b);
	free(a);
	free(b);
	return (final);
}

#define VALID_TKN_CHARS "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXY_0123456789"
#define SINGLE_CHAR_TKN "$?-#*@!0123456789" // $_ is not considered SingleCharToken, because '$_a' is a valid one

t_bool	is_one_char_token(char *str)
{
	if (str[0] != '$' || str[1] == '\0')
		return (false);
	if (ft_hasany(SINGLE_CHAR_TKN, str[1]))
		return (true);
	return (false);
}

char *expand_custom_tkn(char *str, t_env_lst *envp, size_t *i)
{
	char	*token;
	char	*result;
	char	*variable;

	*i += 2;
	result = ft_substr(str, 2, ft_strlen(str));
	token = ft_chardup(str[1]);
	if (str_equals(token, "-"))
		variable = ft_strdup("himBH"); // https://stackoverflow.com/questions/42757236/what-does-mean-in-bash
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

char 	*expand_tkn(char *str, t_env_lst *envp, size_t *i)
{
	size_t tkn_len;
	char	*variable;
	char	*token;
	char	*result;

	if (!str || str[0] != '$')
		return (NULL);
	tkn_len = 0;
	if (is_one_char_token(str)) // TODO: Unwrap variables
		return (expand_custom_tkn(str, envp, i));
	while (str[tkn_len + 1]) // +1 to skip the initial '$'
	{
		if (!ft_hasany(VALID_TKN_CHARS, str[tkn_len + 1]))
			break;
		tkn_len++;
	}
	if (tkn_len == 0)
		return (ft_strdup(str));
	token = ft_substr(str, 1, tkn_len);
	variable = ft_strdup( ft_getenv(envp, token) );
	*i += ft_strlen(variable);
	result = join_two(variable, ft_substr(str, tkn_len + 1, ft_strlen(str)));
	free(token);
	return (result);
}

char	*expand(char *str, t_env_lst *env)
{
	size_t	i;
	char *aux;

	if (!str || str[0] == '\'')
		return (str);
	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
		{
			aux = join_two(ft_substr(str, 0, i), expand_tkn(str + i, env, &i));
			free(str);
			if (!aux)
			{
				printf(ERROR_MALLOC);
				return (NULL);
			}
			str = aux;
		}
		i++;
	}
	return (str);
}

char *expand_arg(char **str_ptr, t_env_lst *envp)
{
	char	*str;
	char	*dequoted;
	char	*expanded;
	size_t	len;
	size_t	i;

	i = 0;
	str = *str_ptr;
	len = ft_strlen(str);
	expanded = ft_strdup("");
	while (i <= len && str[i])
	{
		dequoted = dequote(expand(get_next_quote(str + i, &i), envp));
		expanded = join_two(expanded, dequoted);
		if (!expanded)
			break ;
	}
	free(*str_ptr);
	if (!expanded)
	{
		printf(ERROR_MALLOC);
		return (NULL);
	}
	return (expanded);
}
t_bool expand_file_list(t_file_lst **lst_ptr, t_env_lst *envp)
{
	t_file_lst *node;
	t_file *file;

	if (!lst_ptr || !*lst_ptr)
		return (true);
	node = *lst_ptr;
	while (node)
	{
		file = node->content;
		if (!file)
			continue;
		file->name = expand_arg(&file->name, envp);
		if (!file->name)
			return (false);
		node = node->next;
	}
	return (true);
}

t_bool expand_cmd(t_cmd **cmd_ptr, t_env_lst *envp)
{
	int	i;
	t_cmd *cmd;

	if (!cmd_ptr || !*cmd_ptr || !*cmd_ptr)
		return (false);
	cmd = *cmd_ptr;
	i = 0;
	while (cmd->args[i])
	{
		cmd->args[i] = expand_arg(&cmd->args[i], envp);
		if (!cmd->args[i])
			return (false);
		i++;
	}
	if (expand_file_list(&cmd->in, envp) && expand_file_list(&cmd->out, envp))
		return (true);
	return (false);
}
