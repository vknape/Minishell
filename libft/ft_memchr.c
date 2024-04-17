/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vknape <vknape@codam.student.nl>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 09:38:44 by vknape            #+#    #+#             */
/*   Updated: 2023/10/20 10:05:33 by vknape           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *str, int c, size_t n)
{
	size_t			i;
	unsigned char	*cstr;

	c = (unsigned char) c;
	i = 0;
	cstr = (unsigned char *)str;
	while (i < n)
	{
		if (cstr[i] == c)
			return (cstr + i);
		i++;
	}
	return (NULL);
}
