/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strnstr.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: adakheel <adakheel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/09 11:29:14 by adakheel      #+#    #+#                 */
/*   Updated: 2023/10/16 16:18:00 by adakheel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	c;

	if (*little == 0 || big == little)
		return ((char *)big);
	c = ft_strlen(little);
	while (*big && c <= len--)
	{
		if (!(ft_strncmp((char *)big, (char *)little, c)))
			return ((char *)big);
		big++;
	}
	return (NULL);
}
