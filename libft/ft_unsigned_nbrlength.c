/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_unsigned_nbrlength.c                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: adakheel <adakheel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/31 09:59:48 by adakheel      #+#    #+#                 */
/*   Updated: 2024/02/14 16:21:20 by adakheel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_unsignednbr(unsigned int n)
{
	char	current;

	if (n >= 10)
	{
		ft_unsignednbr(n / 10);
		ft_unsignednbr(n % 10);
	}
	else
	{
		current = n + '0';
		write(1, &current, 1);
	}
}

int	ft_unsigned_nbrlength(unsigned int num)
{
	int	len;

	len = 0;
	ft_unsignednbr(num);
	if (num == 0)
		len = 1;
	while (num != 0)
	{
		len++;
		num = num / 10;
	}
	return (len);
}
