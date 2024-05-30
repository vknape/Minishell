/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strncmp.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: vknape <vknape@codam.student.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/20 09:39:49 by vknape        #+#    #+#                 */
/*   Updated: 2024/05/28 13:52:16 by adakheel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *str1, const char *str2, size_t n)
{
	size_t			i;
	unsigned char	a;
	unsigned char	b;

	i = 0;
	if (n == 0)
		return (0);
	// dprintf(2, "str2 is (%s)---------------------------\n", str2);
	while (i < n && (str1[i] || str2[i]))
	{
		// dprintf(2, "letters are (%c) & (%c)\n", str1[i], str2[i]);
		a = str1[i];
		b = str2[i];
		if (a != b)
			return (a - b);
		i++;
	}
	return (str1[i - 1] - str2[i - 1]);
}
