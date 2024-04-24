/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vknape <vknape@student.codam.nl>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 11:45:42 by vknape            #+#    #+#             */
/*   Updated: 2024/04/24 12:03:43 by vknape           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	make_envp_and_set(t_all *all, char *envp[])
{
	int	i;

	i= 0;
	while (envp[i])
	{
		ft_lstadd_back_chunk(all->envp, ft_lstnewchunk(envp[i]));
		ft_lstadd_back_chunk(all->set, ft_lstnewchunk(envp[i]));
		i++;
	}

}

void	make_export(t_all *all, char *envp[])
{
	int		i;
	// char	*c;


	i = 0;
	while (envp[i])
	{
		ft_lstadd_back_chunk(all->export,
			ft_lstnewchunk(ft_strjoin("declare -x ", envp[i])));
		i++;
	}
	
}
