/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vknape <vknape@student.codam.nl>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 09:56:34 by vknape            #+#    #+#             */
/*   Updated: 2023/10/24 14:49:17 by vknape           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*lst1;
	t_list	*ptr;

	if (!lst || !f || !del)
		return (NULL);
	lst1 = ft_lstnew(f(lst->content));
	if (!lst1)
		return (NULL);
	ptr = lst1;
	lst = lst->next;
	while (lst)
	{
		lst1->next = ft_lstnew(f(lst->content));
		if (!lst1->next)
		{
			ft_lstclear(&ptr, del);
			return (NULL);
		}
		lst = lst->next;
		lst1 = lst1->next;
	}
	return (ptr);
}
