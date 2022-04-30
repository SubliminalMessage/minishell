/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 11:48:52 by dangonza          #+#    #+#             */
/*   Updated: 2022/01/24 18:46:04 by dangonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	unsigned int	index;
	size_t			s_len;

	if (s)
	{
		s_len = ft_strlen(s);
		index = 0;
		while (index < s_len)
		{
			f(index, s);
			s++;
			index++;
		}
	}
}
