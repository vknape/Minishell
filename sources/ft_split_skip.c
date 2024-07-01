/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_split_skip.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: vknape <vknape@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/20 09:39:20 by vknape        #+#    #+#                 */
/*   Updated: 2024/06/27 07:56:49 by adakheel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	words_counter_quotes(char const *s, char c, int *i)
{
	int		count;
	char	q;

	count = 0;
	q = s[*i];
	(*i)++;
	while (s[*i] && s[*i] != q)
		(*i)++;
	if (s[*i])
		(*i)++;
	if (!s[*i] || s[*i] == c)
		count++;
	return (count);
}

static int	words_counter(char const *s, char c)
{
	int		count;
	int		i;

	count = 0;
	i = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i] == 34 || s[i] == 39)
			count = count + words_counter_quotes(s, c, &i);
		else if (s[i])
		{
			while (s[i] && s[i] != c && s[i] != 34 && s[i] != 39)
				i++;
			if (!s[i] || s[i] == c)
				count++;
		}
	}
	return (count);
}

static int	len(char const *s, char c)
{
	int		i;
	char	q;

	i = 0;

	while (s[i] && s[i] != c)
	{
		q = -1;
		if (s[i] && (s[i] == 34 || s[i] == 39))
		{
			q = s[i];
			i++;
			while (s[i] && s[i] != q)
				i++;
		}
		i++;
	}
	return (i);
}

void	allocate_array_of_index_failed(t_all *all, char **array_of_s, int index)
{
	free2d_from_indexn(index, &array_of_s[index]);
	memory_allocation_failed(all);
}

char	**ft_split_quotes(t_all *all, char const *s, char c)
{
	char	**array_of_s;
	int		i;
	int		index;

	index = 0;
	array_of_s = malloc(sizeof(char *) * (words_counter(s, c) + 1));
	i = 0;
	if (array_of_s == NULL && errno == 12)
		memory_allocation_failed(all);
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i] && s[i] != c)
		{
			array_of_s[index] = malloc(sizeof(char) * (len(&s[i], c) + 1));
			if (!array_of_s[index])
				allocate_array_of_index_failed(all, array_of_s, index);
			ft_strlcpy(array_of_s[index++], &s[i], (len(&s[i], c) + 1));
			i = i + len(&s[i], c);
		}
	}
	array_of_s[index] = NULL;
	return (array_of_s);
}
