/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   free2.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: adakheel <adakheel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/06/27 07:30:21 by adakheel      #+#    #+#                 */
/*   Updated: 2024/07/01 11:51:10 by adakheel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free2d_from_indexn(int index, char **array)
{
	while (index >= 0)
	{
		free(array[index]);
		index--;
	}
	free(array);
}

void	free_open_faild(t_all *all, char *str)
{
	char	*text;
	char	*join;

	text = strerror(errno);
	join = ft_strjoin(str, ": ");
	if (!join && errno == 12)
		memory_allocation_failed(all);
	join = ft_strjoin_free(join, text);
	if (!join && errno == 12)
		memory_allocation_failed(all);
	join = ft_strjoin_free(join, "\n");
	if (!join && errno == 12)
		memory_allocation_failed(all);
	write(2, join, ft_strlen(join));
	free(join);
	all->last_exit_status = 1;
	kill_process(all);
}

void	memory_allocation_failed(t_all *all)
{
	all->last_exit_status = 12;
	perror("");
	kill_process(all);
}

void	kill_process(t_all *all)
{
	int	local;

	local = all->last_exit_status;
	if (g_glob == 2)
	{
		all->last_exit_status = 130;
		local = all->last_exit_status;
	}
	free_all(&all);
	exit(local);
}

