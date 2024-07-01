/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   free3.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: adakheel <adakheel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/07/01 11:50:39 by adakheel      #+#    #+#                 */
/*   Updated: 2024/07/01 11:53:45 by adakheel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	create_print_error2(t_all *all, char *str, char *temp)
{
	char	*temp2;

	temp2 = ft_strjoin(str, temp);
	if (!temp2 && errno == 12)
		memory_allocation_failed(all);
	temp2 = ft_strjoin_free(temp2, "\n");
	if (!temp2 && errno == 12)
		memory_allocation_failed(all);
	write(2, temp2, ft_strlen(temp2));
	free(temp2);
}

void	create_print_error(t_all *all, char *str, int num)
{
	char	*temp;

	if (num == 1)
		temp = ": Command not found";
	else if (num == 2)
		temp = ": too many arguments";
	else if (num == 3)
		temp = ": numeric argument required";
	else if (num == 4)
		temp = ": not a valid identifier";
	else if (num == 5)
		temp = ": No such file or directory";
	else if (num == 6)
		temp = "syntax error near unexpected token";
	else if (num == 7)
		temp = ": here-document delimited by end-of-file";
	else if (num == 8)
		temp = ": permission denied";
	else if (num == 12)
		temp = ": Cannot allocate memory";
	else
		temp = ": something else";
	create_print_error2(all, str, temp);
}
