/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtins.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: adakheel <adakheel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/06/25 13:22:42 by adakheel      #+#    #+#                 */
/*   Updated: 2024/06/27 07:55:55 by adakheel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_remove_var(t_chunk *chunk, char *str)
{
	t_chunk	*temp;
	t_chunk	*temp2;

	temp = chunk;
	if (!ft_strncmp2(str, temp->str, ft_strlen(str) + 1))
	{
		chunk = temp->next;
		free(temp);
		return ;
	}
	while (temp->next)
	{
		if (!ft_strncmp2(str, temp->next->str, ft_strlen(str) + 1))
		{
			temp2 = temp->next;
			temp->next = temp->next->next;
			free(temp2->str);
			free(temp2);
			temp2 = NULL;
			return ;
		}
		temp = temp->next;
	}
}

char	**update_env(t_all *all)
{
	t_chunk	*temp;
	int		count_nodes;
	char	**env_updated;
	int		index;

	index = 0;
	temp = all->envp;
	count_nodes = ft_lstsizechunk(temp);
	env_updated = malloc(sizeof(char *) * (count_nodes + 1));
	if (!env_updated && errno == 12)
		memory_allocation_failed(all);
	while (temp)
	{
		env_updated[index++] = ft_strdup(temp->str);
		if (!env_updated[index - 1] && errno == 12)
		{
			free2d_from_indexn(index - 1, env_updated);
			memory_allocation_failed(all);
		}
		temp = temp->next;
	}
	env_updated[index] = NULL;
	return (env_updated);
}

void	ft_unset(t_all *all, char **str)
{
	char	*c;
	int		i;

	i = 1;
	while (str[i])
	{
		c = ft_strjoin("declare -x ", str[i]);
		if (!c && errno == 12)
			memory_allocation_failed(all);
		ft_remove_var(all->envp, str[i]);
		ft_remove_var(all->export, c);
		free(c);
		i++;
	}
	if (all->envcur)
		free2d(all->envcur);
	all->envcur = update_env(all);
}

void	update_pwd(t_all *all)
{
	char	*pwd;
	char	*temp;

	pwd = get_current_dir(all);
	all->line->temp = ft_strjoin("PWD=", pwd);
	if (!all->line->temp && errno == 12)
	{
		free(pwd);
		memory_allocation_failed(all);
	}
	free(pwd);
	update_envp(all, all->line->temp, 2);
	update_export(all, all->line->temp, 2);
	free(all->line->temp);
	all->line->temp = NULL;
}

int	ft_isalnum_under(int i)
{
	if (ft_isalpha(i) || ft_isdigit(i) || i == '_')
		return (1);
	return (0);
}
