/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vknape <vknape@codam.student.nl>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 09:39:52 by vknape            #+#    #+#             */
/*   Updated: 2023/10/20 09:39:53 by vknape           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (little[0] == '\0')
		return ((char *)big);
	if (big[0] == '\0')
		return (NULL);
	if (len == 0)
		return (NULL);
	while (j < len)
	{
		while (big[j + i] == little[i] && j + i < len)
		{
			if (little[i + 1] == '\0')
				return ((char *)big + j);
			i++;
		}
		i = 0;
		j++;
	}
	return (NULL);
}
