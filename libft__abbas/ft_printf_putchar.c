/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_printf_putchar.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: adakheel <adakheel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/13 11:50:39 by adakheel      #+#    #+#                 */
/*   Updated: 2024/02/15 10:44:26 by adakheel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printf_putchar(char c)
{
	write(1, &c, 1);
	return (1);
}
