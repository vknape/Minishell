/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memchr.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: adakheel <adakheel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/09 10:36:38 by adakheel      #+#    #+#                 */
/*   Updated: 2023/10/23 09:41:06 by adakheel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*p;
	unsigned char	*ischarfind;

	p = (unsigned char *)s;
	ischarfind = NULL;
	while (c > 255)
		c -= 256;
	while ((n > 0))
	{
		if (*p == (unsigned char)c)
		{
			ischarfind = p;
			break ;
		}
		else
		{
			p++;
			n--;
		}
	}
	return (ischarfind);
}
