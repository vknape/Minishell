/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vknape <vknape@student.codam.nl>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 10:49:29 by vknape            #+#    #+#             */
/*   Updated: 2023/10/24 14:33:41 by vknape           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*lst1;

	lst1 = (t_list *) malloc(sizeof(t_list));
	if (lst1 == NULL)
		return (NULL);
	(*lst1).content = content;
	(*lst1).next = NULL;
	return (lst1);
}
