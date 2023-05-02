/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonza <dangonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 21:38:58 by jre-gonz          #+#    #+#             */
/*   Updated: 2023/05/02 14:10:44 by dangonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/**
 * @brief Creates a path to the given command. It concatenates following:
 * 
 * String.format("%s/%s", path, cmd)
 * 
 * @param path The path to concatenate.
 * @param cmd The command to concatenate.
 * @return char* The path to the command.
 */
static char	*ft_make_path(char *path, char *cmd)
{
	int		path_len;
	int		cmd_len;
	char	*str;

	if (!path || !cmd)
		return (NULL);
	path_len = ft_strlen(path);
	cmd_len = ft_strlen(cmd);
	str = (char *) ft_calloc(sizeof(char), path_len + cmd_len + 2);
	if (!str)
		return (NULL);
	ft_strlcpy(str, path, path_len + 1);
	ft_strlcpy(str + path_len, "/", 2);
	ft_strlcpy(str + path_len + 1, cmd, cmd_len + 1);
	return (str);
}

/**
 * @brief Checks if the given path is a directory.
 * 
 * @param path The path to check.
 * @return t_bool
 */
static t_bool	ft_is_dir(char *path)
{
	struct stat	buf;

	if (stat(path, &buf) == -1)
		return (false);
	return (S_ISDIR(buf.st_mode));
}

/**
 * @brief Handles the case when the command does not need the $PATH.
 * @note this function does not check absolute paths necessarily.
 * It checks all commands that contain a '/', like "./", "../".
 *
 * @param cmd The command to use.
 * @return t_bool true if the command is valid, false otherwise.
 */
static t_bool	ft_handle_absolute_path(char *cmd)
{
	if (ft_is_dir(cmd))
	{
		ft_printf_fd(2, "minishell: %s: Is a directory\n", cmd); // TODO refactor
		return (false);
	}
	if (access(cmd, X_OK) == 0)
		return (true);
	ft_printf_fd(2, "minishell: %s: Permission denied\n", cmd); // TODO refactor
	return (false);
}

/**
 * @brief Attempts to find the command in the $PATH array given
 * @note Updates the cmd->cmd to the path of the command if found.
 * 
 * @param cmd
 * @param path
 * @return t_bool true if the command is valid, false otherwise.
 */
static t_bool	ft_handle_cmd(t_cmd *cmd, char **path)
{
	int		i;
	char	*path_cmd;

	i = 0;
	while (path[i])
	{
		path_cmd = ft_make_path(path[i], cmd->cmd);
		if (!path_cmd)
			return (false);
		if (!ft_is_dir(path_cmd) && access(path_cmd, X_OK) == 0)
		{
			free(cmd->cmd);
			cmd->cmd = path_cmd;
			return (true);
		}
		free(path_cmd);
		i++;
	}
	ft_printf_fd(2, "minishell: %s: command not found\n", cmd->cmd); // TODO refactor
	return (false);
}

/**
 * @brief Checks if the command with the given environment variables
 * can be executed.
 * @note The command is updated to the path of the command if found.
 * @note Expects the cmd->cmd to be allocated.
 * 
 * @param cmd Command to check.
 * @param envp Environment variables to use.
 * @return t_bool true if the command is valid, false otherwise.
 */
t_bool	ft_get_path(t_cmd *cmd, t_env_lst *envp)
{
	t_bool	r;
	char	**path;
	char	*variable;

	if (!cmd || !cmd->cmd)
		return (false);
	if (ft_strnstr(cmd->cmd, "/", ft_strlen(cmd->cmd)) != NULL)
		return (ft_handle_absolute_path(cmd->cmd));
	variable = ft_strdup(ft_getenv(envp, "PATH"));
	path = ft_split(variable, ':');
	free(variable);
	if (!path)
		return (false);
	r = ft_handle_cmd(cmd, path);
	return (ft_free_array(path), r);
}
