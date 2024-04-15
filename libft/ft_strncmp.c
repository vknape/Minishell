/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strncmp.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: adakheel <adakheel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/06 12:18:51 by adakheel      #+#    #+#                 */
/*   Updated: 2024/02/15 12:26:27 by adakheel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	int				i;
	int				result;

	i = 0;
	result = 0;
	while (((unsigned char)s1[i] != '\0' || \
	(unsigned char)s2[i] != '\0') && n > 0)
	{
		if ((unsigned char)s1[i] != (unsigned char)s2[i])
		{
			result = (unsigned char)s1[i] - (unsigned char)s2[i];
			break ;
		}
		i++;
		n--;
	}
	return (result);
}
