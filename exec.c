/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: adakheel <adakheel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/08 09:40:42 by adakheel      #+#    #+#                 */
/*   Updated: 2024/05/30 15:22:59 by adakheel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*heredoc_text(t_chunk *infile)
{
	char	*line;
	char	*temp;

	line = NULL;
	temp = NULL;
	// dprintf(2, "here1\n");
	// line = readline("> ");
	// dprintf(2, "here2\n");
	// if (g_glob == 2)
	// {
	// 	dprintf(2, "here2.5\n");
	// 	exit(0);
	// 	return (NULL);
	// }
	// if (!line)
	// 	return (NULL);
	while (1)
	{
		// dprintf(2, "here\n");
		line = readline("> ");
		if (!line)
			return (NULL);
		// if (g_glob == 2)
		// {
		// 	dprintf(2, "here3\n");
		// 	return (NULL);
		// }
		if (!ft_strncmp(line, infile->str, ft_strlen(infile->str)) && \
			ft_strlen(line) == ft_strlen(infile->str))
		{
			temp = ft_strjoin_free(temp, "\n");
			free(line);
			return (temp);
		}
		if (!temp)
			temp = ft_strdup(line);
		else
		{
			temp = ft_strjoin_free(temp, "\n");
			temp = ft_strjoin_free(temp, line);
			free(line);
		}
		// printf("\n");
		// rl_on_new_line();
		// rl_replace_line("\n> ", 0);
		// rl_redisplay();
		// line = readline("> ");
	}
	
}

void	handle_infiles(t_all *all, t_chunk *infile)
{
	int		fd;
	char	*text;

	while (infile)
	{
		if (infile->is_infile)
		{
			//dprintf(2, "infile name is (%s)\n", infile->str);
			fd = open(infile->str, O_RDONLY);
			if (fd == -1)
			{
				perror("can't open file: ");
			}
			if (!infile->next)
				dup2(fd, STDIN_FILENO);
			close(fd);
		}
		if (infile->is_heredoc)
		{
			text = heredoc_text(infile);
			// if (g_glob == 2)
			// {
			// 	dprintf(2, "here4\n");
			// 	return ;
			// }
			if (!infile->next)
			{
				pipe(all->line->heredoc_pipe);
				write(all->line->heredoc_pipe[1], text, ft_strlen(text));
				close(all->line->heredoc_pipe[1]);
				dup2(all->line->heredoc_pipe[0], STDIN_FILENO);
				close(all->line->heredoc_pipe[0]);
			}
			free(text);
		}
		infile = infile->next;
	}
}

void	handle_outfiles(t_chunk *outfile)
{
	int	fd;

	while (outfile)
	{
		if (outfile->is_outfile)
		{
			// dprintf(2, "outfile not okay\n");
			// dprintf(2, "outfile not okay %d\n", outfile->is_outfile);
			fd = open(outfile->str, O_WRONLY | O_CREAT | O_TRUNC, 0777);
			// if (fd == -1)
				// dprintf(2, "outfile not okay %s\n", outfile->str);
			if (!outfile->next)
				dup2(fd, STDOUT_FILENO);
			close(fd);
		}
		if (outfile->is_append)
		{
			fd = open(outfile->str, O_WRONLY | O_CREAT | O_APPEND, 0777);
			if (!outfile->next)
				dup2(fd, STDOUT_FILENO);
			close(fd);
		}
		outfile = outfile->next;
	}
}

void	exec_cmd(t_all *all, t_cmd *cmd)
{
	// printf("here\n");
	get_path(all, cmd);
	if (cmd->path_found == 0)
	{
		all->line->exit_value = 127;
		ft_exit(all);
	}
	// printf("here\n");
	// printf("%s\n", all->line->each_cmd->cmd[0]);
	// printf("%s\n", all->line->each_cmd->cmd[1]);
	// dup2(all->stdinfd, STDIN_FILENO);
	// close(STDIN_FILENO);
	close(all->stdinfd);
	close(all->stdoutfd);
	execve(cmd->cmd[0], cmd->cmd, all->envpcpy);
	exit(1);
}

void	exec_builtin(t_all *all, t_cmd *cmd)
{
	// printf("we got here %s\n", all->line->each_cmd->cmd[0]);
	if (!ft_strncmp("echo", cmd->cmd[0], 5))
		ft_echo_quotes(all, cmd->cmd);
	if (!ft_strncmp("cd", cmd->cmd[0], 3))
		ft_cd(all);
	if (!ft_strncmp("pwd", cmd->cmd[0], 4))
		ft_pwd();
	if (!ft_strncmp("export", cmd->cmd[0], 7))
		ft_export(all);
	if (!ft_strncmp("unset", cmd->cmd[0], 6))
		ft_unset(all, cmd->cmd);
	if (!ft_strncmp("env", cmd->cmd[0], 4))
		ft_env(all);
	if (!ft_strncmp("exit", cmd->cmd[0], 5))
	{
		ft_exit(all);
		// free_all(&all);
		// exit(1);
	}
	// free_all(&all);
	ft_exit(all);
}

void	check_scenario(t_all *all, t_cmd *cmd)
{
	// printf("%d\n", all->line->each_cmd->is_builtin);
	// dup2(all->line->pipe[1], STDOUT_FILENO);
	// printf("%d\n", all->line->each_cmd->infile);
	// dprintf(2, "outfile not okay\n");
	if (cmd->infile)
	{
		// printf("%s\n", cmd->infile->str);
		// dprintf(2, "outfile not okay\n");
		handle_infiles(all, cmd->infile);
		if (g_glob == 2)
		{
			//dprintf(2, "here\n");
			return ;
		}
	}
	// printf("%d\n", cmd->is_builtin);
	if (cmd->outfile)
	{
		// dprintf(2, "outfile not okay\n");
		handle_outfiles(cmd->outfile);
	}
	// printf("%d\n", cmd->is_builtin);
	if (cmd->is_builtin)
		exec_builtin(all, cmd);
	else
		exec_cmd(all, cmd);
}

pid_t	start_fork(t_all *all, t_cmd *cmd)
{
	pid_t	p;
	// dprintf(2, "outfile not okay %d\n", all->line->each_cmd->outfile->is_outfile);
	p = fork();
	if(p == -1)
		exit(1);
	if (p > 0)
	{
		close(all->line->pipe[1]);
		dup2(all->line->pipe[0], STDIN_FILENO);
		close(all->line->pipe[0]);
	}
	else if (p == 0)
	{
		all->sa.sa_handler = &sigchild;

		if (sigaction(SIGINT, &all->sa, NULL) == -1)
		{
			// free_all(&all);
			// printf("\n");
			// rl_on_new_line();
			// rl_replace_line("", 0);
			// rl_redisplay();
			// printf("\n");
			ft_exit(all);
		}
		// dprintf(2, "cmd here is %s\n", all->line->each_cmd->cmd[0]);
		close(all->line->pipe[0]);
		if (cmd->next)
			dup2(all->line->pipe[1], STDOUT_FILENO);
		else
			dup2(all->stdoutfd, STDOUT_FILENO);
		close(all->line->pipe[1]);
		// dprintf(2, "outfile not okay %d\n", all->line->each_cmd->outfile->is_outfile);
		check_scenario(all, cmd);
		// free_all(&all);
		//dprintf(2, "end\n");
		// exit(0);
	}
	return (p);
}

pid_t	start_fork_1cmd(t_all *all, t_cmd *cmd)
{
	pid_t	p;
	// dprintf(2, "outfile not okay %d\n", all->line->each_cmd->outfile->is_outfile);
	p = fork();
	if(p == -1)
		exit(1);
	if (p > 0)
	{
		;
	}
	else if (p == 0)
	{
		all->sa.sa_handler = &sigchild;

		if (sigaction(SIGINT, &all->sa, NULL) == -1)
		{
			free_all(&all);
			// printf("\n");
			// rl_on_new_line();
			// rl_replace_line("", 0);
			// rl_redisplay();
			// printf("\n");
			ft_exit(all);
		}
		// dprintf(2, "cmd here is %s\n", all->line->each_cmd->cmd[0]);
		// dup2(all->stdoutfd, STDOUT_FILENO);
		// dprintf(2, "outfile not okay %d\n", all->line->each_cmd->outfile->is_outfile);
		check_scenario(all, cmd);
		// free_all(&all);
		//dprintf(2, "end\n");
		// exit(0);
	}
	return (p);
}

void	start_exec(t_all *all)
{
	t_cmd	*temp;
	pid_t	p;
	pid_t	wpid;
	int		status;
	// dprintf(2, "outfile not okay %d\n", all->line->each_cmd->outfile->is_outfile);
	// dprintf(2, "cmd here is%s\n", all->line->each_cmd->cmd[0]);
	// dprintf(2, "cmd here is%s\n", all->line->each_cmd->next->cmd[0]);
	p = 0;
	temp = all->line->each_cmd;
	while (temp)
	{
		if (all->line->total_cmd == 1 && all->line->each_cmd->is_builtin)
		{
			// dprintf(2, "here\n");
			if (!ft_strncmp("echo", temp->cmd[0], 5))
				ft_echo_quotes(all, temp->cmd);
			if (!ft_strncmp("cd", temp->cmd[0], 3))
				ft_cd(all);
			if (!ft_strncmp("pwd", temp->cmd[0], 4))
				ft_pwd();
			if (!ft_strncmp("export", temp->cmd[0], 7))
				ft_export(all);
			if (!ft_strncmp("unset", temp->cmd[0], 6))
				ft_unset(all, temp->cmd);
			if (!ft_strncmp("env", temp->cmd[0], 4))
				ft_env(all);
			if (!ft_strncmp("exit", temp->cmd[0], 5))
			{
				// free_all(&all);
				ft_exit(all);
			}
		}
		else
		{
			if (all->line->total_cmd > 1)
			{
				if (temp->next)
					pipe(all->line->pipe);
				p = start_fork(all, temp);
			}
			else
				p = start_fork_1cmd(all, temp);
		}
		temp = temp->next;
	}
	if (p)
	{
		wpid = waitpid(p, &status, 0);
		if (wpid == -1)
			all->last_exit_status = 1;
		if (WIFEXITED(status))
			all->last_exit_status = (WEXITSTATUS(status));
		else if (WIFSIGNALED(status))
			all->last_exit_status = 128 + (WTERMSIG(status));
		while (wait(NULL) != -1)
			;
	}
}
