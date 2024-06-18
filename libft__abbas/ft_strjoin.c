/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strjoin.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: adakheel <adakheel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/10 13:24:01 by adakheel      #+#    #+#                 */
/*   Updated: 2024/06/10 12:47:12 by adakheel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// void	*safe_malloc(size_t size, void *all)
// {
// 	void	*ptr;

// 	ptr = malloc(size);
// 	if (!ptr)
// 	{
// 		//print error
// 		//free;
// 		//exit
// 	}
// 	return (ptr);
// }

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*p;
	size_t	lens1;
	size_t	lens2;
	size_t	tolen;

	if (!s1)
		return ((char *) s2);
	if (!s2)
		return ((char *)s1);
	lens1 = ft_strlen(s1);
	lens2 = ft_strlen(s2);
	tolen = lens1 + lens2 + 1;
	//p = safe_malloc(tolen * (sizeof(char)));
	p = (char *)malloc(tolen * (sizeof(char)));
	if (!p)
		return (NULL);
	ft_strlcpy(p, s1, lens1 + 1);
	ft_strlcpy(p + lens1, s2, lens2 + 1);
	return (p);
}
