/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 11:59:39 by dangonza          #+#    #+#             */
/*   Updated: 2022/01/24 18:40:44 by dangonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

char	*ft_strrchr(const char *s, int c)
{
	size_t	char_index;
	char	*null_pointer;
	int		last_seen;

	null_pointer = 0;
	char_index = 0;
	last_seen = -1;
	while (*(s + char_index))
	{
		if ((unsigned char) *(s + char_index) == (unsigned char) c)
			last_seen = char_index;
		char_index++;
	}
	if (c == '\0')
		last_seen = char_index;
	if (last_seen != -1)
		return ((char *)(s + last_seen));
	return (null_pointer);
}
