/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_printf_putstr.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: adakheel <adakheel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/13 12:25:12 by adakheel      #+#    #+#                 */
/*   Updated: 2024/02/15 10:44:17 by adakheel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printf_putstr(char *s)
{
	int		len;

	if (s == NULL)
	{
		write(1, &"(null)", 6);
		return (6);
	}
	len = ft_strlen(s);
	if (s)
		write(1, s, len);
	return (len);
}
