/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 11:26:12 by dangonza          #+#    #+#             */
/*   Updated: 2022/01/20 13:04:55 by dangonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t	index;
	char	*null_pointer;

	null_pointer = 0;
	index = 0;
	while (index < n)
	{
		if (*((unsigned char *)(s + index)) == (unsigned char) c)
			return ((void *)(s + index));
		index++;
	}
	return (null_pointer);
}
