/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   envp.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: vknape <vknape@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/04/24 11:45:42 by vknape        #+#    #+#                 */
/*   Updated: 2024/05/03 13:09:09 by adakheel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	make_envp_and_set(t_all *all, char *envp[])
{
	int	i;

	i = 0;
	while (envp[i])
	{
		ft_lstadd_back_chunk(&all->envp, ft_lstnewchunk(ft_substr(envp[i], 0, ft_strlen(envp[i]))));
		ft_lstadd_back_chunk(&all->set, ft_lstnewchunk(ft_substr(envp[i], 0, ft_strlen(envp[i]))));
		i++;
	}
}

// void	make_export(t_all *all, char *envp[])
// {
// 	int		i;

// 	i = 0;
// 	while (envp[i])
// 	{
// 		ft_lstadd_back_chunk(&all->export,
// 			ft_lstnewchunk(ft_strjoin("declare -x ", envp[i])));
// 		i++;
// 	}
// }

void	ft_swap_strings(char **str1, char **str2)
{
	char	*temp;

	temp = *str1;
	*str1 = *str2;
	*str2 = temp;
}

void	sorter_export(t_all *all)
{
	t_chunk	*temp;
	t_chunk	*temp2;

	temp = all->export;
	while (temp)
	{
		temp2 = temp->next;
		while (temp2)
		{
			if (ft_strncmp(temp->str, temp2->str, ft_strlen(temp->str)) > 0)
			{
				ft_swap_strings(&temp->str, &temp2->str);
			}
			temp2 = temp2->next;
		}
		temp = temp->next;
	}
}

void	make_export(t_all *all, char *envp[])
{
	int		i;

	i = 0;
	while (envp[i])
	{
		ft_lstadd_back_chunk(&all->export, ft_lstnewchunk(ft_strjoin("declare -x ", envp[i])));
		i++;
	}
	sorter_export(all);
}
