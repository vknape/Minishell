/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: adakheel <adakheel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/06/27 07:57:08 by adakheel      #+#    #+#                 */
/*   Updated: 2024/07/01 11:43:20 by adakheel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

g_glob = 0;

void	make_line2(t_all *all)
{
	all->last_exit_status = 0;
	all->line->curline = check_input(all->line->curline, all);
	add_history(all->line->curline);
	free(all->line->curline);
	all->line->curline = NULL;
	split_cmd_nodes(all);
	remove_whitespace_quotes(all, all->line->each_cmd);
	start_exec(all);
	if (all->last_exit_status == 131)
	{
		printf("Quit (core dumped)\n");
		// printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		// rl_redisplay();
	}
}

void	make_line(t_all *all)
{
	char	*current_path;
	char	*prompt;

	all->line = ft_calloc(1, sizeof(t_line));
	current_path = get_current_dir(all);
	prompt = ft_strjoin(current_path, "$ ");
	free(current_path);
	current_path = NULL;
	if (!prompt)
		memory_allocation_failed(all);
	all->line->curline = readline(prompt);
	add_history(all->line->curline);
	free(prompt);
	prompt = NULL;
	if (!all->line->curline)
		kill_process(all);
	if (!check_space(all->line->curline))
	{
		add_history(all->line->curline);
		free(all->line->curline);
		all->line->curline = NULL;
		return ;
	}
	if (all->line->curline[0] != '\0')
		make_line2(all);
}



int	main(int argc, char **argv, char **envp)
{
	t_all	*all;

	all = ft_calloc(1, sizeof(t_all));
	all->sa.sa_handler = &sigparent;
	sigemptyset(&all->sa.sa_mask);
	all->sa.sa_flags = 0;
	all->stdinfd = dup(STDIN_FILENO);
	all->stdoutfd = dup(STDOUT_FILENO);
	if (!all)
		return (1);
	make_envp_and_set(all, envp);
	make_export(all, envp);
	all->envcur = update_env(all);
	while (1)
	{
		dup2(all->stdinfd, STDIN_FILENO);
		dup2(all->stdoutfd, STDOUT_FILENO);
		if (signal(SIGQUIT, SIG_IGN))
			g_glob = 3;
		// if (all->last_exit_status == 130)
		// {
			if (signal(SIGINT, sigparent) == SIG_ERR)
			{
				free_line(&all->line);
			}
		// }
		// else
		// {
		// 	if (signal(SIGINT, sigparent2) == SIG_ERR)
		// 	{
		// 		free_line(&all->line);
		// 	}
		// }
		// if (sigaction(SIGINT, &all->sa, NULL) == -1)// || sigaction(SIGQUIT, &all->sa, NULL) == -1)
		// {
		// 	free_line(&all->line);
		// 	// printf("\n");
		// 	// rl_on_new_line();
		// 	// rl_replace_line("", 0);
		// 	// rl_redisplay();
		// }
		// else
		// {
			make_line(all);
			free_line(&all->line);
		// }
		// make_line(all);
		// free_line(&all->line);
		// printf("\n");
		// rl_on_new_line();
		// rl_replace_line("", 0);
		// rl_redisplay();
	}
	return (0);
}
