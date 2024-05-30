/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   free.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: adakheel <adakheel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/20 13:02:28 by adakheel      #+#    #+#                 */
/*   Updated: 2024/05/30 14:26:58 by adakheel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

// void	free_chunk(t_chunk **chunk)
// {
// 	t_chunk	*temp;
// 	t_chunk	*temp2;
	
	
// 	temp = *chunk;
// 	while (temp)
// 	{
// 		free(temp->str);
// 		temp2 = temp;
// 		temp = temp->next;
// 		free(temp2);
// 	}
// 	chunk = NULL;
// }

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

// void	free_cmd(t_cmd **cmd)
// {
// 	t_cmd	*temp;
// 	t_cmd	*temp2;

// 	temp = *cmd;
// 	while (temp)
// 	{
// 		free_chunk(&temp->delimiter);
// 		free_chunk(&temp->infile);
// 		free_chunk(&temp->outfile);
// 		free2d(temp->cmd);
// 		if (temp->templine)
// 			free(temp->templine);
// 		temp2 = temp;
// 		temp = temp->next;
// 		free(temp2);
// 	}
// 	cmd = NULL;
// }

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
		if ((*line)->saved_line)
			free((*line)->saved_line);
		free_chunk(&(*line)->chunks);
		free_cmd(&(*line)->each_cmd);
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
		dup2((*all)->stdinfd, STDIN_FILENO);
		dup2((*all)->stdoutfd, STDOUT_FILENO);
		close((*all)->stdinfd);
		close((*all)->stdoutfd);
		free((*all));
		// close(STDOUT_FILENO);
		// close(STDIN_FILENO);
	}
	all = NULL;
}
