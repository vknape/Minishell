/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_signal.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: adakheel <adakheel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/17 12:10:58 by adakheel      #+#    #+#                 */
/*   Updated: 2024/05/23 11:37:04 by adakheel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sigparent(int sig)
{
	// char	*current_path;
	// char	*prompt;
	
	// dprintf(2, "parent signal =  (%d)\n", sig);
	if (sig == 2)
	{
		g_glob = sig;
		// dprintf(2, "glob is (%d)\n", g_glob);
		// current_path = get_current_dir();
		// prompt = ft_strjoin(current_path, "$ ");
		// free(prompt);
		// free(current_path);
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		return ;
	}
	if (sig == 3)
		return ;
	// exit(0);
}

void	sigchild(int sig)
{
	// dprintf(2, "child signal =  (%d)\n", sig);
	// g_glob = 2;
	// if (g_glob == 0)
	// {
	// printf("\n");
	// rl_on_new_line();
	// rl_replace_line("", 0);
	// rl_redisplay();
	// }
	if (sig == 2)
	{
		g_glob = sig;
		exit(1);
	}
	// if (sig == 2)
	// {
	// 	return ;
	// }
	if (sig == 3)
		return ;
}
