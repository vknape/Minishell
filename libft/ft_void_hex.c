/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_void_hex.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: adakheel <adakheel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/31 11:47:03 by adakheel      #+#    #+#                 */
/*   Updated: 2024/02/15 10:46:34 by adakheel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	len_hex(unsigned long long num)
{
	int	len;

	len = 2;
	if (num == 0)
		len++;
	while (num != 0)
	{
		num = num / 16;
		len++;
	}
	return (len);
}

static void	put_hex(unsigned long long num)
{
	if (num >= 16)
	{
		put_hex((num / 16));
		put_hex((num % 16));
	}
	else
	{
		if (num <= 9)
			ft_printf_putchar(num + '0');
		else
			ft_printf_putchar((num - 10) + 'a');
	}
}

int	ft_void_hex(void *hex)
{
	int		count;
	char	*x;

	count = 0;
	x = "0x";
	if (hex == 0)
		return (ft_printf_putstr("(nil)"));
	else
	{
		write(1, x, 2);
		put_hex((unsigned long long)hex);
		count = len_hex((unsigned long long)hex);
	}
	return (count);
}
