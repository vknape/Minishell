
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
	// while (temp != NULL)
	// {
	// 	// dprintf(2, "(%s)\n", temp->str);
	// 	if (!ft_strncmp2(copy_str, temp->str, ft_strlen(copy_str) + 1))
	// 	{
	// 		copy_value = ft_substr(temp->str, ft_strlen(copy_str) + 1, ft_strlen(temp->str) - ft_strlen(copy_str));
	// 		dprintf(2,"do we het here (%s)\n", copy_value);
	// 		break ;
	// 	}
	// 	temp = temp->next;
	// }
	if (copy_value == NULL)
	{
		temp = all->export;
		while (temp != NULL)
		{
			// dprintf(2, "(%s)\n", temp->str);
			// while (temp->str[i] && temp->str[i] != '=')
			// 	i++;
			if (!ft_strncmp2(copy_str, temp->str + 11, ft_strlen(copy_str) + 1))
			{
				// dprintf(2, "temp str (%s)\n", temp->str);
				copy_value = ft_substr(temp->str, ft_strlen(copy_str) + 1 + 11, ft_strlen(temp->str) - ft_strlen(copy_str));
				// copy_value = remove_quotes_exp(copy_value);
				break ;
			}
			temp = temp->next;
		}
	}
	if (!copy_value)
		copy_value = ft_substr(copy_str, ft_strlen(copy_str), 1);
	free(copy_str);
	// printf("copy str (%s)\n", copy_value);
	// copy_value = remove_quotes_exp(copy_value);
	// copy_value = remove_whitespace_cmd(copy_value);
	// dprintf(2, "copy str after remove _quotes_cmd(%s)\n", copy_value);
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
		// dprintf(2, "echo str = (%s)\n", array_str[index]);
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
	if (!ft_strncmp2(str, temp->str, ft_strlen(str) + 1))
	{
		chunk = temp->next;
		free(temp);
		return ;
	}
	while (temp->next)
	{
		if (!ft_strncmp2(str, temp->next->str, ft_strlen(str) + 1))
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

char	**update_env(t_all *all)
{
	t_chunk	*temp;
	int		count_nodes;
	char	**env_updated;
	int		index;

	index = 0;
	temp = all->envp;
	count_nodes = ft_lstsizechunk(temp);
	env_updated = malloc(sizeof(char *) * (count_nodes + 1));
	while (temp)
	{
		// dprintf(2, "str = (%s)\n", temp->str);
		env_updated[index++] = ft_strdup(temp->str);
		temp = temp->next;
	}
	env_updated[index] = NULL;
	// index = 0;
	// while (env_updated[index])
	// {
	// 	dprintf(2, "%s\n", env_updated[index]);
	// 	index++;
	// }
	return (env_updated);
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
	if (all->envcur)
		free2d(all->envcur);
	all->envcur = update_env(all);
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

void	update_pwd_oldpwd(t_all *all, char *oldpwd)
{
	char	*pwd;
	char	*temp;

	temp = ft_strjoin("OLDPWD=", oldpwd);
	free(oldpwd);
	oldpwd = ft_strdup(temp);
	update_envp(all, temp, 2);
	update_export(all, oldpwd, 2);
	free(oldpwd);
	free(temp);
	pwd = get_current_dir();
	temp = ft_strjoin("PWD=", pwd);
	free(pwd);
	pwd = ft_strdup(temp);
	update_envp(all, temp, 2);
	update_export(all, pwd, 2);
	free(pwd);
	free(temp);
	if (all->envcur)
		free2d(all->envcur);
	all->envcur = update_env(all);
	sorter_export(all);
}

// void	change_pwd_oldpwd(t_all *all, char *new_pwd)
// {
// 	char	*cur_dir;
// 	t_chunk	*chunk;
// 	char	*temp;

// 	cur_dir = get_current_dir();
// 	temp = ft_strjoin("PWD=", new_pwd);
// 	free(new_pwd);
// 	chunk = all->envp;
// 	while (chunk)
// 	{
// 		if (!ft_strncmp2("PWD", chunk->str, ft_strlen(chunk->str)))
// 		{
// 			free(chunk->str);
// 			chunk->str = ft_strdup(temp);
// 			break ;
// 		}
// 		chunk = chunk->next;
// 	}
// 	new_pwd = ft_joined_for_export(temp, 4);
// 	chunk = all->export;
// 	while (chunk)
// 	{
// 		if (!ft_strncmp2("PWD", chunk->str + 11, ft_strlen(chunk->str)))
// 		{
// 			free(chunk->str);
// 			chunk->str = ft_strdup(new_pwd);
// 			break ;
// 		}
// 		chunk = chunk->next;
// 	}
// 	free(new_pwd);
// 	temp = ft_strjoin("OLDPWD=", cur_dir);
// 	chunk = all->envp;
// 	while (chunk)
// 	{
// 		if (!ft_strncmp2("OLDPWD", chunk->str, ft_strlen(chunk->str)))
// 		{void	update_envp(t_all *all, char *str, int varvalue)
// 			free(chunk->str);
// 			chunk->str = ft_strdup(temp);
// 			break ;
// 		}
// 		chunk = chunk->next;
// 	}
// 	new_pwd = ft_joined_for_export(temp, 7);
// 	chunk = all->export;
// 	while (chunk)
// 	{
// 		if (!ft_strncmp2("OLDPWD", chunk->str + 11, ft_strlen(chunk->str)))
// 		{
// 			free(chunk->str);
// 			chunk->str = new_pwd;
// 			break ;
// 		}
// 		chunk = chunk->next;
// 	}
// 	free(new_pwd);
// }

char *create_new_path(t_all *all, char **array)
{
	char	*dir;
	char	*new_dir;

	if (!array[1] || array[1][0] == '~')
	{
		new_dir = value_of_dollar_sign(all, "HOME", 4);
		dir = remove_quotes_cmd(new_dir);
		if (array[1] && array[1][1])
		{
			new_dir = ft_substr(array[1], 1, ft_strlen(array[1]));
			dir = ft_strjoin_free(dir, new_dir);
			free(new_dir);
		}
	}
	else if (array[1][0] == '-')
	{
		new_dir = value_of_dollar_sign(all, "OLDPWD", 7);
		dir = remove_quotes_cmd(new_dir);
		// dprintf(2, "oldpwd  = (%s)\n", dir);
		// dir = ft_strjoin_free(dir, "/");
		// dir = ft_strjoin_free(dir, new_dir);
		// free(new_dir);
	}
	return (dir);
}
	// if (!array)
	// {
	// 	dir = value_of_dollar_sign(all, "HOME", 4);
	// 	new_dir = remove_quotes_cmd(dir);
	// 	return (new_dir);
	// }
	// dir = get_current_dir();
	// while (array && array[i])
	// {
	// 	if (!ft_strncmp(array[i], ".", 2))
	// 	{
	// 		i++;
	// 		continue ;
	// 	}
	// 	else if (!ft_strncmp(array[i], "..", 3))
	// 	{
	// 		new_dir = ft_substr(dir, 0, number_of_char_until_first_slash(dir));
	// 		if (new_dir[0] == '\0')
	// 		{
	// 			free(new_dir);
	// 			new_dir = ft_substr(dir, 0, 1);
	// 		}
	// 		free(dir);
	// 		dir = new_dir;
	// 		// printf("new_dir = (%s)\n", new_dir);
	// 	}
	// 	else if (!ft_strncmp(array[i], "~", 2) && i == 0)
	// 	{
	// 		new_dir = value_of_dollar_sign(all, "HOME", 4);
	// 		dir = remove_quotes_cmd(new_dir);
	// 	}
	// 	else if (!ft_strncmp(array[i], "-", 2) && i == 0)
	// 	{
	// 		new_dir = value_of_dollar_sign(all, "OLDPWD", 7);
	// 		dir = ft_strjoin_free(dir, "/");
	// 		dir = ft_strjoin_free(dir, new_dir);
	// 		free(new_dir);
	// 	}
	// 	else
	// 	{
	// 		// printf("new dir (%s)\n", dir);
	// 		dir = ft_strjoin_free(dir, "/");
	// 		dir = ft_strjoin_free(dir, array[i]);
	// 	}
	// 	i++;
	// }
	// printf("new dir (%s)\n", dir);
	// return (dir);
// }

void	ft_cd(t_all *all)
{
	char	*new_dir;
	char	**array;
	char	*pwd;

	array = all->line->each_cmd->cmd;
	if (array[1] && array[2])
	{
		dprintf(2, "error bash: cd: too many arguments\n");
		all->last_exit_status = 1;
		kill_process(all);
	}
	if (!array[1])
		new_dir = create_new_path(all, array);
	else if (array[1][0] == '~' || array[1][0] == '-')
		new_dir = create_new_path(all, array);
	else
		new_dir = ft_substr(array[1], 0, ft_strlen(array[1]));
	if (chdir(new_dir) == -1)
	{
		free(new_dir);
		dprintf(2, "error invalid dir\n");
		all->last_exit_status = 1;
		kill_process(all);
	}
	pwd = get_current_dir();
	update_pwd_oldpwd(all, pwd);
	free(new_dir);
	// kill_process(all);
}

// char *create_new_path(t_all *all, char **array)
// {
// 	int		i;
// 	char	*dir;
// 	char	*new_dir;

// 	i = 0;
// 	if (!array)
// 	{
// 		dir = value_of_dollar_sign(all, "HOME", 4);
// 		new_dir = remove_quotes_cmd(dir);
// 		return (new_dir);
// 	}
// 	dir = get_current_dir();
// 	while (array && array[i])
// 	{
// 		if (!ft_strncmp(array[i], ".", 2))
// 		{
// 			i++;
// 			continue ;
// 		}
// 		else if (!ft_strncmp(array[i], "..", 3))
// 		{
// 			new_dir = ft_substr(dir, 0, number_of_char_until_first_slash(dir));
// 			if (new_dir[0] == '\0')
// 			{
// 				free(new_dir);
// 				new_dir = ft_substr(dir, 0, 1);
// 			}
// 			free(dir);
// 			dir = new_dir;
// 			// printf("new_dir = (%s)\n", new_dir);
// 		}
// 		else if (!ft_strncmp(array[i], "~", 2) && i == 0)
// 		{
// 			new_dir = value_of_dollar_sign(all, "HOME", 4);
// 			dir = remove_quotes_cmd(new_dir);
// 		}
// 		else if (!ft_strncmp(array[i], "-", 2) && i == 0)
// 		{
// 			new_dir = value_of_dollar_sign(all, "OLDPWD", 7);
// 			dir = ft_strjoin_free(dir, "/");
// 			dir = ft_strjoin_free(dir, new_dir);
// 			free(new_dir);
// 		}
// 		else
// 		{
// 			// printf("new dir (%s)\n", dir);
// 			dir = ft_strjoin_free(dir, "/");
// 			dir = ft_strjoin_free(dir, array[i]);
// 		}
// 		i++;
// 	}
// 	// printf("new dir (%s)\n", dir);
// 	return (dir);
// }

// void	ft_cd(t_all *all)
// {
// 	char	*current_dir;
// 	char	*new_dir;
// 	char	**array;
// 	int		total_indexes;

// 	current_dir = get_current_dir();
// 	array = NULL;
// 	// dprintf(2, "(%s)\n", current_dir);
// 	total_indexes = 0;
// 	while (all->line->each_cmd->cmd && all->line->each_cmd->cmd[total_indexes])
// 		total_indexes++;
// 	// printf("here (%s)\n", current_dir);
// 	if (total_indexes > 2)
// 	{
// 		dprintf(2, "error bash: cd: too many arguments\n");
// 		exit(EXIT_FAILURE);
// 	}
// 	dprintf(2, "total_indexes(%d)\n", total_indexes);
// 	if (total_indexes > 1 && !ft_strncmp(all->line->each_cmd->cmd[1], "/", 2))
// 	{
// 		new_dir = ft_substr(current_dir, 0, 1);
// 	}
// 	else
// 	{
// 		if (total_indexes == 1)
// 		{
// 			dprintf(2, "just\n");
// 			new_dir = create_new_path(all, array);
// 		}
// 		else
// 		{
// 			array = ft_split(all->line->each_cmd->cmd[1], '/');
// 			if (total_indexes == 2)
// 			{
// 				new_dir = create_new_path(all, array);
// 			}
// 		}
// 	}
// 	// printf("new dir is (%s)\n", new_dir);
// 	if (chdir(new_dir) == -1)
// 	{
// 		dprintf(2, "error invalid dir\n");
// 	}
// 	change_pwd_oldpwd(all, new_dir);
// 	free(current_dir);
// 	free(new_dir);
// 	// current_dir = get_current_dir();
// 	// dprintf(2, "here %s\n", current_dir);
// }

char	*ft_joined_for_export(char *str, int start)
{
	char	*temp1;
	char	*temp2;

	temp1 = ft_substr(str, 0, start + 1);
	temp2 = ft_strjoin("declare -x ", temp1);
	free(temp1);
	if (str[start] == '=')
	{
		temp1 = ft_strjoin(temp2, "\"");
		free(temp2);
		temp2 = ft_substr(str, start + 1, ft_strlen(str) - (start + 1));
		temp1 = ft_strjoin_free(temp1, temp2);
		free(temp2);
		temp2 = ft_strjoin_free(temp1, "\"");
	}
	// printf("str for export is (%s)\n", temp2);
	return (temp2);
}

int	ft_isalnum_under(int i)
{
	if (ft_isalpha(i) || ft_isdigit(i) || i == '_')
		return (1);
	return (0);
}

void	ft_printexport(t_all *all)
{
	t_chunk	*chunks;

	chunks = all->export;
	while (chunks)
	{
		printf("%s\n", chunks->str);
		chunks = chunks->next;
	}
}

int		check_export_in(t_all *all, char *str)
{
	int i;

	i = 0;
	if (ft_strchr("1234567890=", str[0]))
	{
		printf("bashs: export: %s: not a valid identifier\n", str);
		all->last_exit_status = 1;
		return (0);
	}
	while (str[i] && str[i] != '=')// && ft_isalnum_under(str[i]))
	{
		if (!ft_isalnum_under(str[i]))
		{
			printf("bashs: export: %s: not a valid identifier\n", str);
			all->last_exit_status = 1;
			return (0);
		}
		i++;
	}
	all->last_exit_status = 0;
	if (str[i] && str[i] == '=')
		return (2);
	else
		return (1);
	
}

int		is_in_export(t_chunk *node, char *str)
{
	t_chunk	*temp;
	int		i;

	temp = node;
	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	while (temp)
	{
		if (!ft_strncmp(temp->str + 11, str, i))
		{
			if (str[i])
			{
				// dprintf(2, "2\n");
				return (2);
			}
			else
			{
				// dprintf(2, "1\n");
				return (1);
			}
		}
		temp = temp->next;
	}
	return (0);
}

int		is_in_envp(t_chunk *node, char *str)
{
	t_chunk	*temp;
	int		i;

	temp = node;
	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	while (temp)
	{
		if (!ft_strncmp(temp->str, str, i))
		{
			if (str[i])
				return (2);
			else
				return (1);
		}
		temp = temp->next;
	}
	return (0);
}

void	update_export(t_all *all, char *str, int varvalue)
{
	int		i;
	char	*temp;
	char	*temp2;
	t_chunk	*list;

	list = all->export;
	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	if (varvalue == 1 && is_in_export(list, str) > 0)
		return ;
	else if (varvalue > 0 && is_in_export(list, str) == 0)
	{
		temp = ft_joined_for_export(str, i);
		ft_lstadd_back_chunk(&all->export, ft_lstnewchunk(temp));
	}
	else if (varvalue == 2 && is_in_export(list, str) > 0)
	{
		temp2 = ft_substr(str, 0, i);
		temp = ft_strjoin("declare -x ", temp2);
		free(temp2);
		ft_remove_var(all->export, temp);
		free(temp);
		temp = ft_joined_for_export(str, i);
		ft_lstadd_back_chunk(&all->export, ft_lstnewchunk(temp));
	}
}

void	update_envp(t_all *all, char *str, int varvalue)
{
	int		i;
	char	*temp;
	t_chunk	*list;

	list = all->envp;
	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	if (varvalue != 2)
		return ;
	if (is_in_envp(list, str) == 0)
	{
		temp = ft_strdup(str);
		ft_lstadd_back_chunk(&all->envp, ft_lstnewchunk(temp));
	}
	else if (is_in_envp(list, str) > 0)
	{
		ft_remove_var(all->envp, str);
		temp = ft_strdup(str);
		ft_lstadd_back_chunk(&all->envp, ft_lstnewchunk(temp));
	}
}

void	ft_export(t_all *all)
{
	t_chunk	*chunks;
	int		index;
	int		varvalue;

	chunks = all->export;
	index = 1;
	if (!all->line->each_cmd->cmd[1])
		ft_printexport(all);
	else
	{
		while (all->line->each_cmd->cmd[index])
		{
			varvalue = check_export_in(all, all->line->each_cmd->cmd[index]);
			if (varvalue == 1)
				update_export(all, all->line->each_cmd->cmd[index], varvalue);
			if (varvalue == 2)
			{
				update_envp(all, all->line->each_cmd->cmd[index], varvalue);
				update_export(all, all->line->each_cmd->cmd[index], varvalue);
				if (all->envcur)
					free2d(all->envcur);
				all->envcur = update_env(all);
			}
			index++;
		}
		sorter_export(all);
	}
}

// void	ft_export(t_all	*all)
// {
// 	int		i;
// 	int		i_char;
// 	int		to_env;
// 	t_chunk	*chuncks;
// 	char	*joined_for_export;

// 	i = 0;
// 	chuncks = all->export;
// 	while (all->line->each_cmd->cmd[i] != NULL)
// 		i++;
// 	if (i == 1)
// 	{
// 		while (chuncks)
// 		{
// 			printf("%s\n", chuncks->str);
// 			chuncks = chuncks->next;
// 		}
// 	}
// 	else
// 	{
// 		// there are some arguments
// 		i = 1;
// 		while (all->line->each_cmd->cmd[i] != NULL)
// 		{
// 			to_env = 0;
// 			i_char = 0;
// 			while (all->line->each_cmd->cmd[i][i_char] && (all->line->each_cmd->cmd[i][i_char] == '=' || ft_isalnum_under(all->line->each_cmd->cmd[i][i_char])))
// 			{
// 				if (all->line->each_cmd->cmd[i][i_char] == '=')
// 					to_env = 1;
// 				i_char++;
// 			}
// 			if (all->line->each_cmd->cmd[i][i_char])
// 			{
// 				printf("bash: export: %s: not a valid identifier\n", all->line->each_cmd->cmd[i]);
// 				all->last_exit_status = 1;
// 				return ;
// 			}
// 			i_char = 0;
// 			if (ft_strchr("1234567890=", all->line->each_cmd->cmd[i][0]))
// 			{
// 				printf("bashs: export: %s: not a valid identifier\n", all->line->each_cmd->cmd[i]);
// 				all->last_exit_status = 1;
// 				return ;
// 			}
// 			else
// 			{
// 				dprintf(2, "str = (%s)\n", all->line->each_cmd->cmd[i]);
// 				if (to_env)
// 				{
// 					ft_lstadd_back_chunk(&all->envp, ft_lstnewchunk(all->line->each_cmd->cmd[i]));
// 				}
// 				while (all->line->each_cmd->cmd[i][i_char] && all->line->each_cmd->cmd[i][i_char] != '=')
// 					i_char++;
// 				if (all->line->each_cmd->cmd[i][i_char])
// 				{
// 					joined_for_export = ft_joined_for_export(all->line->each_cmd->cmd[i], i_char);
// 					ft_lstadd_back_chunk(&all->export, ft_lstnewchunk(joined_for_export));
// 					free(joined_for_export);
// 				}
// 				else
// 				{
// 					joined_for_export = ft_strjoin("declare -x ", all->line->each_cmd->cmd[i]);
// 					ft_lstadd_back_chunk(&all->export, ft_lstnewchunk(joined_for_export));
// 					free(joined_for_export);
// 				}
// 			}
// 			i++;
// 		}
// 		sorter_export(all);
// 		if (to_env == 1)
// 		{
// 			if (all->envcur)
// 				free2d(all->envcur);
// 			all->envcur = update_env(all);
// 		}
// 	}
// 	// just to test the out put
// 	// printf("test\n\n\n");
// 	// chuncks = all->export;
// 	// while (chuncks)
// 	// {
// 	// 	printf("%s\n", chuncks->str);
// 	// 	chuncks = chuncks->next;
// 	// }
// }

// void	error_exit(t_all *all)
// {

// }

void	ft_exit(t_all *all)
{
	int		i;
	int		local;
	char	*str;

	i = 0;
	str = all->line->each_cmd->cmd[1];
	//check arguments
	if (str == NULL)
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
			exit(local);
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
			if (str[0] && (str[0] == '+' || str[0] == '-'))
				i++;
			while (str[i] && ft_isdigit(str[i]))
				i++;
			if (str[i] != '\0')
			{
				//there is another char
				printf(" %s: numeric argument required\n", str);
				all->last_exit_status = 2;
				exit(2);
			}
			else
			{
				//just numbers
				all->last_exit_status = ft_atoi(str) % 256;
				while (all->last_exit_status < 0)
					all->last_exit_status += 256;
				exit(all->last_exit_status);
			}
		}
	}

}
