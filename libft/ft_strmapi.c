/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 11:49:06 by dangonza          #+#    #+#             */
/*   Updated: 2022/01/24 18:45:03 by dangonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(const char *s, char (*f)(unsigned int, char))
{
	char			*new_str;
	unsigned int	index;
	size_t			s_len;

	if (!s)
		return (NULL);
	s_len = ft_strlen(s);
	new_str = malloc(sizeof(char) * (s_len + 1));
	if (new_str != NULL)
	{
		new_str[s_len] = '\0';
		index = 0;
		while (index < s_len)
		{
			new_str[index] = f(index, *(s + index));
			index++;
		}
	}
	return (new_str);
}
