/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   link_list_chunk.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: adakheel <adakheel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/06/27 07:33:44 by adakheel      #+#    #+#                 */
/*   Updated: 2024/07/01 11:45:06 by adakheel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_chunk	*ft_lstnewchunkfree(t_all *all, char *str)
{
	t_chunk	*lst1;

	lst1 = calloc(1, sizeof(t_chunk));
	if (lst1 == NULL)
	{
		free(str);
		memory_allocation_failed(all);
	}
	(*lst1).next = NULL;
	lst1->str = str;
	return (lst1);
}

t_chunk	*ft_lstnewchunk(t_all *all, char *str)
{
	t_chunk	*lst1;

	lst1 = calloc(1, sizeof(t_chunk));
	if (lst1 == NULL)
		memory_allocation_failed(all);
	(*lst1).next = NULL;
	lst1->str = str;
	return (lst1);
}

t_chunk	*ft_lstlast_chunk(t_chunk *lst)
{
	if (lst == NULL)
		return (lst);
	while ((*lst).next != NULL)
		lst = (*lst).next;
	return (lst);
}

void	ft_lstadd_back_chunk(t_chunk **lst, t_chunk *new)
{
	t_chunk	*ptr;

	if (!*lst)
	{
		*lst = new;
		return ;
	}
	ptr = ft_lstlast_chunk(*lst);
	if (new)
		(*ptr).next = new;
}

void	lstclear(t_chunk **lst)
{
	t_chunk	*temp;
	t_chunk	*temp2;

	if (!*lst || !*lst)
	{
		return ;
	}
	temp = *lst;
	while (temp)
	{
		free(temp->str);
		temp2 = temp;
		temp = temp->next;
		free(temp2);
		temp2 = NULL;
	}
	*lst = NULL;
}
