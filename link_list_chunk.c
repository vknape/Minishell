
#include "minishell.h"

t_chunk	*ft_lstnewchunk(char *str)
{
	t_chunk	*lst1;

	lst1 = calloc(1, sizeof(t_chunk));
	if (lst1 == NULL)
		return (NULL);
	(*lst1).next = NULL;
	lst1->str = str;
	// dprintf(2, "str to add is (%s)\n", str);
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
	{
		// dprintf(2, "in ft_lstadd_back_chunk add new\n");
		(*ptr).next = new;
	}
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
