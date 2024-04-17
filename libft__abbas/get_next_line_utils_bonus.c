/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line_utils_bonus.c                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: adakheel <adakheel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/16 14:33:00 by adakheel      #+#    #+#                 */
/*   Updated: 2024/02/14 16:48:49 by adakheel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// size_t	ft_strlen(const char *s)
// {
// 	size_t	i;

// 	i = 0;
// 	if (s == NULL)
// 		return (i);
// 	while (s[i] != '\0')
// 	{
// 		i++;
// 	}
// 	return (i);
// }

// size_t	ft_strlcpy(char *dst, const char *src, size_t size)
// {
// 	int		i;
// 	size_t	len;

// 	i = 0;
// 	len = ft_strlen(src);
// 	if (size == 0)
// 		return (len);
// 	while (src[i] != '\0' && (size - 1) > 0)
// 	{
// 		dst[i] = src[i];
// 		i++;
// 		size--;
// 	}
// 	dst[i] = '\0';
// 	return (len);
// }

// char	*ft_strchr(const char *s, int c)
// {
// 	while (c > 255)
// 		c -= 256;
// 	while (*s != '\0')
// 	{
// 		if ((unsigned char)*s == c)
// 			return ((char *)s);
// 		s++;
// 	}
// 	if (c == '\0')
// 		return ((char *)s);
// 	return (NULL);
// }

char	*ft_strjoin_free(char *s1, char *s2)
{
	char	*p;
	size_t	lens1;
	size_t	lens2;
	size_t	tolen;

	lens1 = ft_strlen(s1);
	lens2 = ft_strlen(s2);
	tolen = lens1 + lens2 + 1;
	if (!s1)
		return ((char *) s2);
	if (!s2)
		return ((char *)s1);
	p = (char *)malloc(tolen * (sizeof(char)));
	if (!p)
	{
		free(s1);
		return (NULL);
	}
	ft_strlcpy(p, s1, lens1 + 1);
	ft_strlcpy(p + lens1, s2, lens2 + 1);
	free(s1);
	return (p);
}

char	*ft_free(char **temp)
{
	*temp = NULL;
	free(*temp);
	return (NULL);
}
