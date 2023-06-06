/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_expansion.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonza <dangonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 00:23:19 by dangonza          #+#    #+#             */
/*   Updated: 2023/06/06 19:38:58 by dangonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_bool	is_space(char c)
{
	if (c == ' ' || c == '\0')
		return (true);
	return (false);
}

char	*expand_home_dir(char *str, t_env_lst *env)
{
	int	i;
	char	*expanded;

	if (!ft_hasany(str, '~'))
		return (str);
	i = 0;
	while (str[i])
	{
		if (str[i] == '~')
		{
			if ((i == 0 && is_space(str[i + 1])) || (i > 0 && is_space(str[i - 1])))
			{
				expanded = expand_home_dir(ft_substr(str, i + 1, ft_strlen(str)), env);
				str = join_three(ft_substr(str, 0, i), ft_gethome(env), expanded);
				return (str);
			}
		}
		i++;
	}
	return (str);
}

/**
 * @brief Given a String (normally, one of the arguments of a command), checks
 *        for Environment Variables and expands them.
 * 
 * @param str, the String to check
 * @param env, the Env. Var. List. Will be used to expand those variables it
 *        encounters (if any).
 * 
 * @return char*, the original string, but with all of the variables expanded.
 *         can be NULL, if anything fails in the process.
*/
char	*expand(char *str, t_env_lst *env)
{
	size_t	i;
	char	*aux;
	char	*expanded;
	t_bool	skip;

	skip = (!str || str[0] == '\'');
	str = dequote(str);
	if (!str)
		return (NULL);
	i = -1;
	while (!skip && ++i < ft_strlen(str))
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
	}
	return (str);
}

/**
 * @brief Given an Array of Arguments of a command, loops through all of them
 *        and expands their environment variables. Note this function uses
 *        expand() interally.
 * 
 * @param str_ptr, the Array of Strings, representing the arguments of a
 *        command
 * @param envp, the Env. Var. List that will be used for expanding the Env.
 *        Variables it ecounters (if any).
 * 
 * @return char*, the argument with their variables expanded. Can be NULL if
 *         something failed in the process 
*/
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
		dequoted = expand(get_next_quote(str + i, &i), envp);
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
	return (expand_home_dir(expanded, envp));
}

/**
 * @brief Given a File List of a command, it expands their identifiers's
 *        names (e.g.: 'echo "test" > $USER' -> echo "test" > "dangonza"' ).
 * 
 * @param lst_ptr, double pointer to the File List.
 * @param envp, the Env. Var. List that will be used to expand the variables.
 * 
 * @return t_bool, whether everything went OK or not.
*/
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
		if (!file || file->type == HEREDOC_FTYPE)
		{
			node = node->next;
			continue ;
		}
		file->name = expand_arg(&file->name, envp);
		if (!file->name)
			return (false);
		node = node->next;
	}
	return (true);
}

/**
 * @brief Given a Command Structure, it expands its variables (from everywhere)
 * 
 * @param cmd_ptr, double pointer to the Command
 * @param envp, the Env. Var. List that will be used to expand the variables
 * 
 * @param t_bool, whether everything went OK or not
*/
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
