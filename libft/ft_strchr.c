/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 11:55:12 by dangonza          #+#    #+#             */
/*   Updated: 2022/01/24 18:40:34 by dangonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	size_t	char_index;
	char	*null_pointer;

	null_pointer = 0;
	char_index = 0;
	while (*(s + char_index))
	{
		if (*(s + char_index) == (char)c)
			return ((char *)(s + char_index));
		char_index++;
	}
	if (c == '\0')
		return ((char *)(s + char_index));
	return (null_pointer);
}
