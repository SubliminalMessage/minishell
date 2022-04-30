/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 11:07:57 by dangonza          #+#    #+#             */
/*   Updated: 2022/01/24 18:43:12 by dangonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(const char *s1, const char *s2)
{
	char	*new_string;
	size_t	s1_length;
	size_t	s2_length;

	if (!s1 || !s2)
		return (NULL);
	s1_length = ft_strlen(s1);
	s2_length = ft_strlen(s2);
	new_string = malloc(sizeof(char) * (s1_length + s2_length + 1));
	if (new_string != NULL)
	{
		ft_memcpy(new_string, s1, s1_length);
		ft_memcpy(new_string + s1_length, s2, s2_length);
		*(new_string + s1_length + s2_length) = '\0';
	}
	return (new_string);
}
