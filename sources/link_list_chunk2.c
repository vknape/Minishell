/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   link_list_chunk2.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: adakheel <adakheel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/07/01 11:44:47 by adakheel      #+#    #+#                 */
/*   Updated: 2024/07/01 11:45:11 by adakheel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_lstsizechunk(t_chunk *lst)
{
	int	i;

	if (lst == NULL)
		return (0);
	i = 1;
	while ((*lst).next != NULL)
	{
		i++;
		lst = (*lst).next;
	}
	return (i);
}
