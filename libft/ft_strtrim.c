/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vknape <vknape@codam.student.nl>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 09:40:00 by vknape            #+#    #+#             */
/*   Updated: 2023/10/20 16:33:33 by vknape           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char		*res;
	size_t		length;
	const char	*end = s1 + ft_strlen((char *)s1) - 1;

	while (ft_strchr(set, *s1) && *s1)
		s1++;
	while (ft_strchr(set, *end) && end >= s1)
		end--;
	length = end - s1 + 2;
	res = (char *)malloc((length) * sizeof(char));
	if (res == NULL)
		return (NULL);
	ft_strlcpy(res, s1, (length));
	return (res);
}
