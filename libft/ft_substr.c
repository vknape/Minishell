/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_substr.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: adakheel <adakheel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/10 13:02:23 by adakheel      #+#    #+#                 */
/*   Updated: 2023/10/20 16:27:46 by adakheel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*p;
	size_t	lenght;
	int		to_ma;

	lenght = ft_strlen(s) - start;
	if (start >= ft_strlen(s))
	{
		p = (char *)malloc(1 * sizeof(char));
		if (!p)
			return (NULL);
		*p = 0;
		return (p);
	}
	if (lenght < len)
		to_ma = lenght;
	else
		to_ma = len;
	p = (char *)malloc(to_ma + 1 * sizeof(char));
	if (!p)
		return (NULL);
	ft_strlcpy(p, &s[start], to_ma + 1);
	return (p);
}
