/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_calloc.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: adakheel <adakheel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/10 08:40:13 by adakheel      #+#    #+#                 */
/*   Updated: 2023/10/19 14:41:33 by adakheel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*p;

	if ((nmemb > 2147483647 && size > 0) || (size > 2147483647 && nmemb > 0))
		return (NULL);
	if (nmemb >= __SIZE_MAX__ || size >= __SIZE_MAX__)
		return (NULL);
	if (nmemb * size > 2147483647)
		return (NULL);
	p = malloc(nmemb * size);
	if (p == NULL)
		return (p);
	ft_bzero(p, size * nmemb);
	return (p);
}
