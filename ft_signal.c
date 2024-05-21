/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_signal.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: adakheel <adakheel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/17 12:10:58 by adakheel      #+#    #+#                 */
/*   Updated: 2024/05/20 16:00:53 by adakheel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sighandler(int sig)
{
	// dprintf(2, "value of signal is (%d)\n", sig);
	if (sig == 2)
		return ;
	if (sig == 3)
		return ;
}
