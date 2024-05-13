/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   access.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: adakheel <adakheel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/08 11:52:52 by adakheel      #+#    #+#                 */
/*   Updated: 2024/05/08 13:33:11 by adakheel      ########   odam.nl         */
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
		exit(EXIT_FAILURE);
	}
	path = ft_strjoin(temp, cmd);
	if (!path)
	{
		free(temp);
		exit(EXIT_FAILURE);
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
		if (!cmd || !path || (access(path, F_OK | X_OK) \
		== -1 && all_paths[i + 1] == NULL))
		{
			free(path);
			return (NULL);
		}
		else if (access(path, F_OK | X_OK) == 0)
			return (path);
		free(path);
		i++;
	}
	return (NULL);
}

void	get_path(t_all *all)
{
	char	*path;
	char	**all_paths;
	int		i;

	i = 0;
	while (ft_strncmp("PATH", all->envp2[i], 4))
		i++;
	all_paths = ft_split((all->envp2[i] + 5), ':');
	path = check_access(all_paths, all->line->each_cmd->cmd[0]);
	// free(all->line->each_cmd->cmd[0]);
	if (path)
		all->line->each_cmd->cmd[0] = path;
	else
		all->line->each_cmd->cmd[0] = NULL;
}
