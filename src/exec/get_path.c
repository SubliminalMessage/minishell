/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jre-gonz <jre-gonz@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 21:38:58 by jre-gonz          #+#    #+#             */
/*   Updated: 2023/04/29 22:31:09 by jre-gonz         ###   ########.fr       */
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

static t_bool	ft_absolute_path(char *path)
{
	return (ft_strnstr(path, "/", ft_strlen(path)) != NULL);
}

static t_bool	ft_is_dir(char *path)
{
	struct stat	buf;

	if (stat(path, &buf) == -1)
		return (false);
	return (S_ISDIR(buf.st_mode));
}

t_bool	ft_get_path(t_cmd *cmd, t_env_lst *envp)
{
	char	**path;
	char	*path_cmd;
	int		i;

	if (ft_absolute_path(cmd->cmd))
	{
		if (ft_is_dir(cmd->cmd))
		{
			ft_printf_fd(2, "minishell: %s: Is a directory\n", cmd->cmd); // TODO refactor
			return (false);
		}
		if (access(cmd->cmd, X_OK) == 0)
			return (true);
		ft_printf_fd(2, "minishell: %s: Permission denied\n", cmd->cmd); // TODO refactor
		return (false);
	}
	path = ft_split(ft_getenv(envp, "PATH"), ':');
	if (!path)
		return (false);
	i = 0;
	while (path[i])
	{
		path_cmd = ft_make_path(path[i], cmd->cmd);
		if (!path_cmd)
			return (ft_free_array(path), false);
		if (access(path_cmd, X_OK) == 0)
		{
			free(cmd->cmd);
			cmd->cmd = path_cmd;
			return (ft_free_array(path), true);
		}
		free(path_cmd);
		i++;
	}
	ft_printf_fd(2, "minishell: %s: command not found\n", cmd->cmd); // TODO refactor
	return (ft_free_array(path), false);
}
