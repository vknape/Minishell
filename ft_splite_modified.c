
#include "minishell.h"

static int	words_counter(char const *s, char c, int max_position)
{
	int	count;
	int	position;

	count = 0;
	position = 0;
	while (*s && position < max_position)
	{
		while (*s == c)
			s++;
		if (*s && position < max_position)
			count++;
		while ((*s != c) && (*s) && position < max_position)
		{
			s++;
			position++;
		}
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

char	**ft_split_until(char const *s, char c, int max_position)
{
	printf("ft_split_until\n\n");
	char	**array_of_s;
	int		index;
	int		position;

	index = 0;
	position = 0;
	array_of_s = malloc(sizeof(char *) * (words_counter(s, c, max_position) + 1));
	if (array_of_s == NULL)
		return (NULL);
	while (*s && position < max_position)
	{
		if (*s == c)
			s++;
		else
		{
			array_of_s[index] = malloc(sizeof(char) * (len(s, c) + 1));
			if (!array_of_s[index])
			{
				ft_free_s(index, array_of_s);
				return (NULL);
			}
			ft_strlcpy(array_of_s[index++], s, (len(s, c) + 1));
			position += len(s, c) + 1;
			s = s + len(s, c);
		}
	}
	array_of_s[index] = NULL;
	return (array_of_s);
}
