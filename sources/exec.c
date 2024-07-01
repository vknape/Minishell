/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: adakheel <adakheel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/08 09:40:42 by adakheel      #+#    #+#                 */
/*   Updated: 2024/06/27 07:56:24 by adakheel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// char	*heredoc_text(t_all *all, t_chunk *infile)
// {
// 	char	*line;
// 	char	*temp;

// 	line = NULL;
// 	temp = NULL;
// 	if (signal(SIGINT, SIG_DFL) == SIG_ERR)
// 	{
// 		free(line);
// 		free(temp);
// 		kill_process(all);
// 	}
// 	while (1)
// 	{
// 		line = readline("> ");
// 		if (!line)
// 		{
// 			line = ft_strjoin("wanted ", infile->str);
// 			create_print_error(all, line, 7);
// 			free(line);
// 			if (temp)
// 				temp = ft_strjoin_free(temp, "\n");
// 			return (temp);
// 		}
// 		if (!ft_strncmp(line, infile->str, ft_strlen(infile->str)) && \
// 			ft_strlen(line) == ft_strlen(infile->str))
// 		{
// 			if (!temp)
// 			{
// 				free(line);
// 				return (NULL);
// 			}
// 			temp = ft_strjoin_free(temp, "\n");
// 			free(line);
// 			return (temp);
// 		}
// 		if (!temp)
// 			temp = ft_strdup(line);
// 		else
// 		{
// 			temp = ft_strjoin_free(temp, "\n");
// 			temp = ft_strjoin_free(temp, line);
// 			free(line);
// 		}
// 		// printf("\n");
// 		// rl_on_new_line();
// 		// rl_replace_line("\n> ", 0);
// 		// rl_redisplay();
// 		// line = readline("> ");
// 	}
// }

// void	handle_infiles(t_all *all, t_chunk *infile)
// {
// 	int		fd;
// 	char	*text;
// 	int		in;

// 	while (infile)
// 	{
// 		dup2(all->stdinfd, STDIN_FILENO);
// 		if (infile->is_infile)
// 		{
// 			//dprintf(2, "infile name is (%s)\n", infile->str);
// 			fd = open(infile->str, O_RDONLY);
// 			if (fd == -1)
// 			{
// 				perror("can't open file: ");
// 			}
// 			else
// 			{
// 				dup2(fd, in);
// 				close(fd);
// 			}
// 		}
// 		if (infile->is_heredoc)
// 		{
// 			dprintf(2, "last heredoc delimiter\n");
// 			pipe(all->line->heredoc_pipe);
// 			text = heredoc_text(all, infile);
// 			write(all->line->heredoc_pipe[1], text, ft_strlen(text));
// 			close(all->line->heredoc_pipe[1]);
// 			dup2(all->line->heredoc_pipe[0], in);
// 			close(all->line->heredoc_pipe[0]);
// 			free(text);
// 			// dprintf(2, "its heredoc\n");
// 			// close(STDIN_FILENO);
// 			// dup2(all->stdinfd, STDIN_FILENO);
// 			// if (g_glob == 2)
// 			// {
// 			// 	dprintf(2, "here4\n");
// 			// 	return ;
// 			// }
// 		}
// 		if (!infile->next)
// 			dup2(in, STDIN_FILENO);
// 		infile = infile->next;
// 	}
// }


void	exec_builtin(t_all *all, t_cmd *cmd, int child)
{
	if (!ft_strncmp("echo", cmd->cmd[0], 5))
		ft_echo_quotes(all, cmd->cmd);
	if (!ft_strncmp("cd", cmd->cmd[0], 3))
		ft_cd(all);
	if (!ft_strncmp("pwd", cmd->cmd[0], 4))
		ft_pwd(all);
	if (!ft_strncmp("export", cmd->cmd[0], 7))
		ft_export(all);
	if (!ft_strncmp("unset", cmd->cmd[0], 6))
		ft_unset(all, cmd->cmd);
	if (!ft_strncmp("env", cmd->cmd[0], 4))
		ft_env(all);
	if (!ft_strncmp("exit", cmd->cmd[0], 5))
	{
		ft_exit(all, cmd);
	}
	if (child)
		kill_process(all);
}

void	no_cmd(t_all *all, t_cmd *cmd)
{
	if (cmd->infile)
	{
		handle_infiles(all, cmd->infile);
		if (g_glob == 2)
		{
			return ;
		}
	}
	if (cmd->outfile)
	{
		handle_outfiles(all, cmd->outfile);
	}
}

pid_t	start_exec_which_scenario(t_all *all, t_cmd	*temp, pid_t p)
{
	temp = all->line->each_cmd;
	while (temp)
	{
		if (all->line->total_cmd == 1 && all->line->each_cmd->is_builtin)
			exec_builtin(all, temp, 0);
		else if (all->line->total_cmd > 1)
		{
			if (temp->next)
				pipe(all->line->pipe);
			p = start_fork(all, temp);
		}
		else if (all->line->total_cmd == 1 && temp->cmd)
			p = start_fork_1cmd(all, temp);
		else
			no_cmd(all, temp);
		temp = temp->next;
	}
	return (p);
}

void	start_exec(t_all *all)
{
	t_cmd	*temp;
	pid_t	p;
	pid_t	wpid;
	int		status;

	p = 0;
	check_heredoc(all, p, status);
	if (all->last_exit_status == 130)
		return ;
	p = start_exec_which_scenario(all, temp, p);
	if (p)
	{
		wpid = waitpid(p, &status, 0);
		while (wait(NULL) != -1)
			;
		if (wpid == -1)
			all->last_exit_status = 1;
		if (WIFEXITED(status))
			all->last_exit_status = (WEXITSTATUS(status));
		else if (WIFSIGNALED(status))
			all->last_exit_status = 128 + (WTERMSIG(status));
	}
}
