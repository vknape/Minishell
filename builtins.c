
#include "minishell.h"

char	*get_current_dir(t_all *all)
{
	size_t	buf_size;
	char	*buf;
	char	*ptr;

	buf_size = 1024;
	buf = malloc(buf_size);
	if (!buf && errno == 12)
		memory_allocation_failed(all);
	ptr = getcwd(buf, buf_size);
	if (!ptr && errno == 12)
		memory_allocation_failed(all);
	return (ptr);
}

void	ft_pwd(t_all *all)
{
	char	*current;

	current = get_current_dir(all);
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
	while (i < n && (str1[i] || str2[i]))
	{
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

// char	*make_and_protect_substr(t_all *all, char *str, int start, int len)
// {
// 	char	*new;

// 	new = ft_substr(str, start, len);
// 	if (!new && errno == 12)
// 		memory_allocation_failed(all);
// 	return ()

// }

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

void	join_all_indexes_of_array(t_all *all, char **array_str, int index, int new_line)
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

void	free_from_n_index(int index, char **array)
{
	while (index >= 0)
	{
		free(array[index]);
		index--;
	}
	free(array);
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
	if (!env_updated && errno == 12)
		memory_allocation_failed(all);
	while (temp)
	{
		env_updated[index++] = ft_strdup(temp->str);
		if (!env_updated[index - 1] && errno == 12)
		{
			free_from_n_index(index - 1, env_updated);
			memory_allocation_failed(all);
		}
		temp = temp->next;
	}
	env_updated[index] = NULL;
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
		if (!c && errno == 12)
			memory_allocation_failed(all);
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

// void	update_pwd_oldpwd(t_all *all, char *oldpwd)
// {
// 	char	*pwd;
// 	char	*temp;

// 	temp = ft_strjoin("OLDPWD=", oldpwd);
// 	free(oldpwd);
// 	oldpwd = ft_strdup(temp);
// 	update_envp(all, temp, 2);
// 	update_export(all, oldpwd, 2);
// 	free(oldpwd);
// 	free(temp);
// 	pwd = get_current_dir(all);
// 	temp = ft_strjoin("PWD=", pwd);
// 	free(pwd);
// 	pwd = ft_strdup(temp);
// 	update_envp(all, temp, 2);
// 	update_export(all, pwd, 2);
// 	free(pwd);
// 	free(temp);
// 	if (all->envcur)
// 		free2d(all->envcur);
// 	all->envcur = update_env(all);
// 	sorter_export(all);
// }

void	update_pwd(t_all *all)
{
	char	*pwd;
	char	*temp;

	pwd = get_current_dir(all);
	// temp = ft_strjoin("PWD=", pwd);
	all->line->temp = ft_strjoin("PWD=", pwd);
	if (!all->line->temp && errno == 12)
	{
		free(pwd);
		memory_allocation_failed(all);
	}
	free(pwd);
	// pwd = ft_strdup(temp);
	// if (!pwd && errno == 12)
	// {
	// 	free(temp);
	// 	memory_allocation_failed(all);
	// }
	update_envp(all, all->line->temp, 2);
	update_export(all, all->line->temp, 2);
	free(all->line->temp);
	all->line->temp = NULL;
	// free(pwd);
	// free(temp);

}

void	update_pwd_oldpwd(t_all *all, char *oldpwd)
{
	char	*temp;

	// temp = ft_strjoin("OLDPWD=", oldpwd);
	all->line->temp = ft_strjoin("OLDPWD=", oldpwd);
	if (!all->line->temp && errno == 12)
	{
		free(oldpwd);
		memory_allocation_failed(all);
	}
	free(oldpwd);
	// oldpwd = ft_strdup(temp);
	// if (!oldpwd && errno == 12)
	// {
	// 	free(temp);
	// 	memory_allocation_failed(all);
	// }
	update_envp(all, all->line->temp, 2);
	update_export(all, all->line->temp, 2);
	free(all->line->temp);
	all->line->temp = NULL;
	// free(oldpwd);
	// free(temp);
	update_pwd(all);
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

char *create_new_path2(t_all *all, char **array)
{
	char	*dir;
	char	*new_dir;

	new_dir = value_of_dollar_sign(all, "OLDPWD", 7);
	if (!new_dir && errno == 12)
		memory_allocation_failed(all);
	dir = remove_quotes_cmd(new_dir);
	if (!dir && errno == 12)
		memory_allocation_failed(all);
	write (1, dir, ft_strlen(dir));
	write (1, "\n", 1);
	return (dir);
}

char *create_new_path(t_all *all, char **array)
{
	char	*dir;
	char	*new_dir;

	if (!array[1] || array[1][0] == '~')
	{
		new_dir = value_of_dollar_sign(all, "HOME", 4);
		if (!new_dir && errno == 12)
			memory_allocation_failed(all);
		dir = remove_quotes_cmd(new_dir);
		if (!dir && errno == 12)
			memory_allocation_failed(all);
		if (array[1] && array[1][1])
		{
			new_dir = ft_substr(array[1], 1, ft_strlen(array[1]));
			if (!new_dir && errno == 12)
				memory_allocation_failed(all);
			dir = ft_strjoin_free(dir, new_dir);
			free(new_dir);
			if (!dir && errno == 12)
				memory_allocation_failed(all);
		}
	}
	else if (array[1][0] == '-')
		dir = create_new_path2(all, array);
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

void	ft_cd2(t_all *all, char *new_dir)
{
	char	*pwd;

	pwd = get_current_dir(all);
	if (chdir(new_dir) == -1)
	{
		create_print_error(all, new_dir, 5);
		free(new_dir);
		free(pwd);
		all->last_exit_status = 1;
		return ;
	}
	update_pwd_oldpwd(all, pwd);
	free(new_dir);
}

void	ft_cd(t_all *all)
{
	char	*new_dir;
	char	**array;
	char	*pwd;

	array = all->line->each_cmd->cmd;
	if (array[1] && array[2])
	{
		create_print_error(all, array[2], 2);
		all->last_exit_status = 1;
		return ;
	}
	if (!array[1])
		new_dir = create_new_path(all, array);
	else if (array[1][0] == '~' || array[1][0] == '-')
		new_dir = create_new_path(all, array);
	else
	{
		new_dir = ft_substr(array[1], 0, ft_strlen(array[1]));
		if (!new_dir && errno == 12)
			memory_allocation_failed(all);
	}
	ft_cd2(all, new_dir);
	// pwd = get_current_dir(all);
	// if (chdir(new_dir) == -1)
	// {
	// 	create_print_error(all, new_dir, 5);
	// 	free(new_dir);
	// 	free(pwd);
	// 	all->last_exit_status = 1;
	// 	return ;
	// }
	// update_pwd_oldpwd(all, pwd);
	// free(new_dir);
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
// 	{cat < infile.txt < out_new | ls | cat -e >outfile >tester/bredir.txt
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
// 			dir =cat < infile.txt < out_new | ls | cat -e >outfile >tester/bredir.txt remove_quotes_cmd(new_dir);
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
// }cat < infile.txt < out_new | ls | cat -e >outfile >tester/bredir.txt

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

char	*dup_protect(char *str, t_all *all)
{
	char	*temp;

	temp = NULL;
	temp = ft_strdup(str);
	if (!temp && errno == 12)
	{
		free(str);
		str = NULL;
		memory_allocation_failed(all);
	}
	return (temp);
}

char	*sub_protect(char *str, t_all *all, int start, int len)
{
	char	*temp;

	temp = NULL;
	temp = ft_substr(str, start, len);
	if (!temp && errno == 12)
	{
		free(str);
		str = NULL;
		memory_allocation_failed(all);
	}
	return (temp);
}

char	*ft_joined_for_export2(t_all	*all, char *str, char *temp2, int start)
{
	char *temp1;

	temp1 = ft_strjoin(temp2, "\"");
	free(temp2);
	if (!temp1 && errno == 12)
		memory_allocation_failed(all);
	temp2 = ft_substr(str, start + 1, ft_strlen(str) - (start + 1));
	if (!temp2 && errno == 12)
	{
		free(temp1);
		memory_allocation_failed(all);
	}
	temp1 = ft_strjoin_free(temp1, temp2);
	free(temp2);
	if (!temp1 && errno == 12)
		memory_allocation_failed(all);
	temp2 = ft_strjoin_free(temp1, "\"");
	if (!temp2 && errno == 12)
		memory_allocation_failed(all);
	return (temp2);
}

char	*ft_joined_for_export(t_all	*all, char *str, int start)
{
	char	*temp1;
	char	*temp2;

	temp1 = ft_substr(str, 0, start + 1);
	if (!temp1 && errno == 12)
		memory_allocation_failed(all);
	temp2 = ft_strjoin("declare -x ", temp1);
	free(temp1);
	if (!temp2 && errno == 12)
		memory_allocation_failed(all);
	if (str[start] == '=')
	{
		temp2 = ft_joined_for_export2(all, str, temp2, start);
		// temp1 = ft_strjoin(temp2, "\"");
		// free(temp2);
		// if (!temp1 && errno == 12)
		// 	memory_allocation_failed(all);
		// temp2 = ft_substr(str, start + 1, ft_strlen(str) - (start + 1));
		// if (!temp2 && errno == 12)
		// {
		// 	free(temp1);
		// 	memory_allocation_failed(all);
		// }
		// temp1 = ft_strjoin_free(temp1, temp2);
		// free(temp2);
		// if (!temp1 && errno == 12)
		// 	memory_allocation_failed(all);
		// temp2 = ft_strjoin_free(temp1, "\"");
		// if (!temp2 && errno == 12)
		// 	memory_allocation_failed(all);
	}
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
	int	i;

	i = 0;
	if (ft_strchr("1234567890=", str[0]))
	{
		create_print_error(all, str, 4);
		all->last_exit_status = 1;
		return (0);
	}
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum_under(str[i]))
		{
			create_print_error(all, str, 4);
			all->last_exit_status = 1;
			return (0);
		}
		i++;
	}
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
				return (2);
			else
				return (1);
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

void	update_export2(t_all *all, char *str, char *temp, int i)
{
	char	*temp2;

	temp2 = ft_substr(str, 0, i);
	if (!temp2 && errno == 12)
		memory_allocation_failed(all);
	temp = ft_strjoin("declare -x ", temp2);
	free(temp2);
	if (!temp && errno == 12)
		memory_allocation_failed(all);
	ft_remove_var(all->export, temp);
	free(temp);
	temp = ft_joined_for_export(all, str, i);
	ft_lstadd_back_chunk(&all->export, ft_lstnewchunk(all, temp));
}

void	update_export(t_all *all, char *str, int varvalue)
{
	int		i;
	char	*temp;
	t_chunk	*list;

	list = all->export;
	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	if (varvalue == 1 && is_in_export(list, str) > 0)
		return ;
	else if (varvalue > 0 && is_in_export(list, str) == 0)
	{
		temp = ft_joined_for_export(all, str, i);
		ft_lstadd_back_chunk(&all->export, ft_lstnewchunk(all, temp));
	}
	else if (varvalue == 2 && is_in_export(list, str) > 0)
		update_export2(all, str, temp, i);
	// {
	// 	temp2 = ft_substr(str, 0, i);
	// 	if (!temp2 && errno == 12)
	// 		memory_allocation_failed(all);
	// 	temp = ft_strjoin("declare -x ", temp2);
	// 	free(temp2);
	// 	if (!temp && errno == 12)
	// 		memory_allocation_failed(all);
	// 	ft_remove_var(all->export, temp);
	// 	free(temp);
	// 	temp = ft_joined_for_export(all, str, i);
	// 	ft_lstadd_back_chunk(&all->export, ft_lstnewchunk(all, temp));
	// }
}



void	update_envp(t_all *all, char *str, int varvalue)
{
	int		i;
	char	*temp;
	char	*to_remove;
	t_chunk	*list;

	list = all->envp;
	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	if (varvalue != 2)
		return ;
	if (is_in_envp(list, str) > 0)
	{
		to_remove = sub_protect(str, all, 0, i);
		ft_remove_var(all->envp, to_remove);
		free(to_remove);
	}
	temp = dup_protect(str, all);
	ft_lstadd_back_chunk(&all->envp, ft_lstnewchunk(all, temp));
}

// void	update_envp(t_all *all, char *str, int varvalue)
// {
// 	int		i;
// 	char	*temp;
// 	char	*to_remove;
// 	if (is_in_envp(list, str) == 0)
// 	{
// 		temp = ft_strdup(str);
// 		ft_lstadd_back_chunk(&all->envp, ft_lstnewchunk(all, temp));
// 	}
// 	else if (is_in_envp(list, str) > 0)
// 	{
// 		to_remove = ft_substr(str, 0, i);
// 		ft_remove_var(all->envp, to_remove);
// 		free(to_remove);
// 		temp = ft_strdup(str);
// 		ft_lstadd_back_chunk(&all->envp, ft_lstnewchunk(all, temp));
// 	}
// 	// if (!temp && errno == 12)
// 	// 	memory_allocation_failed(all);
// }

void	ft_export(t_all *all)
{
	int		index;
	int		varvalue;

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

// void	ft_exit(t_all *all, t_cmd *cmd)
// {
// 	int		i;
// 	int		local;
// 	char	*str;

// 	i = 0;
// 	str = cmd->cmd[1];
// 	if (str == NULL)
// 	{
// 		local = all->line->exit_value;
// 		if (g_glob == 2)
// 		{
// 			all->line->exit_value = 130;
// 			local = all->line->exit_value;
// 		}
// 		free_all(&all);
// 		exit(local);
// 	}
// 	else
// 	{
// 		if (cmd->cmd[2] != NULL)
// 		{
// 			create_print_error(all, cmd->cmd[2], 2);
// 			//dprintf(2, "too many arguments\n");
// 			all->last_exit_status = 1;
// 		}
// 		else if (cmd->cmd[2] == NULL)
// 		{
// 			if (str[0] && (str[0] == '+' || str[0] == '-'))
// 				i++;
// 			while (str[i] && ft_isdigit(str[i]))
// 				i++;
// 			if (str[i] != '\0')
// 			{
// 				create_print_error(all, str, 3);
// 				//dprintf(2, " %s: numeric argument required\n", str);
// 				all->last_exit_status = 2;
// 			}
// 			else
// 			{
// 				all->last_exit_status = ft_atoi(str) % 256;
// 				while (all->last_exit_status < 0)
// 					all->last_exit_status += 256;
// 			}
// 		}
// 		local = all->last_exit_status;
// 		free_all(&all);
// 		exit(local);
// 	}
// }

void	ft_exit2(t_all *all, t_cmd *cmd, char *str, int i)
{
	if (str[0] && (str[0] == '+' || str[0] == '-'))
		i++;
	while (str[i] && ft_isdigit(str[i]))
		i++;
	if (str[i] == '\0' && cmd->cmd[2])
	{
		create_print_error(all, cmd->cmd[0], 2);
		all->last_exit_status = 1;
		return ;
	}
	else if (str[i] != '\0')
	{
		create_print_error(all, cmd->cmd[0], 3);
		all->last_exit_status = 2;
	}
	else if (!cmd->cmd[2] && str[i] == '\0')
	{
		all->last_exit_status = ft_atoi(str) % 256;
		while (all->last_exit_status < 0)
			all->last_exit_status += 256;
	}
	i = all->last_exit_status;
	free_all(&all);
	exit(i);
}

void	ft_exit(t_all *all, t_cmd *cmd)
{
	int		i;
	int		local;
	char	*str;

	i = 0;
	str = cmd->cmd[1];
	if (str == NULL)
	{
		local = all->line->exit_value;
		if (g_glob == 2)
		{
			all->line->exit_value = 130;
			local = all->line->exit_value;
		}
		free_all(&all);
		exit(local);
	}
	else
		ft_exit2(all, cmd, str, i);
	// {
	// 	if (str[0] && (str[0] == '+' || str[0] == '-'))
	// 		i++;
	// 	while (str[i] && ft_isdigit(str[i]))
	// 		i++;
	// 	if (str[i] == '\0' && cmd->cmd[2])
	// 	{
	// 		create_print_error(all, cmd->cmd[0], 2);
	// 		all->last_exit_status = 1;
	// 		return ;
	// 	}
	// 	else if (str[i] != '\0')
	// 	{
	// 		create_print_error(all, cmd->cmd[0], 3);
	// 		all->last_exit_status = 2;
	// 	}
	// 	else if (!cmd->cmd[2] && str[i] == '\0')
	// 	{
	// 		all->last_exit_status = ft_atoi(str) % 256;
	// 		while (all->last_exit_status < 0)
	// 			all->last_exit_status += 256;
	// 	}
	// 	local = all->last_exit_status;
	// 	free_all(&all);
	// 	exit(local);
	// }
}
