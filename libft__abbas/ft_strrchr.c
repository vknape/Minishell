/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strrchr.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: adakheel <adakheel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/09 08:17:09 by adakheel      #+#    #+#                 */
/*   Updated: 2023/10/20 15:19:55 by adakheel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*tp;
	int		len;

	tp = NULL;
	len = ft_strlen(s) - 1;
	while (c > 255)
		c = c - 256;
	if (c == '\0')
		return ((char *)s + len + 1);
	while (s && len >= 0)
	{
		if (s[len] == c)
		{
			tp = (char *)&s[len];
			return (tp);
		}
		len--;
	}
	return (tp);
}
