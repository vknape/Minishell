
#include "minishell.h"

char	*get_current_dir(void)
{
	size_t	buf_size;
	char	*buf;
	char	*ptr;

	buf_size = 1024;
	buf = malloc(buf_size);
	if (!buf)
	{
		perror("malloc failed");
		exit(EXIT_FAILURE);
	}
	ptr = getcwd(buf, buf_size);
	if (!ptr)
	{
		 perror("getcwd failed");
		exit(EXIT_FAILURE);
	}
	printf("path is (%s)\n", buf);
	return (ptr);
}

void	change_directory(char *dir)
{
	// if (access(dir, F_OK) == -1)
	// 	perror("chdir() error");
	if (chdir(dir) == -1)
		perror("chdir() error");
	else
		get_current_dir();
}


char	*value_of_dollar_sign(t_all *all, char *str, int len)
{
	int		i;
	char	*copy_str;
	char	*copy_value;

	i = 1;
	copy_value = NULL;
	copy_str = ft_substr(str, 0, len);
	if (str[0] == '$' && ft_strlen(copy_str) == 1)
		return (copy_str);
	while (all->envp != NULL)
	{
		if (!strncmp(copy_str, all->envp->str, ft_strlen(copy_str)))
		{
			copy_value = ft_substr(all->envp->str, ft_strlen(copy_str) + 1, ft_strlen(all->envp->str) - ft_strlen(copy_str));
			break ;
		}
		all->envp = all->envp->next;
	}
	if (copy_value == NULL)
	{
		while (all->export != NULL)
		{
			if (!strncmp(copy_str, all->export->str, ft_strlen(copy_str)))
			{
				copy_value = ft_substr(all->export->str, ft_strlen(copy_str) + 1, ft_strlen(all->export->str) - ft_strlen(copy_str));
				break ;
			}
			all->export = all->export->next;
		}
	}
	return (copy_value);
}


void	join_all_indexes_of_array(char **array_str)
{
	char	*line_joined;
	char	*temp_line;
	int		index;

	index = 1;
	temp_line = NULL;
	line_joined = NULL;
	while (array_str[index] != NULL)
	{
		if (!line_joined)
			line_joined = ft_strdup(array_str[index]);
		else
		{
			temp_line = ft_strjoin(line_joined, " ");
			free(line_joined);
			line_joined = NULL;
			line_joined = ft_strjoin(temp_line, array_str[index]);
			free(temp_line);
			temp_line = NULL;
		}
		index++;
	}
	printf("line_joined is %s\n", line_joined);
}

int	is_white_space(char c)
{
	if (c == 32 || (c >= 9 && c <= 13))
		return (1);
	return (0);
}

char	*ft_strjoin_free(char *s1, char *s2)
{
	char	*p;
	size_t	lens1;
	size_t	lens2;
	size_t	tolen;

	lens1 = ft_strlen(s1);
	lens2 = ft_strlen(s2);
	tolen = lens1 + lens2 + 1;
	if (!s1)
		return ((char *) s2);
	if (!s2)
		return ((char *)s1);
	p = (char *)malloc(tolen * (sizeof(char)));
	if (!p)
	{
		free(s1);
		return (NULL);
	}
	ft_strlcpy(p, s1, lens1 + 1);
	ft_strlcpy(p + lens1, s2, lens2 + 1);
	if (s1)
		free(s1);
	return (p);
}

void	ft_echo_quotes(t_all *all, char **array_str)
{
	int		index;
	int		i;
	int		start;
	char	*str;
	char	*dvalue;
	char	*temp;

	index = 1;
	start = 0;
	str = NULL;
	while (array_str[index] != NULL)
	{
		i = 0;
		if (array_str[index][0] == '"')
		{
			while (array_str[index][i])
			{
				if (i == 0)
					i++;
				start = i;
				while (array_str[index][i] && array_str[index][i] != '$' && array_str[index][i] != '"')
					i++;
				temp = ft_substr(&array_str[index][start], 0, i - start);
				if (!str)
					str = ft_strdup(temp);
				else
					str = ft_strjoin_free(str, temp);
				free(temp);
				if (array_str[index][i] && array_str[index][i] == '$' && !is_white_space(array_str[index][i + 1]))
				{
					start = i;
					if (!array_str[index][i + 1] || array_str[index][i + 1] == '"')
					{
						dvalue = value_of_dollar_sign(all, &array_str[index][start], 1);
						start += 2;
						i += 2;
					}
					else
					{
						while (array_str[index][i] && !is_white_space(array_str[index][i]) && array_str[index][i] != '"')
							i++;
						start++;
						dvalue = value_of_dollar_sign(all, &array_str[index][start], i - start);
					}
					str = ft_strjoin_free(str, dvalue);
					free(dvalue);
				}
				else if (array_str[index][i] && array_str[index][i] == '$' && is_white_space(array_str[index][i + 1]))
				{
					temp = ft_substr(&array_str[index][i], 0, 1);
					str = ft_strjoin_free(str, temp);
					free(temp);
					i++;
				}
				if (array_str[index][i] == '"')
					i++;
			}
			free(array_str[index]);
			array_str[index] = ft_strdup(str);
			free(str);
			str = NULL;
		}
		else
		{
			i = 0;
			while (array_str[index][i])
			{
				if (array_str[index][i] == '$' && (!array_str[index][i + 1] || !is_white_space(array_str[index][i + 1])))
				{
					if (!array_str[index][i + 1])
					{
						dvalue = value_of_dollar_sign(all, &array_str[index][start], 1);
						i++;
					}
					else
					{
						i++;
						start = i;
						while (array_str[index][i] && !is_white_space(array_str[index][i]))
							i++;
						dvalue = value_of_dollar_sign(all, &array_str[index][start], i - start);
					}
					if (!str)
						str = ft_strdup(dvalue);
					else
					{
						str = ft_strjoin_free(str, " ");
						str = ft_strjoin_free(str, dvalue);
					}
					free(dvalue);
				}
				else
				{
					start = i;
					while (array_str[index][i] && array_str[index][i] != '$')
						i++;
					temp = ft_substr(&array_str[index][start], 0, i - start);
					if (!str)
						str = ft_strdup(temp);
					else
					{
						str = ft_strjoin_free(str, " ");
						str = ft_strjoin_free(str, temp);
					}
					free(temp);
				}
			}
			free(array_str[index]);
			array_str[index] = ft_strdup(str);
			free(str);
			str = NULL;
		}
		index++;
	}
	join_all_indexes_of_array(array_str);
}

