/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vknape <vknape@student.codam.nl>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 09:39:20 by vknape            #+#    #+#             */
/*   Updated: 2024/04/11 08:50:31 by vknape           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	words(const char *s, char c);
static int	letters(const char *s, char c);
static void	rm(int words, char **ptr);

char	**ft_split(char const *s, char c)
{
	int		i;
	char	**ptr;

	ptr = malloc((words(s, c) + 1) * sizeof(char *));
	if (ptr == NULL)
		return (NULL);
	i = 0;
	while (*s)
	{
		if (*s == c)
			s++;
		else
		{
			ptr[i] = malloc((letters(s, c) + 1) * sizeof(char));
			if (ptr[i] == NULL)
			{
				rm(i, ptr);
				return (NULL);
			}
			ft_strlcpy(ptr[i++], s, letters(s, c) + 1);
			s += letters(s, c);
		}
	}
	ptr[i] = NULL;
	return (ptr);
}

static int	words(const char *s, char c)
{
	int	i;
	int	words;
	int	start;

	i = 0;
	words = 0;
	start = 0;
	while (s[i])
	{
		if (s[i] == c)
			start = 0;
		if (s[i] != c && start == 0)
		{
			start = 1;
			words++;
		}
		i++;
	}
	return (words);
}

static int	letters(const char *s, char c)
{
	int	letter;

	letter = 0;
	while (*s)
	{
		if (*s == c)
			return (letter);
		letter++;
		s++;
	}
	return (letter);
}

static void	rm(int words, char **ptr)
{
	int	i;

	i = 0;
	while (i < words)
	{
		free(ptr[i]);
		i++;
	}
	free(ptr);
}
