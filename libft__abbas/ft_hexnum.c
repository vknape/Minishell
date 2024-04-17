/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_hexnum.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: adakheel <adakheel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/31 09:58:53 by adakheel      #+#    #+#                 */
/*   Updated: 2024/02/15 10:45:06 by adakheel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	len_hex(unsigned int num)
{
	int	len;

	len = 0;
	if (num == 0)
		len = 1;
	while (num != 0)
	{
		num = num / 16;
		len++;
	}
	return (len);
}

static void	put_hex(unsigned int num, const char *format)
{
	if (num >= 16)
	{
		put_hex((num / 16), format);
		put_hex((num % 16), format);
	}
	else
	{
		if (num <= 9)
			ft_printf_putchar(num + '0');
		else
		{
			if (*format == 'X')
				ft_printf_putchar((num - 10) + 'A');
			else
				ft_printf_putchar((num - 10) + 'a');
		}
	}
}

int	ft_hexnum(int hex, const char *format)
{
	int		count;

	count = 0;
	put_hex((unsigned int)hex, format);
	count = len_hex((unsigned int)hex);
	return (count);
}
