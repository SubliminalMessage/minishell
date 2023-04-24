/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_expansion.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonza <dangonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 00:23:19 by dangonza          #+#    #+#             */
/*   Updated: 2023/04/24 17:56:12 by dangonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*expand(char *str, t_env_lst *env)
{
	size_t	i;
	char	*aux;
	char	*expanded;

	if (!str || str[0] == '\'')
		return (str);
	i = 0;
	while (i < ft_strlen(str))
	{
		if (str[i] == '$')
		{
			aux = ft_substr(str, 0, i);
			expanded = expand_tkn(str + i, env, &i);
			aux = join_two(aux, expanded);
			free(str);
			if (!aux)
			{
				print_parse_error(ERROR_MALLOC, false);
				return (NULL);
			}
			str = aux;
		}
		i++;
	}
	return (str);
}

char	*expand_arg(char **str_ptr, t_env_lst *envp)
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
		print_parse_error(ERROR_MALLOC, false);
		return (NULL);
	}
	return (expanded);
}

t_bool	expand_file_list(t_file_lst **lst_ptr, t_env_lst *envp)
{
	t_file_lst	*node;
	t_file		*file;

	if (!lst_ptr || !*lst_ptr)
		return (true);
	node = *lst_ptr;
	while (node)
	{
		file = node->content;
		if (!file)
			continue ;
		file->name = expand_arg(&file->name, envp);
		if (!file->name)
			return (false);
		node = node->next;
	}
	return (true);
}

t_bool	expand_cmd(t_cmd **cmd_ptr, t_env_lst *envp)
{
	int		i;
	t_cmd	*cmd;

	if (!cmd_ptr || !*cmd_ptr || !*cmd_ptr)
		return (false);
	cmd = *cmd_ptr;
	i = 0;
	while (cmd->args[i])
	{
		cmd->args[i] = expand_arg(&cmd->args[i], envp);
		if (!cmd->args[i])
		{
			ft_free_array_content(&cmd->args[i + 1]);
			return (false);
		}
		i++;
	}
	if (expand_file_list(&cmd->in, envp) && expand_file_list(&cmd->out, envp))
		return (true);
	return (false);
}
