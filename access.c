/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   access.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: adakheel <adakheel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/08 11:52:52 by adakheel      #+#    #+#                 */
/*   Updated: 2024/06/05 14:38:12 by adakheel      ########   odam.nl         */
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

// char	*check_access(char **all_paths, char *cmd)
// {
// 	int		i;
// 	char	*path;

// 	i = 0;
// 	while (all_paths[i])
// 	{
// 		path = combine_str(all_paths[i], "/", cmd);
// 		// dprintf(2, "path is (%s)\n", path);
// 		if (access(path, F_OK | X_OK) == -1 && all_paths[i + 1] == NULL)
// 		{
// 			perror("minishell: ");
// 			free(path);
// 			free2d(all_paths);
// 			return (NULL);
// 		}
// 		else if (access(path, F_OK | X_OK) == 0)
// 			return (path);
// 		free(path);
// 		i++;
// 	}
// 	free2d(all_paths);
// 	return (NULL);
// }

char	*ft_gethome(t_all *all)
{
	t_chunk		*temp;

	temp = all->envp;
	while (temp)
	{
		if (!ft_strncmp2(temp->str, "HOME=", 5))
		{
			return (ft_substr(temp->str, 6, ft_strlen(temp->str)));
		}
		temp = temp->next;
	}
	return (NULL);
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
		// dprintf(2, "path is (%s)\n", path);
		// if (access(path, F_OK | X_OK) == -1 && all_paths[i + 1] == NULL)
		// {
		// 	perror("minishell: ");
		// 	free(path);
		// 	free2d(all_paths);
		// 	return (NULL);
		// }
		if (access(path, F_OK | X_OK) == 0)
			return (path);
		free(path);
		i++;
	}
	if (cmd[0] == '~')
	{
		path = ft_gethome(all);
		temp = ft_strjoin("/", path);
		free(path);
		path = ft_strjoin_free(temp, cmd + 1);
		dprintf(2, "path = (%s)\n", path);
	}
	else if (cmd[0] == '.')
	{
		path = ft_strjoin_free(get_current_dir(), "/");
		path = ft_strjoin_free(path, cmd);
	}
	// free(cmd);
	if ((cmd[0] == '~' || cmd[0] == '.') && access(path, F_OK | X_OK) == 0)
	{
		// dprintf(2, "cmd found\n");
		// if (cmd[0] == '.')
		// {
		// 	path = ft_strjoin_free(get_current_dir(), "/");
		// 	path = ft_strjoin_free(path, cmd);
		// }
		// else
		// {
		// 	path = ft_gethome(all);
		// 	path = ft_strjoin_free(path, "/");
		// 	path = ft_strjoin_free(path, cmd);
		// 	dprintf(2, "path = (%s)\n", path);
		// }
		// free(cmd);
		return (path);
	}
	else
	{
		// free(path);
		perror(cmd);
		return (NULL);
	}
}

void	get_path(t_all *all, t_cmd *cmd)
{
	char	*path;
	char	**all_paths;
	int		i;

	i = 0;
	// dprintf(2, "command here is (%s)\n", cmd->cmd[0]);
	while (ft_strncmp("PATH", all->envcur[i], 4))
		i++;
	all_paths = ft_split((all->envcur[i] + 5), ':');
	path = check_access(all, all_paths, cmd->cmd[0]);
	free2d(all_paths);
	if (path)
	{
		cmd->path_found = 1;
		free(cmd->cmd[0]);
		cmd->cmd[0] = path;
	}
	else
	{
		// dprintf(2, "no command\n");
		cmd->path_found = 0;
		all->last_exit_status = 127;
	}
}
