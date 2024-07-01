/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtins_export.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: adakheel <adakheel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/06/25 12:57:14 by adakheel      #+#    #+#                 */
/*   Updated: 2024/06/27 07:55:46 by adakheel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_printexport(t_all *all)
{
	t_chunk	*chunks;

	chunks = all->export;
	while (chunks)
	{
		printf("%s\n", chunks->str);
		chunks = chunks->next;
	}
}

int	check_export_in(t_all *all, char *str)
{
	int	i;

	i = 0;
	if (ft_strchr("1234567890=", str[0]))
	{
		create_print_error(all, str, 4);
		all->last_exit_status = 1;
		return (0);
	}
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum_under(str[i]))
		{
			create_print_error(all, str, 4);
			all->last_exit_status = 1;
			return (0);
		}
		i++;
	}
	if (str[i] && str[i] == '=')
		return (2);
	else
		return (1);
}

int	is_in_envp(t_chunk *node, char *str)
{
	t_chunk	*temp;
	int		i;

	temp = node;
	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	while (temp)
	{
		if (!ft_strncmp(temp->str, str, i))
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

void	update_envp(t_all *all, char *str, int varvalue)
{
	int		i;
	char	*temp;
	char	*to_remove;
	t_chunk	*list;

	list = all->envp;
	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	if (varvalue != 2)
		return ;
	if (is_in_envp(list, str) > 0)
	{
		to_remove = sub_protect(str, all, 0, i);
		ft_remove_var(all->envp, to_remove);
		free(to_remove);
	}
	temp = dup_protect(str, all);
	ft_lstadd_back_chunk(&all->envp, ft_lstnewchunk(all, temp));
}

void	ft_export(t_all *all)
{
	int		index;
	int		varvalue;

	index = 1;
	if (!all->line->each_cmd->cmd[1])
		ft_printexport(all);
	else
	{
		while (all->line->each_cmd->cmd[index])
		{
			varvalue = check_export_in(all, all->line->each_cmd->cmd[index]);
			if (varvalue == 1)
				update_export(all, all->line->each_cmd->cmd[index], varvalue);
			if (varvalue == 2)
			{
				update_envp(all, all->line->each_cmd->cmd[index], varvalue);
				update_export(all, all->line->each_cmd->cmd[index], varvalue);
				if (all->envcur)
					free2d(all->envcur);
				all->envcur = update_env(all);
			}
			index++;
		}
		sorter_export(all);
	}
}
