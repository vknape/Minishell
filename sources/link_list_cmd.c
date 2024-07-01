/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   link_list_cmd.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: adakheel <adakheel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/06/27 07:33:54 by adakheel      #+#    #+#                 */
/*   Updated: 2024/06/27 07:56:57 by adakheel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_cmd	*ft_lstnewcmd(void)
{
	t_cmd	*lst1;

	lst1 = ft_calloc(1, sizeof(t_cmd));
	if (lst1 == NULL)
		return (NULL);
	(*lst1).next = NULL;
	return (lst1);
}

t_cmd	*ft_lstlast_cmd(t_cmd *lst)
{
	if (lst == NULL)
		return (lst);
	while ((*lst).next != NULL)
		lst = (*lst).next;
	return (lst);
}

void	ft_lstadd_back_cmd(t_cmd **lst, t_cmd *new)
{
	t_cmd	*ptr;

	if (!*lst)
	{
		*lst = new;
		return ;
	}
	ptr = ft_lstlast_cmd(*lst);
	if (new)
		(*ptr).next = new;
}

void	lstclear_cmd(t_cmd **lst)
{
	t_cmd	*temp;
	t_cmd	*temp2;

	if (!*lst || !*lst)
	{
		return ;
	}
	temp = *lst;
	while (temp)
	{
		temp2 = temp;
		temp = temp->next;
		free(temp2);
		temp2 = NULL;
	}
	lst = NULL;
}
