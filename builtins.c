
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
	// printf("%s\n", buf);
	// printf("ptr  %s\n", ptr);
	return (ptr);
}

void	ft_pwd(void)
{
	char	*current;

	current = get_current_dir();
	printf("%s\n", current);
	free(current);
}


char	*value_of_dollar_sign(t_all *all, char *str, int len)
{
	int		i;
	char	*copy_str;
	char	*copy_value;
	t_chunk	*temp;


	i = 1;
	temp = all->envp;
	copy_value = NULL;
	// printf("str here is (%s)\n", str);
	copy_str = ft_substr(str, 0, len);
	if (str[0] == '$' && ft_strlen(copy_str) == 1)
		return (copy_str);
	while (temp != NULL)
	{
		if (!strncmp(copy_str, temp->str, ft_strlen(copy_str)))
		{
			copy_value = ft_substr(temp->str, ft_strlen(copy_str) + 1, ft_strlen(temp->str) - ft_strlen(copy_str));
			// printf("do we het here (%s)\n", copy_value);
			break ;
		}
		temp = temp->next;
	}
	if (copy_value == NULL)
	{
		temp = all->export;
		while (temp != NULL)
		{
			if (!strncmp(copy_str, temp->str, ft_strlen(copy_str)))
			{
				copy_value = ft_substr(temp->str, ft_strlen(copy_str) + 1, ft_strlen(temp->str) - ft_strlen(copy_str));
				break ;
			}
			temp = temp->next;
		}
	}
	// printf("copy str (%s)\n", copy_value);
	return (copy_value);
}


