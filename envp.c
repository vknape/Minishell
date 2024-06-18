/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   envp.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: vknape <vknape@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/04/24 11:45:42 by vknape        #+#    #+#                 */
/*   Updated: 2024/06/17 11:54:11 by adakheel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	make_envp_and_set(t_all *all, char *envp[])
// {
// 	int		i;

// 	i = 0;
// 	while (envp[i])
// 	{
// 		ft_lstadd_back_chunk(&all->envp, ft_lstnewchunk(ft_substr(envp[i], 0, ft_strlen(envp[i]))));
// 		i++;
// 	}
// }

void	make_envp_and_set(t_all *all, char *envp[])
{
	int		i;
	char	*temp;

	i = 0;
	while (envp[i])
	{
		temp = NULL;
		temp = ft_substr(envp[i], 0, ft_strlen(envp[i]));
		if (!temp && errno == 12)
			memory_allocation_failed(all);
		ft_lstadd_back_chunk(&all->envp, ft_lstnewchunk(all, temp));
		// ft_lstadd_back_chunk(&all->set, ft_lstnewchunk(ft_substr(envp[i], 0, ft_strlen(envp[i]))));
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
	int		j;

	i = 0;
	while (envp[i])
	{
		j = 0;
		while (envp[i][j] && envp[i][j] != '=')
			j++;
		ft_lstadd_back_chunk(&all->export, ft_lstnewchunk(all, ft_joined_for_export(all, envp[i], j)));
		i++;
	}
	sorter_export(all);
}
