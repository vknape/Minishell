/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtins_export2.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: adakheel <adakheel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/06/25 13:07:03 by adakheel      #+#    #+#                 */
/*   Updated: 2024/07/01 11:07:42 by adakheel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_in_export(t_chunk *node, char *str)
{
	t_chunk	*temp;
	int		i;

	temp = node;
	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	while (temp)
	{
		if (!ft_strncmp(temp->str + 11, str, i))
		{
			if (str[i])
				return (2);
			else
				return (1);
		}
		temp = temp->next;
	}
	return (0);
}

char	*ft_joined_for_export2(t_all	*all, char *str, char *temp2, int start)
{
	char	*temp1;

	temp1 = ft_strjoin(temp2, "\"");
	free(temp2);
	if (!temp1 && errno == 12)
		memory_allocation_failed(all);
	temp2 = ft_substr(str, start + 1, ft_strlen(str) - (start + 1));
	if (!temp2 && errno == 12)
	{
		free(temp1);
		memory_allocation_failed(all);
	}
	temp1 = ft_strjoin_free(temp1, temp2);
	free(temp2);
	if (!temp1 && errno == 12)
		memory_allocation_failed(all);
	if (!ft_strncmp2("declare -x SHLVL", temp1, 17))
		temp1 = change_shlvl(all, temp1);
	temp2 = ft_strjoin_free(temp1, "\"");
	if (!temp2 && errno == 12)
		memory_allocation_failed(all);
	return (temp2);
}

char	*ft_joined_for_export(t_all	*all, char *str, int start)
{
	char	*temp1;
	char	*temp2;
	char	*temp3;

	temp1 = ft_substr(str, 0, start + 1);
	if (!temp1 && errno == 12)
		memory_allocation_failed(all);
	temp2 = ft_strjoin("declare -x ", temp1);
	free(temp1);
	if (!temp2 && errno == 12)
		memory_allocation_failed(all);
	if (str[start] == '=')
		temp2 = ft_joined_for_export2(all, str, temp2, start);
	return (temp2);
}

void	update_export2(t_all *all, char *str, char *temp, int i)
{
	char	*temp2;

	temp2 = ft_substr(str, 0, i);
	if (!temp2 && errno == 12)
		memory_allocation_failed(all);
	temp = ft_strjoin("declare -x ", temp2);
	free(temp2);
	if (!temp && errno == 12)
		memory_allocation_failed(all);
	ft_remove_var(all->export, temp);
	free(temp);
	temp = ft_joined_for_export(all, str, i);
	ft_lstadd_back_chunk(&all->export, ft_lstnewchunk(all, temp));
}

void	update_export(t_all *all, char *str, int varvalue)
{
	int		i;
	char	*temp;
	t_chunk	*list;

	list = all->export;
	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	if (varvalue == 1 && is_in_export(list, str) > 0)
		return ;
	else if (varvalue > 0 && is_in_export(list, str) == 0)
	{
		temp = ft_joined_for_export(all, str, i);
		ft_lstadd_back_chunk(&all->export, ft_lstnewchunk(all, temp));
	}
	else if (varvalue == 2 && is_in_export(list, str) > 0)
		update_export2(all, str, temp, i);
}
