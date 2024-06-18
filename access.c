/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   access.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: adakheel <adakheel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/08 11:52:52 by adakheel      #+#    #+#                 */
/*   Updated: 2024/06/18 10:58:18 by adakheel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*combine_str(char *str, char *slash, char *cmd)
{
	char	*temp;
	char	*path;

	if (!cmd)
		return (NULL);
	temp = ft_strjoin(str, slash);
	if (!temp)
		return (NULL);
	path = ft_strjoin(temp, cmd);
	if (!path)
	{
		free(temp);
		return (NULL);
	}
	free(temp);
	return (path);
}


char	*ft_gethome(t_all *all)
{
	t_chunk		*temp;
	char		*str;

	temp = all->envp;
	while (temp)
	{
		if (!ft_strncmp2(temp->str, "HOME=", 5))
		{
			str = ft_substr(temp->str, 6, ft_strlen(temp->str));
			if (!str && errno == 12)
				memory_allocation_failed(all);
			return (str);
		}
		temp = temp->next;
	}
	return (NULL);
}

char	*check_acces_path(t_all *all, char *cmd)
{
	char	*path;
	char	*temp;

	path = NULL;
	if (cmd[0] == '~')
	{
		path = ft_gethome(all);
		temp = ft_strjoin("/", path);
		free(path);
		if (!temp && errno == 12)
			memory_allocation_failed(all);
		path = ft_strjoin_free(temp, cmd + 1);
		if (!path && errno == 12)
			memory_allocation_failed(all);
	}
	else if (cmd[0] == '.')
	{
		path = ft_strjoin_free(get_current_dir(all), "/");
		if (!path && errno == 12)
			memory_allocation_failed(all);
		path = ft_strjoin_free(path, cmd);
		if (!path && errno == 12)
			memory_allocation_failed(all);
	}
	return (path);
}

char	*check_access(t_all *all, char **all_paths, char *cmd)
{
	int		i;
	char	*path;
	char	*temp;

	i = 0;
	while (all_paths[i])
	{
		path = combine_str(all_paths[i], "/", cmd);
		if (!path && errno == 12)
			memory_allocation_failed(all);
		if (access(path, F_OK | X_OK) == 0)
			return (path);
		free(path);
		i++;
	}
	path = check_acces_path(all, cmd);
	if ((cmd[0] == '~' || cmd[0] == '.') && access(path, F_OK | X_OK) == 0)
		return (path);
	else
	{
		create_print_error(all, cmd, 1);
		return (NULL);
	}
}

char	*get_path(t_all *all, t_cmd *cmd)
{
	char	*path;
	char	**all_paths;
	int		i;

	i = 0;
	while (ft_strncmp("PATH", all->envcur[i], 4))
		i++;
	all_paths = ft_split((all->envcur[i] + 5), ':');
	if (!all_paths && errno == 12)
		memory_allocation_failed(all);
	path = check_access(all, all_paths, cmd->cmd[0]);
	free2d(all_paths);
	if (path)
	{
		cmd->path_found = 1;
		return (path);
	}
	else
	{
		cmd->path_found = 0;
		all->last_exit_status = 127;
		return (NULL);
	}
}
