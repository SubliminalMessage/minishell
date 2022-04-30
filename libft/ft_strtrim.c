/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 11:38:41 by dangonza          #+#    #+#             */
/*   Updated: 2022/01/24 18:43:35 by dangonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(const char *s1, const char *set)
{
	size_t	index;
	size_t	s_len;
	char	*null_pointer;

	null_pointer = 0;
	if (!s1 || !set)
		return (null_pointer);
	index = 0;
	while (*(s1 + index) && ft_strchr(set, *(s1 + index)))
		index++;
	s_len = ft_strlen(s1 + index);
	if (s_len != 0)
		while (ft_strchr(set, *(s1 + index + s_len)))
			s_len--;
	return (ft_substr(s1 + index, 0, s_len + 1));
}
