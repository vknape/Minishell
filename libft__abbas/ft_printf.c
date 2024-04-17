/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_printf.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: adakheel <adakheel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/31 09:57:12 by adakheel      #+#    #+#                 */
/*   Updated: 2024/02/15 10:45:50 by adakheel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	dtat_type_decide(const char *format, va_list ap)
{
	int	counter;

	counter = 0;
	if (*format == 'd' || *format == 'i')
		counter = ft_nbrlength(va_arg(ap, int));
	else if (*format == 'c')
		counter = ft_printf_putchar(va_arg(ap, int));
	else if (*format == 's')
		counter = ft_printf_putstr(va_arg(ap, char *));
	else if (*format == 'x' || *format == 'X')
		counter = ft_hexnum(va_arg(ap, int), format);
	else if (*format == '%')
		counter = ft_printf_putchar(*format);
	else if (*format == 'p')
		counter = ft_void_hex(va_arg(ap, void *));
	else if (*format == 'u')
		counter = ft_unsigned_nbrlength(va_arg(ap, int));
	return (counter);
}

int	ft_printf(const char *format, ...)
{
	va_list	ap;
	int		i;
	int		counter;
	int		count;

	i = 0;
	count = 0;
	va_start(ap, format);
	while (format[i] != '\0')
	{
		if (format[i] != '%')
		{
			ft_printf_putchar(format[i]);
			i++;
			count++;
		}
		if (format[i] == '%')
		{
			counter = dtat_type_decide(&format[i + 1], ap);
			count = count + counter;
			i = i + 2;
		}
	}
	va_end(ap);
	return (count);
}

// int	main(void)
// {
// 	int a, b;
// 	a = printf("hex number (%d)\n", 2147483647);
// 	printf("return value is (%d)\n", a);
// 	b = ft_printf("hex number (%d)\n", 2147483647);
// 	printf("return value is (%d)\n", b);
// 	return (0);
// }
