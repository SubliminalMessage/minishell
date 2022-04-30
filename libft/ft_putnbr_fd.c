/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 11:48:44 by dangonza          #+#    #+#             */
/*   Updated: 2022/01/24 11:48:45 by dangonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

static void	print_number_recursively(int number, int fd);

void	ft_putnbr_fd(int n, int fd)
{
	if (n == -2147483648)
		write(fd, "-2147483648", 11);
	else
	{
		if (n < 0)
		{
			n *= -1;
			write(fd, "-", 1);
		}
		print_number_recursively(n, fd);
	}
}

static void	print_number_recursively(int number, int fd)
{
	int	last_digit;

	if (number < 10)
	{
		number += 48;
		write(fd, &number, 1);
	}
	else
	{
		last_digit = (number % 10) + 48;
		number /= 10;
		print_number_recursively(number, fd);
		write(fd, &last_digit, 1);
	}
}
