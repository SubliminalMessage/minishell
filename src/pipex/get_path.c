/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jre-gonz <jre-gonz@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 10:48:50 by jre-gonz          #+#    #+#             */
/*   Updated: 2022/12/27 09:31:26 by jre-gonz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/**
 * @brief Attempt to get the path of the given command with the env PATH.
 * 
 * @param cmd The command to search for.
 * @param path_array The array of paths to search in (also uses the current).
 * @return char* The path of the command or NULL if not found.
 */
char	*ft_get_path(char *cmd, char **path_array)
{
	int		i;
	char	*path;

	if (!path_array || !cmd)
		return (NULL);
	i = 0;
	if (access(cmd, X_OK) == 0)
		return (cmd);
	while (path_array[i])
	{
		path = ft_make_path(path_array[i], cmd);
		if (!path)
			return (NULL);
		if (access(path, X_OK) == 0)
			return (path);
		free(path);
		i++;
	}
	return (NULL);
}
