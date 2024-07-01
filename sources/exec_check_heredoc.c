/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec_check_heredoc.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: adakheel <adakheel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/06/25 13:22:58 by adakheel      #+#    #+#                 */
/*   Updated: 2024/06/27 07:56:07 by adakheel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	heredoc_child(t_all *all, t_chunk *infile)
{
	char	*text;

	close(all->line->heredoc_pipe[0]);
	text = heredoc_text(all, infile);
	if (write(all->line->heredoc_pipe[1], text, ft_strlen(text)) == -1)
	{
		perror("write ");
		all->last_exit_status = 1;
		kill_process(all);
	}
	free(text);
	close(all->line->heredoc_pipe[1]);
	kill_process(all);
}

void	heredoc_parent(t_all *all, t_chunk *infile)
{
	char	buf[1024];
	int		read_number;

	close(all->line->heredoc_pipe[1]);
	free(infile->str);
	infile->str = NULL;
	while (1)
	{
		read_number = read(all->line->heredoc_pipe[0], buf, 1023);
		if (!read_number)
			break ;
		buf[read_number] = '\0';
		if (!infile->str)
		{
			infile->str = ft_strdup(buf);
			if (!infile->str)
				memory_allocation_failed(all);
		}
		else
			infile->str = ft_strjoin_free(infile->str, buf);
		if (!infile->str && errno == 12)
			memory_allocation_failed(all);
	}
	close(all->line->heredoc_pipe[0]);
}

int	check_heredoc_fork(t_all *all, pid_t p, t_chunk *infile, int status)
{
	pid_t	wpid;

	if (pipe(all->line->heredoc_pipe) == -1)
	{
		perror("pipe ");
		all->last_exit_status = 1;
		kill_process(all);
	}
	p = fork();
	if (p < 0)
	{
		perror("fork ");
		all->last_exit_status = 1;
		kill_process(all);
	}
	else if (p == 0)
		heredoc_child(all, infile);
	else if (p > 0)
		heredoc_parent(all, infile);
	wpid = waitpid(p, &status, 0);
	if (wpid == -1)
		all->last_exit_status = 1;
	return (status);
}

void	check_heredoc(t_all *all, pid_t p, int status)
{
	t_chunk	*infile;
	t_cmd	*cmd;

	cmd = all->line->each_cmd;
	while (cmd)
	{
		infile = cmd->infile;
		while (infile)
		{
			if (infile->is_heredoc)
			{
				status = check_heredoc_fork(all, p, infile, status);
				if (WIFEXITED(status))
					all->last_exit_status = (WEXITSTATUS(status));
				else if (WIFSIGNALED(status))
					all->last_exit_status = 128 + (WTERMSIG(status));
				if (all->last_exit_status == 130)
					return ;
			}
			infile = infile->next;
		}
		cmd = cmd->next;
	}
}
