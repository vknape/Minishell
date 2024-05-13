/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: adakheel <adakheel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/08 09:40:42 by adakheel      #+#    #+#                 */
/*   Updated: 2024/05/13 14:40:22 by adakheel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// char	*heredoc_text(t_chunk *infile)
// {
// 	char	*line;
// 	char	*temp;

// 	line = NULL;
// 	temp = NULL;
// 	line = get_next_line(0);
// 	if (!line)
// 		return (NULL);
// 	while (1)
// 	{
// 		if (!ft_strncmp(line, infile->lim, ft_strlen(infile->lim)) && \
// 			ft_strlen(line) - 1 == ft_strlen(infile->lim))
// 		{
// 			free(line);
// 			return (temp);
// 		}
// 		if (!temp)
// 			temp = ft_strdup(line);
// 		else
// 		{
// 			temp = ft_strjoin_free(temp, line);
// 			free(line);
// 		}
// 		line = get_next_line(0);
// 	}
// }

void	handle_infiles(t_all *all, t_chunk *infile)
{
	int		fd;
	char	*text;

	while (infile)
	{
		if (infile->is_infile)
		{
			fd = open(infile->str, O_RDONLY);
			if (!infile->next)
				dup2(fd, STDIN_FILENO);
			close(fd);
		}
		if (infile->is_heredoc)
		{
			// text = heredoc_text(infile);
			// if (!infile->next)
			// {
			// 	pipe(all->line->heredoc_pipe);
			// 	write(all->line->heredoc_pipe[1], text, ft_strlen(text));
			// 	close(all->line->heredoc_pipe[1]);
			// 	dup2(all->line->heredoc_pipe[0], STDIN_FILENO);
			// }
			// free(text);
			exit(1);
		}
		infile = infile->next;
	}
}

void	handle_outfiles(t_chunk *outfile)
{
	int fd;

	while (outfile)
	{
		if (outfile->is_outfile)
		{
			fd = open(outfile->str, O_WRONLY | O_CREAT | O_TRUNC, 0777);
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
	}
	
}

void	exec_cmd(t_all *all)
{
	// printf("here\n");
	get_path(all);
	// printf("here\n");
	// printf("%s\n", all->line->each_cmd->cmd[0]);
	// printf("%s\n", all->line->each_cmd->cmd[1]);
	execve(all->line->each_cmd->cmd[0], all->line->each_cmd->cmd, all->envpcpy);
	exit(1);
}

void	exec_builtin(t_all *all)
{
	if (!ft_strncmp("echo", all->line->each_cmd->cmd[0], 5))
		ft_echo_quotes(all, all->line->each_cmd->cmd);
	if (!ft_strncmp("cd", all->line->each_cmd->cmd[0], 3))
		ft_cd(all);
	if (!ft_strncmp("pwd", all->line->each_cmd->cmd[0], 4))
		ft_pwd();
	if (!ft_strncmp("export", all->line->each_cmd->cmd[0], 7))
		ft_export(all);
	if (!ft_strncmp("unset", all->line->each_cmd->cmd[0], 6))
		ft_unset(all, all->line->each_cmd->cmd);
	if (!ft_strncmp("env", all->line->each_cmd->cmd[0], 4))
		ft_env(all);
	if (!ft_strncmp("exit", all->line->each_cmd->cmd[0], 5))
		exit(1);
	exit(1);
}

void	check_scenario(t_all *all)
{
	// printf("%d\n", all->line->each_cmd->is_builtin);
	// dup2(all->line->pipe[1], STDOUT_FILENO);
	// printf("%d\n", all->line->each_cmd->infile);
	if (all->line->each_cmd->infile)
	{
		// printf("%s\n", all->line->each_cmd->infile->str);
		handle_infiles(all, all->line->each_cmd->infile);
	}
	// printf("%d\n", all->line->each_cmd->is_builtin);
	if (all->line->each_cmd->outfile)
	{
		handle_outfiles(all->line->each_cmd->outfile);
	}
	// printf("%d\n", all->line->each_cmd->is_builtin);
	if (all->line->each_cmd->is_builtin)
		exec_builtin(all);
	else
		exec_cmd(all);
}

pid_t	start_fork(t_all *all)
{
	pid_t p;
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
		// dprintf(2, "cmd here is %s\n", all->line->each_cmd->cmd[0]);
		close(all->line->pipe[0]);
		if (all->line->each_cmd->next)
			dup2(all->line->pipe[1], STDOUT_FILENO);
		else
			dup2(all->stdoutfd, STDOUT_FILENO);
		close(all->line->pipe[1]);
		check_scenario(all);
		
	}
}

void	start_exec(t_all *all)
{
	pid_t	p;
	pid_t	wpid;
	int		status;

	// dprintf(2, "cmd here is%s\n", all->line->each_cmd->cmd[0]);
	// dprintf(2, "cmd here is%s\n", all->line->each_cmd->next->cmd[0]);
	while (all->line->each_cmd)
	{
		// dprintf(2, "heregdgfdg\n");
		pipe(all->line->pipe);
		p = start_fork(all);
		all->line->each_cmd = all->line->each_cmd->next;
	}
	wpid = waitpid(p, &status, 0);
	while (wait(NULL) != -1)
		;
}
