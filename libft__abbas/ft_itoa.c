/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_itoa.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: adakheel <adakheel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/11 13:13:32 by adakheel      #+#    #+#                 */
/*   Updated: 2024/04/23 12:45:11 by adakheel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	nbrlen(long int n)
{
	int	len;

	len = 0;
	if (n < 0)
	{
		len = 1;
		n = n * -1;
	}
	if (n == 0)
	{
		len = 1;
	}
	while (n != 0)
	{
		n = n / 10;
		len++;
	}
	return (len);
}

static void	convert_to_string(char *p, long n, int neg, int l)
{
	char		*str;
	int			len;
	long		nbr;
	int			sign;
	char *base = "0123456789ABCDEF";

	str = p;
	len = l;
	nbr = n;
	sign = neg;
	str[len] = '\0';
	while (len > 0)
	{
		str[len - 1] = nbr % 10 + '0';
		nbr = nbr / 10;
		len--;
	}
	if (sign == -1)
		str[0] = '-';
}

char	*ft_itoa(int n)
{
	long			nbr;
	int				sign;
	int				len;
	char			*str;

	nbr = n;
	len = nbrlen(nbr);
	sign = 1;
	if (nbr < 0)
	{
		sign = -1;
		nbr = nbr * -1;
	}
	str = NULL;
	str = malloc((len + 1) * sizeof(char));
	if (!str)
		return (NULL);
	convert_to_string(str, nbr, sign, len);
	return (str);
}
