/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 11:14:58 by dangonza          #+#    #+#             */
/*   Updated: 2022/01/24 18:42:30 by dangonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	int		str_len;
	char	*str_pointer;

	str_len = ft_strlen(s1);
	str_pointer = malloc(sizeof(char) * (str_len + 1));
	if (str_pointer != NULL)
		ft_strlcpy(str_pointer, s1, (str_len + 1));
	return (str_pointer);
}
