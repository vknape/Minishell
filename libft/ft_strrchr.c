/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vknape <vknape@codam.student.nl>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 09:39:57 by vknape            #+#    #+#             */
/*   Updated: 2023/10/20 16:31:05 by vknape           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*end;

	c = c % 256;
	end = (char *)s + ft_strlen(s);
	while (*end != c)
	{
		if (end == s)
			return (NULL);
		end--;
	}
	return (end);
}
