/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 10:56:25 by dangonza          #+#    #+#             */
/*   Updated: 2022/01/24 18:41:32 by dangonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	find_needle(char *haystack, char *needle, size_t start_position);
static int	should_return_smth(char *haystack, char *needle, size_t index);

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	needle_length;
	size_t	haystack_length;
	size_t	index;

	index = 0;
	needle_length = ft_strlen(needle);
	if (needle_length == 0)
		return ((char *) haystack);
	haystack_length = ft_strlen(haystack) - needle_length;
	if (ft_strlen(haystack) == 0 || !(*haystack))
		return (NULL);
	while (index <= haystack_length && index < len)
	{
		if (should_return_smth((char *) haystack, (char *) needle, index))
		{	
			if (needle_length > 1 && (index + needle_length > len))
				return (NULL);
			else
				return ((char *) haystack + index);
		}
		index++;
	}
	return (NULL);
}

static int	should_return_smth(char *haystack, char *needle, size_t index)
{
	if (*(haystack + index) == *(needle))
		if (find_needle((char *) haystack, (char *) needle, index))
			return (1);
	return (0);
}

static int	find_needle(char *haystack, char *needle, size_t start_position)
{
	size_t	index;
	char	need;
	char	hays;

	index = 0;
	need = *(needle + index);
	hays = *(haystack + start_position + index);
	while (need && hays)
	{
		if (need != hays)
			return (0);
		index++;
		need = *(needle + index);
		hays = *(haystack + start_position + index);
	}
	return (1);
}
