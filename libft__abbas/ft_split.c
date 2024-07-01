/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_split.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: adakheel <adakheel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/17 15:07:04 by adakheel      #+#    #+#                 */
/*   Updated: 2024/06/25 10:43:31 by adakheel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	words_counter(char const *s, char c)
{
	int	count;

	count = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s)
			count++;
		while ((*s != c) && (*s))
			s++;
	}
	return (count);
}

static int	len(char const *s, char c)
{
	int	len;

	len = 0;
	while ((*s != c) && (*s != '\0'))
	{
		len++;
		s++;
	}
	return (len);
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

char	**ft_split(char const *s, char c)
{
	char	**array_of_s;
	int		index;

	index = 0;
	array_of_s = malloc(sizeof(char *) * (words_counter(s, c) + 1));
	if (array_of_s == NULL)
		return (NULL);
	while (*s)
	{
		if (*s == c)
			s++;
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
	return (array_of_s);
}
