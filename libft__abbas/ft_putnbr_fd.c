/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_putnbr_fd.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: adakheel <adakheel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/13 12:46:55 by adakheel      #+#    #+#                 */
/*   Updated: 2023/10/20 11:23:47 by adakheel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	long	nbr;
	char	current;
	char	sign;

	sign = '-';
	nbr = n;
	if (nbr < 0)
	{
		nbr = nbr * -1;
		write(fd, &sign, 1);
	}
	if (nbr >= 10)
	{
		ft_putnbr_fd(nbr / 10, fd);
		ft_putnbr_fd(nbr % 10, fd);
	}
	else
	{
		current = nbr + '0';
		write(fd, &current, 1);
	}
}
