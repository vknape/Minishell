/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   free.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: adakheel <adakheel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/20 13:02:28 by adakheel      #+#    #+#                 */
/*   Updated: 2024/06/27 07:56:37 by adakheel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free2d(char **str)
{
	int	i;

	i = 0;
	if (!str)
		return ;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

void	free_chunk(t_chunk **chunk)
{
	t_chunk	*temp;

	while (chunk && *chunk)
	{
		free((*chunk)->str);
		temp = (*chunk)->next;
		free(*chunk);
		*chunk = temp;
	}
	chunk = NULL;
}

void	free_cmd(t_cmd **cmd)
{
	t_cmd	*temp;

	while (cmd && *cmd)
	{
		free_chunk(&(*cmd)->delimiter);
		free_chunk(&(*cmd)->infile);
		free_chunk(&(*cmd)->outfile);
		free2d((*cmd)->cmd);
		free((*cmd)->templine);
		temp = (*cmd)->next;
		free(*cmd);
		*cmd = temp;
	}
	cmd = NULL;
}

void	free_line(t_line **line)
{
	if (!line)
		return ;
	if (line && *line)
	{
		free2d((*line)->splits);
		if ((*line)->temp)
			free((*line)->temp);
		if ((*line)->curline)
			free((*line)->curline);
		free_chunk(&(*line)->chunks);
		free_cmd(&(*line)->each_cmd);
		free_chunk(&(*line)->tempchunk);
		free(*line);
	}
	line = NULL;
}

void	free_all(t_all **all)
{
	if (!all)
		return ;
	if (all && *all)
	{
		rl_clear_history();
		free_line(&(*all)->line);
		if ((*all)->lastwd)
			free((*all)->lastwd);
		free_chunk(&(*all)->envp);
		free_chunk(&(*all)->export);
		free2d((*all)->envcur);
		dup2((*all)->stdinfd, STDIN_FILENO);
		dup2((*all)->stdoutfd, STDOUT_FILENO);
		close((*all)->stdinfd);
		close((*all)->stdoutfd);
		free((*all));
	}
	all = NULL;
}
