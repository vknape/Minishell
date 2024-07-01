/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtins_echo_value_dollar.c                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: adakheel <adakheel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/06/25 12:10:37 by adakheel      #+#    #+#                 */
/*   Updated: 2024/06/27 07:55:38 by adakheel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*value_of_dollar_sign2(char *copy_value, char *copy_str)
{
	if (!copy_value)
		copy_value = ft_substr(copy_str, ft_strlen(copy_str), 1);
	free(copy_str);
	if (!copy_value && errno == 12)
		return (NULL);
	return (copy_value);
}

char	*value_of_dollar_sign(t_all *all, char *str, int len)
{
	char	*copy_str;
	char	*copy_value;
	t_chunk	*temp;

	copy_value = NULL;
	copy_str = ft_substr(str, 0, len);
	if (!copy_str)
		return (NULL);
	temp = all->export;
	while (temp != NULL)
	{
		if (!ft_strncmp2(copy_str, temp->str + 11, ft_strlen(copy_str) + 1))
		{
			copy_value = ft_substr(temp->str, ft_strlen(copy_str) + 12, \
			ft_strlen(temp->str) - ft_strlen(copy_str));
			if (!copy_value && errno == 12)
			{
				free(copy_str);
				return (NULL);
			}
			break ;
		}
		temp = temp->next;
	}
	return (value_of_dollar_sign2(copy_value, copy_str));
}

void	print_line(char *line, int newline)
{
	if (!line && newline == 0)
		return ;
	if (!line)
		printf("\n");
	else if (newline == 0)
		printf("%s", line);
	else
		printf("%s\n", line);
}

void	join_all_indexes_of_array(t_all *all, char **array_str, int index, \
	int new_line)
{
	char	*line_joined;

	line_joined = NULL;
	while (array_str[index] != NULL)
	{
		if (array_str[index][0])
		{
			if (!line_joined)
				line_joined = ft_strdup(array_str[index]);
			else
			{
				line_joined = ft_strjoin_free(line_joined, " ");
				if (!line_joined && errno == 12)
					memory_allocation_failed(all);
				line_joined = ft_strjoin_free(line_joined, array_str[index]);
			}
			if (!line_joined && errno == 12)
				memory_allocation_failed(all);
		}
		index++;
	}
	print_line(line_joined, new_line);
	free(line_joined);
}

void	ft_echo_quotes(t_all *all, char **array_str)
{
	int	i;
	int	c;
	int	new_line;

	i = 1;
	new_line = 1;
	while (array_str[i] && !ft_strncmp("-n", array_str[i], 2))
	{
		c = 2;
		while (array_str[i][c] == 'n')
		{
			c++;
		}
		if (i == 1 && array_str[i][c] == '\0')
			new_line = 0;
		if (array_str[i][c] == '\0')
			i++;
		else
			break ;
	}
	join_all_indexes_of_array(all, array_str, i, new_line);
}
