/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_nbrlength.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: adakheel <adakheel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/13 12:46:55 by adakheel      #+#    #+#                 */
/*   Updated: 2024/02/14 16:20:33 by adakheel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_putnbr(long n)
{
	char	current;
	char	sign;

	sign = '-';
	if (n < 0)
	{
		n = n * -1;
		write(1, &sign, 1);
	}
	if (n >= 10)
	{
		ft_putnbr(n / 10);
		ft_putnbr(n % 10);
	}
	else
	{
		current = n + '0';
		write(1, &current, 1);
	}
}

int	ft_nbrlength(long num)
{
	int	len;

	len = 0;
	ft_putnbr(num);
	if (num < 0 || num == 0)
		len = 1;
	while (num != 0)
	{
		len++;
		num = num / 10;
	}
	return (len);
}