void	join_all_indexes_of_array(char **array_str, int index, int new_line)
{
	char	*line_joined;
	char	*temp_line;
	//int		index;

	//index = 1;
	// dprintf(2, "index = (%s)\n", array_str[index]);
	// dprintf(2, "hello\n");
	temp_line = NULL;
	line_joined = NULL;
	while (array_str[index] != NULL)
	{
		if (!line_joined)
			line_joined = ft_strdup(array_str[index]);
		else
		{
			line_joined = ft_strjoin_free(line_joined, " ");
			line_joined = ft_strjoin_free(line_joined, array_str[index]);
		}
		// dprintf(2, "index = (%s)\n", line_joined);
		index++;
	}
	if (!line_joined && new_line == 0)
		return ;
	if (!line_joined)
		printf("\n");
	else if (new_line == 0)
		printf("%s", line_joined);
	else
		printf("%s\n", line_joined);
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


	// int		index;
	// int		i;
	// int		start;
	// char	*str;
	// char	*dvalue;
	// char	*temp;

	// index = 1;
	// start = 0;
	// str = NULL;
	// while (array_str[index] != NULL)
	// {
	// 	i = 0;
	// 	if (array_str[index][0] == '"')
	// 	{
	// 		while (array_str[index][i])
	// 		{
	// 			if (i == 0)
	// 				i++;
	// 			start = i;
	// 			while (array_str[index][i] && array_str[index][i] != '$' && array_str[index][i] != '"')
	// 				i++;
	// 			temp = ft_substr(&array_str[index][start], 0, i - start);
	// 			if (!str)
	// 				str = ft_strdup(temp);
	// 			else
	// 				str = ft_strjoin_free(str, temp);
	// 			free(temp);
	// 			ifi--; (array_str[index][i] && array_str[index][i] == '$' && !is_white_space(array_str[index][i + 1]))
	// 			{
	// 				start = i;
	// 				if (!array_str[index][i + 1] || array_str[index][i + 1] == '"')
	// 				{
	// 					dvalue = value_of_dollar_sign(all, &array_str[index][start], 1);
	// 					start += 2;
	// 					i += 2;
	// 				}
	// 				else
	// 				{
	// 					while (array_str[index][i] && !is_white_space(array_str[index][i]) && array_str[index][i] != '"')
	// 						i++;
	// 					start++;
	// 					dvalue = value_of_dollar_sign(all, &array_str[index][start], i - start);
	// 				}
	// 				str = ft_strjoin_free(str, dvalue);
	// 				free(dvalue);
	// 			}
	// 			else if (array_str[index][i] && array_str[index][i] == '$' && is_white_space(array_str[index][i + 1]))
	// 			{
	// 				temp = ft_substr(&array_str[index][i], 0, 1);
	// 				str = ft_strjoin_free(str, temp);
	// 				free(temp);
	// 				i++;
	// 			}
	// 			if (array_str[index][i] == '"')
	// 				i++;
	// 		}
	// 		free(array_str[index]);
	// 		array_str[index] = ft_strdup(str);
	// 		free(str);
	// 		str = NULL;
	// 	}
	// 	else
	// 	{
	// 		i = 0;
	// 		while (array_str[index][i])
	// 		{
	// 			if (array_str[index][i] == '$' && (!array_str[index][i + 1] || !is_white_space(array_str[index][i + 1])))
	// 			{
	// 				if (!array_str[index][i + 1])
	// 				{
	// 					dvalue = value_of_dollar_sign(all, &array_str[index][start], 1);
	// 				i--;	i++;
	// 				}
	// 				else
	// 				{
	// 					i++;
	// 					start = i;
	// 					while (array_str[index][i] && !is_white_space(array_str[index][i]))
	// 						i++;
	// 					dvalue = value_of_dollar_sign(all, &array_str[index][start], i - start);
	// 				}
	// 				if (!str)
	// 					str = ft_strdup(dvalue);
	// 				else
	// 				{
	// 					str = ft_strjoin_free(str, " ");
	// 					str = ft_strjoin_free(str, dvalue);
	// 				}
	// 				free(dvalue);
	// 			}
	// 			elsei--;
	// 			{
	// 				start = i;
	// 				while (array_str[index][i] && array_str[index][i] != '$')
	// 					i++;
	// 				temp = ft_substr(&array_str[index][start], 0, i - start);
	// 				if (!str)
	// 					str = ft_strdup(temp);
	// 				else
	// 				{
	// 					str = ft_strjoin_free(str, " ");
	// 					str = ft_strjoin_free(str, temp);
	// 				}
	// 				free(temp);
	// 			}
	// 		}
	// 		free(array_str[index]);
	// 		array_str[index] = ft_strdup(str);
	// 		free(str);
	// 		str = NULL;
	// 	}
	// 	index++;
	// }
	void	ft_echo_quotes(t_all *all, char **array_str)
{

	int	i;
	int	c;
	int	new_line;

	i = 1;
	new_line = 1;
	// dprintf(2, "hello\n");
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


	join_all_indexes_of_array(array_str, i, new_line);
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

void	ft_env(t_all *all)
{
	t_chunk *temp;

	temp = all->envp;
	while (temp)
	{
		printf("%s\n", temp->str);
		temp = temp->next;
	}
	// while (all->export)
	// {
	// 	printf("%s\n", all->export->str);
	// 	all->export = all->export->next;
	// }
	// while (all->set)
	// {
	// 	printf("%s\n", all->set->str);
	// 	all->set = all->set->next;
	// }
}

// void	ft_pwd(void)
// {
// 	char	*current_dir;

// 	current_dir = get_current_dir();
// 	printf("%s\n", current_dir);
// }

void	ft_remove_var(t_chunk *chunk, char *str)
{
	t_chunk	*temp;
	t_chunk	*temp2;

	temp = chunk;
	// printf("str is (%s)\n", str);
	if (!ft_strncmp(temp->str, str, ft_strlen(temp->str)))
	{
		// printf("first chunk = (%s)\n", temp->str);
		chunk = temp->next;
		free(temp);
		return ;
	}
	while (temp->next)
	{
		// printf("next chunk = (%s)\n", temp->next->str);
		if (!ft_strncmp(temp->next->str, str, ft_strlen(str)))
		{
			// printf("do free-------------\n");
			temp2 = temp->next;
			temp->next = temp->next->next;
			// printf("temp2 is (%s)\n", temp2->str);
			// if (temp2->str)
			free(temp2->str);
			free(temp2);
			temp2 = NULL;

			return ;
		}
		temp = temp->next;
	}
}

void	ft_unset(t_all *all, char **str)
{
	char	*c;
	int		i;

	i = 1;
	while (str[i])
	{
		c = ft_strjoin("declare -x ", str[i]);
		ft_remove_var(all->envp, str[i]);
		ft_remove_var(all->export, c);
		free(c);
		// ft_remove_var(all->set, str[i]);
		i++;
	}
}


int	number_of_char_until_first_slash(char *s)
{
	int	len;

	len = ft_strlen(s) - 1;
	// printf("len is %d\n", len);
	while (s[len] && len >= 0)
	{
		if (s[len] == 47)
		{
			// printf("len is %d\n", len);
			return (len);
		}
		len--;
	}
	// printf("len is %d\n", len);
	return (0);
}

char *create_new_path(t_all *all, char **array)
{
	int		i;
	char	*dir;
	char	*new_dir;

	i = 0;
	dir = get_current_dir();
	// printf("array[i] (%s)\n", array[i]);
	while (array && array[i])
	{
		// printf("array[i] (%s)\n", array[i]);
		if (!ft_strncmp(array[i], ".", 2))
		{
			i++;
			continue ;
		}
		else if (!ft_strncmp(array[i], "..", 3))
		{
			new_dir = ft_substr(dir, 0, number_of_char_until_first_slash(dir));
			if (new_dir[0] == '\0')
			{
				free(new_dir);
				new_dir = ft_substr(dir, 0, 1);
			}
			free(dir);
			dir = new_dir;
			// printf("new_dir = (%s)\n", new_dir);
		}
		else if (!ft_strncmp(array[i], "~", 2) && i == 0)
		{
			dir = value_of_dollar_sign(all, "HOME", 4);
			// printf("value $ HOME (%s)\n", new_dir);
			// dir = ft_strjoin_free(dir, "/");
			// dir = ft_strjoin_free(dir, new_dir);
			// printf("new dir (%s)\n", dir);
		}
		else if (!ft_strncmp(array[i], "-", 2) && i == 0)
		{
			new_dir = value_of_dollar_sign(all, "OLDPWD", 7);
			dir = ft_strjoin_free(dir, "/");
			dir = ft_strjoin_free(dir, new_dir);
		}
		else
		{
			// printf("new dir (%s)\n", dir);
			dir = ft_strjoin_free(dir, "/");
			dir = ft_strjoin_free(dir, array[i]);
		}
		i++;
	}
	// printf("new dir (%s)\n", dir);
	return (dir);
}

void	ft_cd(t_all *all)
{
	char	*current_dir;
	char	*new_dir;
	char	**array;
	int		total_indexes;

	current_dir = get_current_dir();
	// dprintf(2, "(%s)\n", current_dir);
	total_indexes = 0;
	while (all->line->each_cmd->cmd && all->line->each_cmd->cmd[total_indexes])
		total_indexes++;
	// printf("here (%s)\n", current_dir);
	if (total_indexes > 2)
	{
		printf("error bash: cd: too many arguments\n");
		return ;
	}
	if (!ft_strncmp(all->line->each_cmd->cmd[1], "/", 2))
	{
		new_dir = ft_substr(current_dir, 0, 1);
	}
	else
	{
		array = ft_split(all->line->each_cmd->cmd[1], '/');
		if (total_indexes == 2)
		{
			new_dir = create_new_path(all, array);
		}
	}
	// printf("new dir is (%s)\n", new_dir);
	if (chdir(new_dir) == -1)
	{
		printf("error invalid dir\n");
	}
	// current_dir = get_current_dir();
	// dprintf(2, "here %s\n", current_dir);
}

char	*ft_joined_for_export(char *str, int start)
{
	char	*temp1;
	char	*temp2;

	temp1 = ft_substr(str, 0, start + 1);
	temp2 = ft_strjoin("declare -x ", temp1);
	free(temp1);
	temp1 = ft_strjoin(temp2, "\"");
	free(temp2);
	temp2 = ft_substr(str, start + 1, ft_strlen(str) - (start + 1));
	temp1 = ft_strjoin_free(temp1, temp2);
	free(temp2);
	temp2 = ft_strjoin_free(temp1, "\"");
	// printf("str for export is (%s)\n", temp2);
	return (temp2);
}

void	ft_export(t_all	*all)
{
	int		i;
	int		i_char;
	t_chunk	*chuncks;
	char	*joined_for_export;

	i = 0;
	chuncks = all->export;
	while (all->line->each_cmd->cmd[i] != NULL)
		i++;
	// if i == 1 there are no arguments so just print all export list.
	if (i == 1)
	{
		while (chuncks)
		{
			printf("%s\n", chuncks->str);
			chuncks = chuncks->next;
		}
	}
	else
	{
		// there are some arguments
		i = 1;
		while (all->line->each_cmd->cmd[i] != NULL)
		{
			i_char = 0;
			while (all->line->each_cmd->cmd[1][i_char] && !ft_strchr("~!@#$&*(){}\\\%_-+", all->line->each_cmd->cmd[1][i_char]))
			{
				i_char++;
			}
			if (all->line->each_cmd->cmd[1][i_char])
				printf("bash: export: %s: not a valid identifier\n", all->line->each_cmd->cmd[i]);
			i_char = 0;
			if (ft_strchr("1234567890=", all->line->each_cmd->cmd[1][0]))
			{
				printf("bashs: export: %s: not a valid identifier\n", all->line->each_cmd->cmd[i]);
			}
			else
			{
				while (all->line->each_cmd->cmd[i][i_char] && all->line->each_cmd->cmd[i][i_char] != '=')
					i_char++;
				if (all->line->each_cmd->cmd[i][i_char])
				{
					ft_lstadd_back_chunk(&all->export, ft_lstnewchunk(ft_joined_for_export(all->line->each_cmd->cmd[i], i_char)));
				}
				else
				{
					ft_lstadd_back_chunk(&all->export, ft_lstnewchunk(ft_strjoin("declare -x ", all->line->each_cmd->cmd[i])));
				}
			}
			i++;
		}
	}
	sorter_export(all);
	// just to test the out put
	// printf("test\n\n\n");
	chuncks = all->export;
	// while (chuncks)
	// {
	// 	printf("%s\n", chuncks->str);
	// 	chuncks = chuncks->next;
	// }
}

void	ft_exit(int status)
{
	exit(status);
}
