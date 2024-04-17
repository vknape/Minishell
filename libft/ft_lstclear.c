/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vknape <vknape@student.codam.nl>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 08:28:11 by vknape            #+#    #+#             */
/*   Updated: 2023/10/24 12:52:40 by vknape           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	if (!*lst)
	{
		return ;
	}
	if ((**lst).next)
	{
		ft_lstclear(&(**lst).next, del);
	}
	ft_lstdelone(*lst, del);
	*lst = NULL;
}
