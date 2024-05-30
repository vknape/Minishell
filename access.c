/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   access.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: adakheel <adakheel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/08 11:52:52 by adakheel      #+#    #+#                 */
/*   Updated: 2024/05/30 09:29:35 by adakheel      ########   odam.nl         */
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
	{
		return (NULL);
	}
	path = ft_strjoin(temp, cmd);
	if (!path)
	{
		free(temp);
		return (NULL);
	}
	free(temp);
	return (path);
}

char	*check_access(char **all_paths, char *cmd)
{
	int		i;
	char	*path;

	i = 0;
	while (all_paths[i])
	{
		path = combine_str(all_paths[i], "/", cmd);
		// dprintf(2, "path is (%s)\n", path);
		if (!cmd || !path || (access(path, F_OK | X_OK) \
		== -1 && all_paths[i + 1] == NULL))
		{
			perror("minishell: ");
			free(path);
			free2d(all_paths);
			return (NULL);
		}
		else if (access(path, F_OK | X_OK) == 0)
			return (path);
		free(path);
		i++;
	}
	free2d(all_paths);
	return (NULL);
}

void	get_path(t_all *all, t_cmd *cmd)
{
	char	*path;
	char	**all_paths;
	int		i;

	i = 0;
	while (ft_strncmp("PATH", all->envpcpy[i], 4))
		i++;
	all_paths = ft_split((all->envpcpy[i] + 5), ':');
	path = check_access(all_paths, cmd->cmd[0]);
	if (path)
	{
		cmd->path_found = 1;
		cmd->cmd[0] = path;
	}
	else
	{
		cmd->path_found = 0;
	}
}
