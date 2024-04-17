/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vknape <vknape@codam.student.nl>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 09:38:41 by vknape            #+#    #+#             */
/*   Updated: 2023/10/20 10:04:22 by vknape           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count(int n);

char	*ft_itoa(int n)
{
	int			i;
	const int	neg = (n < 0);
	char		*s;

	if (n == INT_MIN)
		return (ft_strdup("-2147483648"));
	if (n < 0)
		n *= -1;
	i = count(n);
	i += (n == 0);
	s = (char *)malloc((i + 1 + neg) * sizeof(char));
	if (s == NULL)
		return (NULL);
	if (neg != 0)
		s[0] = '-';
	s[i + neg] = '\0';
	while ((i + neg) > (0 + neg))
	{
		s[i - 1 + neg] = (n % 10) + '0';
		n /= 10;
		i--;
	}
	return (s);
}

static int	count(int n)
{
	int	i;

	i = 0;
	while (n > 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}
