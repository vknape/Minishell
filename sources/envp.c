/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   envp.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: vknape <vknape@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/04/24 11:45:42 by vknape        #+#    #+#                 */
/*   Updated: 2024/07/01 11:17:17 by adakheel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*change_shlvl(t_all *all, char *str)
{
	char	*new;
	int		i;

	if (str[0] == 'S')
		i = ft_atoi(str + 6) + 1;
	else
		i = ft_atoi(str + 18) + 1;
	if (str[0] == 'S')
		new = sub_protect(str, all, 0, 6);
	else
		new = sub_protect(str, all, 0, 18);
	if (!new && errno == 12)
		memory_allocation_failed(all);
	free(str);
	str = ft_itoa(i);
	if (!str && errno == 12)
	{
		free(new);
		memory_allocation_failed(all);
	}
	new = ft_strjoin_free(new, str);
	free(str);
	if (!new && errno == 12)
		memory_allocation_failed(all);
	return (new);
}

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
		if (!ft_strncmp2("SHLVL", temp, 5))
			temp = change_shlvl(all, temp);
		ft_lstadd_back_chunk(&all->envp, ft_lstnewchunk(all, temp));
		i++;
	}
}

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
		ft_lstadd_back_chunk(&all->export, \
			ft_lstnewchunk(all, ft_joined_for_export(all, envp[i], j)));
		i++;
	}
	sorter_export(all);
}