/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec_handle_file.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: adakheel <adakheel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/06/25 13:38:58 by adakheel      #+#    #+#                 */
/*   Updated: 2024/06/27 07:56:11 by adakheel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_infiles_if_heredoc(t_all *all, t_chunk *infile)
{
	if (!infile->next)
	{
		if (pipe(all->line->heredoc_pipe) == -1)
		{
			perror("pipe ");
			all->last_exit_status = 1;
			kill_process(all);
		}
		if (write(all->line->heredoc_pipe[1], infile->str, ft_strlen(infile->str)) == -1)
		{
			perror("write ");
			all->last_exit_status = 1;
			kill_process(all);
		}
		close(all->line->heredoc_pipe[1]);
		if (dup2(all->line->heredoc_pipe[0], STDIN_FILENO) == -1)
		{
			perror("dup2 ");
			all->last_exit_status = 1;
			kill_process(all);
		}
		close(all->line->heredoc_pipe[0]);
	}
}

void	handle_infiles(t_all *all, t_chunk *infile)
{
	int		fd;

	while (infile)
	{
		if (infile->is_infile)
		{
			fd = open(infile->str, O_RDONLY);
			if (fd == -1)
				free_open_faild(all, infile->str);
			if (!infile->next)
			{
				if (dup2(fd, STDIN_FILENO) == -1)
				{
					perror("dup2 ");
					all->last_exit_status = 1;
					kill_process(all);
				}
			}
			close(fd);
		}
		if (infile->is_heredoc)
			handle_infiles_if_heredoc(all, infile);
		infile = infile->next;
	}
}

void	handle_outfiles_if_append(t_all *all, t_chunk *outfile, int fd)
{
	fd = open(outfile->str, O_WRONLY | O_CREAT | O_APPEND, 0777);
	if (fd == -1)
		free_open_faild(all, outfile->str);
	if (!outfile->next)
	{
		if (dup2(fd, STDOUT_FILENO) == -1)
		{
			perror("dup2 ");
			all->last_exit_status = 1;
			kill_process(all);
		}
	}
	close(fd);
}


void	handle_outfiles(t_all *all, t_chunk *outfile)
{
	int	fd;

	while (outfile)
	{
		if (outfile->is_outfile)
		{
			fd = open(outfile->str, O_WRONLY | O_CREAT | O_TRUNC, 0777);
			if (fd == -1)
				free_open_faild(all, outfile->str);
			if (!outfile->next)
			{
				if (dup2(fd, STDOUT_FILENO) == -1)
				{
					perror("dup2 ");
					all->last_exit_status = 1;
					kill_process(all);
				}
			}
			close(fd);
		}
		if (outfile->is_append)
			handle_outfiles_if_append(all, outfile, fd);
		outfile = outfile->next;
	}
}
