/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 11:43:56 by dangonza          #+#    #+#             */
/*   Updated: 2022/01/24 11:46:28 by dangonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdlib.h>

static size_t	number_size(int number);
static void		before_parsing(int *n, char *s, size_t *placed, size_t nsize);
static char		*handle_int_min(char *int_min);

char	*ft_itoa(int n)
{
	size_t	n_size;
	size_t	index;
	size_t	placed;
	char	*str;

	if (n == -2147483648)
		return (handle_int_min("-2147483648"));
	n_size = number_size(n);
	str = malloc(sizeof(char) * (n_size + 1));
	if (str != NULL)
	{
		placed = 0;
		before_parsing(&n, str, &placed, n_size);
		index = 0;
		while (placed != n_size)
		{
			str[n_size - (index++) - 1] = (char)((n % 10) + 48);
			n /= 10;
			placed++;
		}
	}
	return (str);
}

static void	before_parsing(int *n, char *s, size_t *placed, size_t nsize)
{
	s[nsize] = '\0';
	if (*n < 0)
	{
		s[0] = '-';
		*n = -(*n);
		*placed = 1;
	}
}

static char	*handle_int_min(char *int_min)
{
	char	*str;
	int		index;

	str = malloc(sizeof(char) * 12);
	index = 0;
	while (index < 11)
	{
		*(str + index) = *(int_min + index);
		index++;
	}
	*(str + index) = '\0';
	return (str);
}

static size_t	number_size(int number)
{
	if (number < 0)
		return (1 + number_size(-number));
	if (number < 10)
		return (1);
	return (1 + number_size(number / 10));
}
