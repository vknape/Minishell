/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec_heredoc_text.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: adakheel <adakheel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/06/25 13:26:16 by adakheel      #+#    #+#                 */
/*   Updated: 2024/06/27 07:56:15 by adakheel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	heredoc_text_join_text(t_all *all, t_chunk *infile, char **line, char **temp)
{
	if (!*temp)
	{
		*temp = ft_strdup(*line);
		free(*line);
		if (!(*temp) && errno == 12)
			memory_allocation_failed(all);
	}
	else
	{
		*temp = ft_strjoin_free(*temp, "\n");
		if (!(*temp) && errno == 12)
		{
			free(*line);
			memory_allocation_failed(all);
		}
		*temp = ft_strjoin_free(*temp, *line);
		free(*line);
		if (!(*temp) && errno == 12)
			memory_allocation_failed(all);
	}
}

char	*heredoc_text_get_dilm(t_all *all, t_chunk *infile, char **line, char **temp)
{
	if (!*temp)
	{
		free(*line);
		return (NULL);
	}
	*temp = ft_strjoin_free(*temp, "\n");
	free(*line);
	if (!(*temp) && errno == 12)
		memory_allocation_failed(all);
	return (*temp);
}

char	*heredoc_text_endoffile(t_all *all, t_chunk *infile, char **line, char **temp)
{
	*line = ft_strjoin("wanted ", infile->str);
	if (!(*line) && errno == 12)
		memory_allocation_failed(all);
	create_print_error(all, *line, 7);
	free(*line);
	if (*temp)
		*temp = ft_strjoin_free(*temp, "\n");
	if (!(*temp) && errno == 12)
		memory_allocation_failed(all);
	return (*temp);
}

char	*heredoc_text(t_all *all, t_chunk *infile)
{
	char	*line;
	char	*temp;

	line = NULL;
	temp = NULL;
	if (signal(SIGINT, SIG_DFL) == SIG_ERR)
	{
		free(line);
		free(temp);
		kill_process(all);
	}
	while (1)
	{
		line = readline("> ");
		if (!line)
			return (heredoc_text_endoffile(all, infile, &line, &temp));
		if (!ft_strncmp(line, infile->str, ft_strlen(infile->str)) && \
			ft_strlen(line) == ft_strlen(infile->str))
			return (heredoc_text_get_dilm(all, infile, &line, &temp));
		else
			heredoc_text_join_text(all, infile, &line, &temp);
	}
}
