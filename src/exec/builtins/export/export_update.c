/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_update.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonza <dangonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 22:39:43 by jre-gonz          #+#    #+#             */
/*   Updated: 2023/06/17 23:31:24 by dangonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/**
 * @brief Given a key and a value, updates the Env. List with that data. This
 *       is an util function for ft_export()
 * 
 * @param envp, the Env. List to edit with a new key-value
 * @param key, the Variable name (e.g.: USER)
 * @param value, the Value (e.g.: dangonza)
 * 
*/
static void	ft_export_update_env(t_env_lst **envp, char *key, char *value)
{
	char	*old_value;

	if (!key)
		return ;
	old_value = ft_getenv(*envp, key);
	if (!old_value)
		return ;
	if (str_equals(old_value, ""))
		update_env(envp, key, value, true);
	else if (value && !str_equals(value, ""))
		update_env(envp, key, value, true);
	if (old_value)
		free(old_value);
}

#define EXPORT_IDENTIFIER "export: '%s': not a valid identifier\n"

/**
 * @brief Given a string representing a key-value env. variable,
 *        parses it and handles the errors (if any). If everything
 *        went OK, updates that Key with the Value.
 * 
 * @param string, the Key-Value (e.g.: USER=dangonza)
 * @param envp, the Env. List to edit
 * 
 * @return int, 1 if something failed. 0 otherwise
*/
int	ft_export_update(char *string, t_env_lst **envp)
{
	int		separator_idx;
	char	*key;
	char	*value;

	separator_idx = ft_strchr(string, '=') - string;
	key = ft_substr(string, 0, separator_idx);
	if (!is_valid_variable_name(key))
	{
		ft_printf_fd(STDERR_FILENO, MINISHELL_ERROR EXPORT_IDENTIFIER, key);
		free(key);
		return (1);
	}
	if (separator_idx <= 0)
		value = NULL;
	else
		value = ft_substr(string, separator_idx + 1, ft_strlen(string));
	if (!key || (!value && separator_idx > 0))
		return (1);
	else
		ft_export_update_env(envp, key, value);
	if (key)
		free(key);
	if (value)
		free(value);
	return (0);
}
