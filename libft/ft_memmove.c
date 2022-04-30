/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 15:28:54 by dangonza          #+#    #+#             */
/*   Updated: 2022/01/24 14:15:31 by dangonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

static void	copy_backwards(unsigned char *dst, unsigned char *src, size_t len);
static void	copy_forwards(unsigned char *dst, unsigned char *src, size_t len);

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*dst_cp;
	unsigned char	*src_cp;

	if (!dst && !src)
		return (NULL);
	dst_cp = (unsigned char *) dst;
	src_cp = (unsigned char *) src;
	if (dst > src)
		copy_backwards(dst_cp, src_cp, len);
	else
		copy_forwards(dst_cp, src_cp, len);
	return (dst_cp);
}

static void	copy_backwards(unsigned char *dst, unsigned char *src, size_t len)
{
	size_t	i;

	i = 1;
	while (i <= len)
	{
		*(dst + len - i) = *(src + len - i);
		i++;
	}
}

static void	copy_forwards(unsigned char *dst, unsigned char *src, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		*(dst + i) = *(src + i);
		i++;
	}
}
