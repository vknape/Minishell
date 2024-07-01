/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec_start_fork.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: adakheel <adakheel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/06/25 13:47:18 by adakheel      #+#    #+#                 */
/*   Updated: 2024/06/27 07:56:20 by adakheel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exec_cmd(t_all *all, t_cmd *cmd)
{
	char	*path;

	path = get_path(all, cmd);
	if (cmd->path_found == 0)
		kill_process(all);
	close(all->stdinfd);
	close(all->stdoutfd);
	signal(SIGQUIT, SIG_DFL);
	if (execve(path, cmd->cmd, all->envcur) == -1)
	{
		free(path);
		perror("execve ");
		all->last_exit_status = 1;
		kill_process(all);
	}
}

void	check_scenario(t_all *all, t_cmd *cmd)
{
	if (cmd->infile)
	{
		handle_infiles(all, cmd->infile);
		if (g_glob == 2)
			return ;
	}
	if (cmd->outfile)
		handle_outfiles(all, cmd->outfile);
	if (cmd->is_builtin)
		exec_builtin(all, cmd, 1);
	else
		exec_cmd(all, cmd);
}

pid_t	start_fork_1cmd(t_all *all, t_cmd *cmd)
{
	pid_t	p;

	p = fork();
	if (p == -1)
	{
		perror("fork ");
		all->last_exit_status = 1;
		kill_process(all);
	}
	if (p > 0)
	{
		//Parent process: Do nothing
	}
	else if (p == 0)
	{
		check_scenario(all, cmd);
	}
	return (p);
}

void	start_fork_child(t_all *all, t_cmd *cmd)
{
	close(all->line->pipe[0]);
	if (cmd->next)
	{
		if (dup2(all->line->pipe[1], STDOUT_FILENO) == -1)
		{
			perror("dup2 ");
			all->last_exit_status = 1;
			kill_process(all);
		}
	}
	else
	{
		if (dup2(all->stdoutfd, STDOUT_FILENO) == -1)
		{
			perror("dup2 ");
			all->last_exit_status = 1;
			kill_process(all);
		}
	}
	close(all->line->pipe[1]);
	check_scenario(all, cmd);
}

pid_t	start_fork(t_all *all, t_cmd *cmd)
{
	pid_t	p;

	p = fork();
	if (p == -1)
	{
		perror("fork ");
		all->last_exit_status = 1;
		kill_process(all);
	}
	if (p > 0 && cmd->next)
	{
		close(all->line->pipe[1]);
		if (dup2(all->line->pipe[0], STDIN_FILENO) == -1)
		{
			perror("dup2 ");
			all->last_exit_status = 1;
			kill_process(all);
		}
		close(all->line->pipe[0]);
	}
	else if (p == 0)
		start_fork_child(all, cmd);
	return (p);
}