// void	ft_echo_quotes(t_all *all, char **array_str)
// {
// 	int		index;
// 	int		i;
// 	int		start;
// 	char	*str;
// 	char	*dvalue;
// 	char	*temp;

// 	index = 1;
// 	start = 0;
// 	str = NULL;
// 	while (array_str[index] != NULL)
// 	{
// 		i = 0;
// 		printf("index is (%d)\n", index);
// 		// printf("(array_str[index] is (%s)\n", array_str[index]);
// 		if (array_str[index][0] == '"')
// 		{
// 			while (array_str[index][i])
// 			{
// 				if (i == 0)
// 					i++;
// 				start = i;
// 				while (array_str[index][i] && array_str[index][i] != '$' && array_str[index][i] != '"')
// 					i++;
// 				temp = ft_substr(&array_str[index][start], 0, i - start);
// 				if (!str)
// 					str = ft_strdup(temp);
// 				else
// 					str = ft_strjoin_free(str, temp);
// 				free(temp);
// 				if (array_str[index][i] && array_str[index][i] == '$' && !is_white_space(array_str[index][i + 1]) && array_str[index][i + 1] != '"')
// 				{
// 					start = i;
// 					while (array_str[index][i] && !is_white_space(array_str[index][i])) //&& array_str[index][i] != '"')
// 						i++;
// 					start++;
// 					dvalue = value_of_dollar_sign(all, &array_str[index][start], i - start);
// 					str = ft_strjoin_free(str, dvalue);
// 					free(dvalue);
// 					printf("here dvalue is (%s)\n", str);
// 				}
// 				else if (array_str[index][i] && array_str[index][i] == '$' && is_white_space(array_str[index][i + 1]) || (array_str[index][i] && array_str[index][i] == '$' && !is_white_space(array_str[index][i + 1]) && array_str[index][i + 1] == '"'))
// 				{
// 					printf("dollar sign without value\n");
// 					temp = ft_substr(&array_str[index][i], 0, 1);
// 					str = ft_strjoin_free(str, temp);
// 					free(temp);
// 					i++;
// 				}
// 				if (array_str[index][i] == '"')
// 					i++;
// 			}
// 			free(array_str[index]);
// 			array_str[index] = ft_strdup(str);
// 			free(str);
// 			str = NULL;
// 			printf("array_str[index] is (%s)\n", array_str[index]);
// 		}
// 		else
// 		{
// 			printf("in else \n");
// 			i = 0;
// 			printf("array_str[index][i] is (%c) \n", array_str[index][i]);
// 			printf("array_str[index] is (%s) \n", array_str[index]);
// 			while (array_str[index][i])
// 			{
// 				if (array_str[index][i] == '$' && !is_white_space(array_str[index][i + 1]))
// 				{
// 					i++;
// 					start = i;
// 					while (array_str[index][i] && !is_white_space(array_str[index][i]))
// 						i++;
// 					dvalue = value_of_dollar_sign(all, &array_str[index][start], i - start);
// 					if (!str)
// 						str = ft_strdup(dvalue);
// 					else
// 					{
// 						str = ft_strjoin_free(str, " ");
// 						str = ft_strjoin_free(str, dvalue);
// 					}
// 					free(dvalue);
// 					printf("here dvalue is (%s)\n", str);
// 				}
// 				else
// 				{
// 					printf("to create\n");
// 					start = i;
// 					while (array_str[index][i] && array_str[index][i] != '$')
// 						i++;
// 					temp = ft_substr(&array_str[index][start], 0, i - start);
// 					if (!str)
// 					{
// 						printf("to strdup\n");
// 						str = ft_strdup(temp);
// 					}
// 					else
// 					{
// 						str = ft_strjoin_free(str, " ");
// 						str = ft_strjoin_free(str, temp);
// 					}
// 					free(temp);
// 				}
// 			}
// 			printf("before free\n");
// 			free(array_str[index]);
// 			array_str[index] = ft_strdup(str);
// 			free(str);
// 			str = NULL;
// 			printf("array_str[index] is (%s)\n", array_str[index]);
// 		}
// 		index++;
// 	}
// 	join_all_indexes_of_array(array_str);
// }