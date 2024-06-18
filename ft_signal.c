/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_signal.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: adakheel <adakheel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/17 12:10:58 by adakheel      #+#    #+#                 */
/*   Updated: 2024/06/17 11:27:38 by adakheel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sigparent(int sig)
{
	// char	*current_path;
	// char	*prompt;
	// dprintf(2, "parent here\n");
	// dprintf(2, "parent signal =  (%d)\n", sig);
	// if (sig != SIGCHLD)
	// g_glob = sig;
	if (sig == 2)
	{
		// g_glob = sig;
		// dprintf(2, "glob is (%d)\n", g_glob);
		// current_path = get_current_dir();
		// prompt = ft_strjoin(current_path, "$ ");
		// free(prompt);
		// free(current_path);
		// dprintf(2, "parent signal =  (%d)\n", sig);
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		// kill(g_glob, SIGINT);
	}
	// else if (sig == SIGCHLD)
	// {
	// 	printf("Quit (core dumped)\n");
	// 	// rl_on_new_line();
	// 	// rl_replace_line("hello ", 0);
	// 	// rl_redisplay();
	// 	// return ;
	// 	// exit(1);
	// 	// rl_on_new_line();
	// 	// rl_replace_line("", 0);
	// 	// rl_redisplay();
	// }
	// if (sig == 3)
	// {
	// 	// dprintf(2, "parent signal =  (%d)\n", sig);
	// 	// printf("\n");
	// 	// rl_on_new_line();
	// 	// rl_replace_line("", 0);
	// 	// rl_redisplay();
	// }
	// if (sig == 3)
	// {
	// 	printf("\n");
	// 	rl_on_new_line();
	// 	rl_replace_line("", 0);
	// 	rl_redisplay();
	// }
	// exit(0);
	g_glob = sig;
}

// void	sigquit(int sig)
// {
// 	if (sig == SIGCHLD && g_glob == 3)
// 	{
// 		dprintf(2, "quit signal =  (%d)\n", g_glob);
// 		printf("Quit (core dumped)\n");
// 		// rl_on_new_line();
// 		// rl_replace_line("hello ", 0);
// 		// rl_redisplay();
// 		// return ;
// 		// exit(1);
// 		// rl_on_new_line();
// 		// rl_replace_line("", 0);
// 		// rl_redisplay();
// 	}
// 	g_glob = 0;
// }

// void	sigchild(int sig)
// {
// 	// dprintf(2, "child signal =  (%d)\n", sig);
// 	// g_glob = 2;
// 	// if (g_glob == 0)
// 	// {
// 	// printf("\n");
// 	// rl_on_new_line();
// 	// rl_replace_line("", 0);
// 	// rl_redisplay();
// 	// }
// 	dprintf(2, "child here\n");
// 	if (sig == 2)
// 	{
// 		g_glob = sig;
// 		// printf("\n");
// 		// rl_on_new_line();
// 		// rl_replace_line("hello ", 6);
// 		// rl_redisplay();
// 		return ;
// 		//exit(1);
// 	}
// 	else if (sig == 3)
// 	{
// 		printf("Quit (core dumped)\n");
// 		// rl_on_new_line();
// 		// rl_replace_line("hello ", 0);
// 		// rl_redisplay();
// 		return ;
// 		// exit(1);
// 		// rl_on_new_line();
// 		// rl_replace_line("", 0);
// 		// rl_redisplay();
// 	}
// 	// if (sig == 2)
// 	// {
// 	// 	return ;
// 	// }
// 	// if (sig == 3)
// 	// {
// 	// 	dprintf(2, "sig num 3 child\n");
// 	// 	signal(SIGQUIT, SIG_IGN);
// 	// 	return ;
// 	// }
// }
