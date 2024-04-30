/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_split_skip.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: vknape <vknape@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/20 09:39:20 by vknape        #+#    #+#                 */
/*   Updated: 2024/04/30 12:56:19 by adakheel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	words_counter(char const *s, char c)
{
	int		count;
	char	q;

	count = 0;
	while (*s)
	{
		// printf("s = (%c)\n", *s);
		while (*s && *s == c)
			s++;
		if (*s == 34 || *s == 39)
		{
			q = *s;
			s++;
			while (*s && *s != q)
				s++;
		}
		while (*s == c)
			s++;
		if (*s)
			count++;
		while (*s && (*s != c && *s != 34 && *s != 39))
			s++;
		if (*s == 34 || *s == 39)
			s++;
	}
	// printf("WC = (%d)\n", count);
	return (count);
}




static int	len(char const *s, char c)
{
	int		len;
	char	q;

	len = 0;
	if (*s == 34 || *s == 39)
	{
		q = *s;
		s++;
		while (*s && *s != q)
		{
			len++;
			s++;
		}
		len = len + 2;
		// printf("len = (%d)\n", len);
		return (len);
	}
	else
	{
		while ((*s != '\0') && (*s != c))
		{
			len++;
			s++;
		}
		// printf("len = (%d)\n", len);
		return (len);
	}
}

static void	ft_free_s(int index, char **array)
{
	while (index >= 0)
	{
		free(array[index]);
		index--;
	}
	free(array);
}

char	**ft_split_quotes(char const *s, char c)
{
	char	**array_of_s;
	int		index;
	char	q;

	index = 0;
	array_of_s = malloc(sizeof(char *) * (words_counter(s, c) + 1));
	if (array_of_s == NULL)
		return (NULL);
	while (*s)
	{
		while (*s && *s == c)
			s++;
		if (*s == 34 || *s == 39)
		{
			q = *s;
			array_of_s[index] = malloc(sizeof(char) * (len(s, q) + 1));
			if (!array_of_s[index])
			{
				ft_free_s(index, &array_of_s[index]);
				return (NULL);
			}

			ft_strlcpy(array_of_s[index++], s, (len(s, q) + 1));
			s = s + len(s, q);
		}
		else
		{
			array_of_s[index] = malloc(sizeof(char) * (len(s, c) + 1));
			if (!array_of_s[index])
			{
				ft_free_s(index, &array_of_s[index]);
				return (NULL);
			}
			ft_strlcpy(array_of_s[index++], s, (len(s, c) + 1));
			s = s + len(s, c);
		}
	}
	array_of_s[index] = NULL;
	// int i = 0;
	// while (array_of_s[i])
	// {
	// 	printf("array_of_s is (%s)\n", array_of_s[i]);
	// 	i++;
	// }
	return (array_of_s);
}

// char	**ft_split_quotes(char const *s, char c)
// {
// 	char	**array_of_s;
// 	int		index;
// 	char	q;

// 	index = 0;
// 	array_of_s = malloc(sizeof(char *) * (words_counter(s, c) + 1));
// 	if (array_of_s == NULL)
// 		return (NULL);
// 	while (*s)
// 	{
// 		if (*s == c)
// 			s++;
// 		else if (*s == 34 || *s == 39)
// 		{
// 			q = *s;
// 			array_of_s[index] = malloc(sizeof(char) * (len(s, q) + 1));
// 			if (!array_of_s[index])
// 			{
// 				ft_free_s(index, &array_of_s[index]);
// 				return (NULL);
// 			}

// 			ft_strlcpy(array_of_s[index++], s, (len(s, q) + 1));
// 			s = s + len(s, q) + 3;
// 		}
// 		else
// 		{
// 			array_of_s[index] = malloc(sizeof(char) * (len(s, c) + 1));
// 			if (!array_of_s[index])
// 			{
// 				ft_free_s(index, &array_of_s[index]);
// 				return (NULL);
// 			}
// 			ft_strlcpy(array_of_s[index++], s, (len(s, c) + 1));
// 			s = s + len(s, c);
// 		}
// 		printf("remainder here is (%s)\n", s);
// 	}
// 	array_of_s[index] = NULL;
// 	return (array_of_s);
// }