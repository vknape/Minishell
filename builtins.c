
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

	return (ptr);
}

void	ft_pwd(void)
{
	char	*current;

	current = get_current_dir();
	printf("%s\n", current);
	free(current);
}


int	ft_strncmp2(const char *str1, const char *str2, size_t n)
{
	size_t			i;
	unsigned char	a;
	unsigned char	b;

	i = 0;
	if (n == 0)
		return (0);
	// dprintf(2, "str2 is (%s)---------------------------\n", str2);
	while (i < n && (str1[i] || str2[i]))
	{
		// dprintf(2, "letters are (%c) & (%c)\n", str1[i], str2[i]);
		a = str1[i];
		b = str2[i];
		if (!a && b == '=')
			return (0);
		if (a != b)
			return (a - b);
		i++;
	}

	return (str1[i - 1] - str2[i - 1]);
}

char	*value_of_dollar_sign(t_all *all, char *str, int len)
{
	int		i;
	char	*copy_str;
	char	*copy_value;
	t_chunk	*temp;


	i = 0;
	temp = all->envp;
	copy_value = NULL;
	copy_str = ft_substr(str, 0, len);
	while (temp != NULL)
	{
		// dprintf(2, "(%s)\n", temp->str);
		if (!ft_strncmp2(copy_str, temp->str, ft_strlen(copy_str) + 1))
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
			// dprintf(2, "(%s)\n", temp->str);
			while (temp->str[i] && temp->str[i] != '=')
				i++;
			if (!ft_strncmp2(copy_str, temp->str, ft_strlen(copy_str) + 1))
			{
				// printf("temp str (%s)\n", temp->str);
				copy_value = ft_substr(temp->str, ft_strlen(copy_str) + 1, ft_strlen(temp->str) - ft_strlen(copy_str));
				copy_value = remove_quotes_exp(copy_value);
				break ;
			}
			temp = temp->next;
		}
	}
	free(copy_str);
	// printf("copy str (%s)\n", copy_value);
	// copy_value = remove_quotes_exp(copy_value);
	copy_value = remove_whitespace_cmd(copy_value);
	dprintf(2, "copy str after remove _quotes_cmd(%s)\n", copy_value);
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
		dprintf(2, "echo str = (%s)\n", array_str[index]);
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
	free(line_joined);
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
	t_chunk	*temp;

	temp = all->envp;
	while (temp)
	{
		printf("%s\n", temp->str);
		temp = temp->next;
	}
}

void	ft_remove_var(t_chunk *chunk, char *str)
{
	t_chunk	*temp;
	t_chunk	*temp2;

	temp = chunk;
	if (!ft_strncmp(temp->str, str, ft_strlen(temp->str)))
	{
		chunk = temp->next;
		free(temp);
		return ;
	}
	while (temp->next)
	{
		if (!ft_strncmp(temp->next->str, str, ft_strlen(str)))
		{
			temp2 = temp->next;
			temp->next = temp->next->next;
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
		i++;
	}
}


int	number_of_char_until_first_slash(char *s)
{
	int	len;

	len = ft_strlen(s) - 1;
	while (s[len] && len >= 0)
	{
		if (s[len] == 47)
		{
			return (len);
		}
		len--;
	}
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
			free(new_dir);
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
		dprintf(2, "error bash: cd: too many arguments\n");
		exit(EXIT_FAILURE);
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
		dprintf(2, "error invalid dir\n");
	}
	free(current_dir);
	free(new_dir);
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

int	ft_isalnum_under(int i)
{
	if (ft_isalpha(i) || ft_isdigit(i) || i == '_')
		return (1);
	return (0);
}

void	ft_export(t_all	*all)
{
	int		i;
	int		i_char;
	int		to_env;
	t_chunk	*chuncks;
	char	*joined_for_export;

	i = 0;
	chuncks = all->export;
	while (all->line->each_cmd->cmd[i] != NULL)
		i++;
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
			to_env = 0;
			i_char = 0;
			while (all->line->each_cmd->cmd[i][i_char] && (all->line->each_cmd->cmd[i][i_char] == '=' || ft_isalnum_under(all->line->each_cmd->cmd[i][i_char])))
			{
				if (all->line->each_cmd->cmd[i][i_char] == '=')
					to_env = 1;
				i_char++;
			}
			if (all->line->each_cmd->cmd[i][i_char])
			{
				printf("bash: export: %s: not a valid identifier\n", all->line->each_cmd->cmd[i]);
				all->last_exit_status = 1;
				return ;
			}
			i_char = 0;
			if (ft_strchr("1234567890=", all->line->each_cmd->cmd[i][0]))
			{
				printf("bashs: export: %s: not a valid identifier\n", all->line->each_cmd->cmd[i]);
				all->last_exit_status = 1;
				return ;
			}
			else
			{
				if (to_env)
				{
					ft_lstadd_back_chunk(&all->envp, ft_lstnewchunk(all->line->each_cmd->cmd[i]));
				}
				while (all->line->each_cmd->cmd[i][i_char] && all->line->each_cmd->cmd[i][i_char] != '=')
					i_char++;
				if (all->line->each_cmd->cmd[i][i_char])
				{
					joined_for_export = ft_joined_for_export(all->line->each_cmd->cmd[i], i_char);
					ft_lstadd_back_chunk(&all->export, ft_lstnewchunk(joined_for_export));
					free(joined_for_export);
				}
				else
				{
					joined_for_export = ft_strjoin("declare -x ", all->line->each_cmd->cmd[i]);
					ft_lstadd_back_chunk(&all->export, ft_lstnewchunk(joined_for_export));
					free(joined_for_export);
				}
			}
			i++;
		}
		sorter_export(all);
	}
	// just to test the out put
	// printf("test\n\n\n");
	// chuncks = all->export;
	// while (chuncks)
	// {
	// 	printf("%s\n", chuncks->str);
	// 	chuncks = chuncks->next;
	// }
}

// void	error_exit(t_all *all)
// {

// }

void	ft_exit(t_all *all)
{
	int	i;
	int	local;

	i = 0;
	//check arguments
	if (all->line->each_cmd->cmd[1] == NULL)
	{
		//no arguments
		local = all->line->exit_value;
		free_all(&all);
		if (g_glob == 2)
		{
			local = 130;
			exit(local);
		}
		else
		{
			exit(local);
		}
	}
	else
	{
		// there are arguments
		if (all->line->each_cmd->cmd[2] != NULL)
		{
			// there are more than one arguments
			dprintf(2,"too many arguments\n");
			all->last_exit_status = 1;
		}
		else if (all->line->each_cmd->cmd[2] == NULL)
		{
			//just one arguments
			//check if is it digit
			while (all->line->each_cmd->cmd[1][i] && ft_isdigit(all->line->each_cmd->cmd[1][i]))
			{
				i++;
			}
			if (all->line->each_cmd->cmd[1][i] != '\0')
			{
				//there is another char
				printf(" %s: numeric argument required\n", all->line->each_cmd->cmd[1]);
				all->last_exit_status = 2;
				exit(2);
			}
			else
			{
				//just numbers
				all->last_exit_status = ft_atoi(all->line->each_cmd->cmd[1]);
				exit(ft_atoi(all->line->each_cmd->cmd[1]));
			}
		}
	}

}
