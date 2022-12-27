/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jre-gonz <jre-gonz@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 22:08:11 by jre-gonz          #+#    #+#             */
/*   Updated: 2022/12/27 09:32:49 by jre-gonz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/**
 * @brief Creates a path to the given command. It concatenates following:
 * 
 * String.format("%s/%s", path, cmd)
 * 
 * @param path The path to concatenate.
 * @param cmd The command to concatenate.
 * @return char* The path to the command.
 */
char	*ft_make_path(char *path, char *cmd)
{
	int		path_len;
	int		cmd_len;
	char	*str;

	if (!path || !cmd)
		return (NULL);
	path_len = ft_strlen(path);
	cmd_len = ft_strlen(cmd);
	str = (char *) malloc(sizeof(char) * (path_len + cmd_len + 2));
	if (str == NULL)
		return (NULL);
	ft_strlcpy(str, path, path_len + 1);
	ft_strlcpy(str + path_len, "/", 2);
	ft_strlcpy(str + path_len + 1, cmd, cmd_len + 1);
	return (str);
}
