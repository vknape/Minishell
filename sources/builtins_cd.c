/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtins_cd.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: adakheel <adakheel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/06/25 11:57:44 by adakheel      #+#    #+#                 */
/*   Updated: 2024/07/01 11:24:00 by adakheel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	update_pwd_oldpwd(t_all *all, char *oldpwd)
{
	char	*temp;

	all->line->temp = ft_strjoin("OLDPWD=", oldpwd);
	if (!all->line->temp && errno == 12)
	{
		free(oldpwd);
		memory_allocation_failed(all);
	}
	free(oldpwd);
	update_envp(all, all->line->temp, 2);
	update_export(all, all->line->temp, 2);
	free(all->line->temp);
	all->line->temp = NULL;
	update_pwd(all);
	if (all->envcur)
		free2d(all->envcur);
	all->envcur = update_env(all);
	sorter_export(all);
}

char	*create_new_path2(t_all *all, char **array)
{
	char	*dir;
	char	*new_dir;

	new_dir = value_of_dollar_sign(all, "OLDPWD", 7);
	if (!new_dir && errno == 12)
		memory_allocation_failed(all);
	dir = remove_quotes_cmd(new_dir, 1);
	if (!dir && errno == 12)
		memory_allocation_failed(all);
	if (dir[0])
	{
		write (1, dir, ft_strlen(dir));
		write (1, "\n", 1);
	}
	return (dir);
}

char	*create_new_path(t_all *all, char **array)
{
	char	*dir;
	char	*new_dir;

	if (!array[1] || array[1][0] == '~')
	{
		new_dir = value_of_dollar_sign(all, "HOME", 4);
		if (!new_dir && errno == 12)
			memory_allocation_failed(all);
		dir = remove_quotes_cmd(new_dir, 1);
		if (!dir && errno == 12)
			memory_allocation_failed(all);
		if (array[1] && array[1][1])
		{
			new_dir = ft_substr(array[1], 1, ft_strlen(array[1]));
			if (!new_dir && errno == 12)
				memory_allocation_failed(all);
			dir = ft_strjoin_free(dir, new_dir);
			free(new_dir);
			if (!dir && errno == 12)
				memory_allocation_failed(all);
		}
	}
	else if (array[1][0] == '-')
		dir = create_new_path2(all, array);
	return (dir);
}

void	ft_cd2(t_all *all, char *new_dir)
{
	char	*pwd;

	pwd = get_current_dir(all);
	if (chdir(new_dir) == -1)
	{
		create_print_error(all, new_dir, 5);
		free(new_dir);
		free(pwd);
		all->last_exit_status = 1;
		return ;
	}
	update_pwd_oldpwd(all, pwd);
	free(new_dir);
}

void	ft_cd(t_all *all)
{
	char	*new_dir;
	char	**array;
	char	*pwd;

	array = all->line->each_cmd->cmd;
	if (array[1] && array[2])
	{
		create_print_error(all, array[2], 2);
		all->last_exit_status = 1;
		return ;
	}
	if (!array[1])
		new_dir = create_new_path(all, array);
	else if (array[1][0] == '~' || array[1][0] == '-')
		new_dir = create_new_path(all, array);
	else
	{
		new_dir = ft_substr(array[1], 0, ft_strlen(array[1]));
		if (!new_dir && errno == 12)
			memory_allocation_failed(all);
	}
	ft_cd2(all, new_dir);
}
