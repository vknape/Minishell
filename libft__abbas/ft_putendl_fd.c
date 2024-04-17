/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_putendl_fd.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: adakheel <adakheel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/13 12:33:35 by adakheel      #+#    #+#                 */
/*   Updated: 2023/10/16 12:56:42 by adakheel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putendl_fd(char *s, int fd)
{
	int		len;
	char	newline;

	len = ft_strlen(s);
	newline = '\n';
	if (s)
		write(fd, s, len);
	write(fd, &newline, 1);
}
