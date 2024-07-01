/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtins_env_pwd_exit.c                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: adakheel <adakheel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/06/25 11:48:37 by adakheel      #+#    #+#                 */
/*   Updated: 2024/06/27 07:55:42 by adakheel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_current_dir(t_all *all)
{
	size_t	buf_size;
	char	*buf;
	char	*ptr;

	buf_size = 1024;
	buf = malloc(buf_size);
	if (!buf && errno == 12)
		memory_allocation_failed(all);
	ptr = getcwd(buf, buf_size);
	if (!ptr && errno == 12)
		memory_allocation_failed(all);
	return (ptr);
}

void	ft_pwd(t_all *all)
{
	char	*current;

	current = get_current_dir(all);
	printf("%s\n", current);
	free(current);
}

void	ft_env(t_all *all)
{
	t_chunk	*temp;

	temp = all->envp;
	while (temp)
	{
		printf("%s\n", temp->str);
		temp = temp->next;
	}
}

void	ft_exit2(t_all *all, t_cmd *cmd, char *str, int i)
{
	if (str[0] && (str[0] == '+' || str[0] == '-'))
		i++;
	while (str[i] && ft_isdigit(str[i]))
		i++;
	if (str[i] == '\0' && cmd->cmd[2])
	{
		create_print_error(all, cmd->cmd[0], 2);
		all->last_exit_status = 1;
		return ;
	}
	else if (str[i] != '\0')
	{
		create_print_error(all, cmd->cmd[0], 3);
		all->last_exit_status = 2;
	}
	else if (!cmd->cmd[2] && str[i] == '\0')
	{
		all->last_exit_status = ft_atoi(str) % 256;
		while (all->last_exit_status < 0)
			all->last_exit_status += 256;
	}
	i = all->last_exit_status;
	free_all(&all);
	exit(i);
}

void	ft_exit(t_all *all, t_cmd *cmd)
{
	int		i;
	int		local;
	char	*str;

	i = 0;
	str = cmd->cmd[1];
	if (str == NULL)
	{
		local = all->line->exit_value;
		if (g_glob == 2)
		{
			all->line->exit_value = 130;
			local = all->line->exit_value;
		}
		free_all(&all);
		exit(local);
	}
	else
		ft_exit2(all, cmd, str, i);
}
