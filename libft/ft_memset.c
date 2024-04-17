/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vknape <vknape@codam.student.nl>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 09:39:01 by vknape            #+#    #+#             */
/*   Updated: 2023/10/20 16:51:49 by vknape           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *str, int c, int n)
{
	int				i;
	unsigned char	*a;

	i = 0;
	a = str;
	while (i < n)
	{
		a[i] = c;
		i++;
	}
	return (a);
}
