/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strlcat.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: adakheel <adakheel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/06 09:59:54 by adakheel      #+#    #+#                 */
/*   Updated: 2023/10/20 11:20:29 by adakheel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	l_d;
	size_t	l_s;
	size_t	result;
	int		i;

	i = 0;
	l_s = ft_strlen(src);
	l_d = ft_strlen(dst);
	if (size > l_d)
		result = l_s + l_d;
	else
		result = size + l_s;
	if (size != 0)
	{
		while (src[i] != '\0' && size - 1 > l_d)
		{
			dst[l_d] = src[i];
			i++;
			l_d++;
		}
		dst[l_d] = '\0';
	}
	return (result);
}
