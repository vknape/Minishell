/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strlen.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: vknape <vknape@codam.student.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/20 09:39:43 by vknape        #+#    #+#                 */
/*   Updated: 2024/04/29 13:14:01 by adakheel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *c)
{
	int	i;

	i = 0;
	if (!c)
		return (0);
	while (c[i])
		i++;
	return (i);
}
