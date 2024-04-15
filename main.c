
#include "minishell.h"

// int	fill_cmd(char *line, int j, t_all *all, int i);
// int	fill_delimiter(char *line, int j, t_all *all, int i);
// int	fill_name_infile(char *line, int j, t_all *all, int i);
// int	fill_flag(char *line, int j, t_all *all, int i);
// char	*join_all_infiles(t_all *all, int i, char *str);

// void	ft_free_3darray(char ***array_3d)
// {
// 	int	i;
// 	int	j;

// 	i = 0;
// 	if (array_3d == NULL)
// 		return ;
// 	while (array_3d[i] != NULL)
// 	{
// 		j = 0;
// 		while (array_3d[i][j] != NULL)
// 		{
// 			free(array_3d[i][j]);
// 			j++;
// 		}
// 		free(array_3d[i]);
// 		i++;
// 	}
// 	free(array_3d);
// }

// void	ft_free_array_3d_and_exit(char ***array_3d, int n)
// {
// 	if (array_3d)
// 		ft_free_3darray(array_3d);
// 	if (n == -1)
// 	{
// 		write(2, "memory allocation failed\n", 25);
// 	}
// 	if (n == -2)
// 	{
// 		write(2, "Error pipe failed\n", 18);
// 	}
// 	if (n == -3)
// 		write(2, "Error split() failed\n", 21);
// 	exit(1);
// }

// char	**get_all_paths(char **envm)
// {
// 	int		i;
// 	char	**str;

// 	i = 0;
// 	while (envm[i] != NULL)
// 	{
// 		if (ft_strncmp(envm[i], "PATH", 4) == 0)
// 		{
// 			str = ft_split(&envm[i][5], ':');
// 			if (!str)
// 			{
// 				return (NULL);
// 			}
// 			break ;
// 		}
// 		i++;
// 	}
// 	return (str);
// }

// char	***initializing_3d(int argc, char **argv, char **envp)
// {
// 	char	***array_3d;
// 	int		i;

// 	i = 0;
// 	array_3d = ft_calloc(argc + 1, sizeof(char **));
// 	if (!array_3d)
// 		ft_free_array_3d_and_exit(array_3d, -1);
// 	while (1)
// 	{
// 		printf("argv[0] is (%s)\n", argv[0]);
// 		while(*argv[i] == ' ')
// 			argv[i]++;
// 		array_3d[i] = ft_split(argv[i], ' ');
// 		printf("array_3d[i][0] is (%s)\n", array_3d[i][0]);
// 		// printf("array_3d[i][1] is (%s)\n", array_3d[i][1]);
// 		// printf("array_3d[i][2] is (%s)\n", array_3d[i][2]);
// 		if (!array_3d[i])
// 			ft_free_array_3d_and_exit(array_3d, -2);
// 		break ;
// 	}
// 	i++;
// 	array_3d[i] = get_all_paths(envp);
// 	if (!array_3d[i])
// 		ft_free_array_3d_and_exit(array_3d, -3);
// 	return (array_3d);
// }

// int	count_cmd(char *line)
// {
// 	int	i;
// 	int	j;
// 	int	not_empty;

// 	i = 0;
// 	j = 0;
// 	while (line[j] != '\0')
// 	{
// 		while ((line[j] == ' ' || line[j] == '\t') && line[j] != '\0')
// 			j++;
// 		not_empty = 0;
// 		while (line[j] != '|' && line[j] != '\0')
// 		{
// 			not_empty++;
// 			j++;
// 		}
// 		if (not_empty == 0 && (line[j - 1] != '\0' || line[j] != '\0'))
// 		{
// 			//empty cmd Error don't execute the line
// 			printf("empty cmd\n");
// 			//not_empty = 1;
// 		}
// 		i++;
// 	}
// 	return (i);
// }

int	count_cmd(char *line)
{
	int i = 0;
	int j = 0;

	while (line[j] != '\0')
	{
		while ((line[j] == ' ' || line[j] == '\t') && line[j] != '\0')
			j++;

		if (line[j] == '|')
		{
			printf("empty cmd here\n");
			while (line[j] == '|')
				j++;
		}
		else
		{
			while (line[j] != '|' && line[j] != '\0')
				j++;
			i++;
		}
	}
	printf(" i is (%d)\n", i);
	return (i);
}

// int	fill_delimiter(char *line, int j, t_all *all, int i)
// {
// 	int		temp;
// 	int		old_j;
// 	char	*str;

// 	temp = 0;
// 	while (line[j] == ' ')
// 		j++;
// 	old_j = j;
// 	while (line[j] != ' ' && line[j] != '|' && line[j] != '\0')
// 	{
// 		temp++;
// 		j++;
// 	}
// 	str = ft_substr(line, old_j, temp);
// 	//printf("str is (%s)\n", str);
// 	all->each_cmd[i].delimiter = ft_strdup(str);
// 	all->each_cmd[i].is_heredoc = true;
// 	free(str);
// 	while (line[j] == ' ' && line[j] != '\0')
// 		j++;
// 	return (j);
// }

// char	*join_all_outfiles(t_all *all, int i, char *str)
// {
// 	int		j;
// 	char	*whole_outfiles;
// 	char	*temp;
// 	char	*new_outfiles;
// 	char	*final_outfiles;

// 	j = 0;
// 	whole_outfiles = NULL;
// 	final_outfiles = NULL;
// 	new_outfiles = NULL;
// 	temp = NULL;
// 	while (all->each_cmd[i].infile[j] != NULL)
// 	{
// 		temp = ft_strjoin(all->each_cmd[i].infile[j], " ");
// 		if (!temp)
// 		{
// 			if (whole_outfiles)
// 				free(whole_outfiles);
// 			return (NULL);
// 		}
// 		if (whole_outfiles == NULL)
// 			whole_outfiles = ft_strdup(temp);
// 		else
// 		{
// 			new_outfiles = ft_strjoin(whole_outfiles, temp);
// 			if (!new_outfiles)
// 			{
// 				free(whole_outfiles);
// 				return (NULL);
// 			}
// 			free(whole_outfiles);
// 			whole_outfiles = ft_strdup(new_outfiles);
// 			free(new_outfiles);
// 		}
// 		free(temp);
// 		j++;
// 	}
// 	final_outfiles = ft_strjoin(whole_outfiles, str);
// 	printf("final_outfiles is (%s)\n", final_outfiles);
// 	free(whole_outfiles);
// 	return (final_outfiles);
// }

// char	*join_all_infiles(t_all *all, int i, char *str)
// {
// 	int		j;
// 	char	*whole_infiles;
// 	char	*temp;
// 	char	*new_infiles;
// 	char	*final_infiles;

// 	j = 0;
// 	whole_infiles = NULL;
// 	final_infiles = NULL;
// 	new_infiles = NULL;
// 	temp = NULL;
// 	while (all->each_cmd[i].infile[j] != NULL)
// 	{
// 		temp = ft_strjoin(all->each_cmd[i].infile[j], " ");
// 		if (!temp)
// 		{
// 			if (whole_infiles)
// 				free(whole_infiles);
// 			return (NULL);
// 		}
// 		if (whole_infiles == NULL)
// 			whole_infiles = ft_strdup(temp);
// 		else
// 		{
// 			new_infiles = ft_strjoin(whole_infiles, temp);
// 			if (!new_infiles)
// 			{
// 				free(whole_infiles);
// 				return (NULL);
// 			}
// 			free(whole_infiles);
// 			whole_infiles = ft_strdup(new_infiles);
// 			free(new_infiles);
// 		}
// 		free(temp);
// 		j++;
// 	}
// 	final_infiles = ft_strjoin(whole_infiles, str);
// 	free(whole_infiles);
// 	return (final_infiles);
// }


// int	fill_name_infile(char *line, int j, t_all *all, int i)
// {
// 	int		temp;
// 	int		old_j;
// 	char	*str;
// 	char	*join_infiles;

// 	temp = 0;
// 	if (line[j] == '<')
// 		j++;
// 	while (line[j] == ' ')
// 		j++;
// 	old_j = j;
// 	while (line[j] != ' ' && line[j] != '|' && line[j] != '\0')
// 	{
// 		temp++;
// 		j++;
// 	}
// 	str = ft_substr(line, old_j, temp);
// 	printf("str is (%s)\n", str);
// 	if (all->each_cmd[i].infile[0] != NULL)
// 	{
// 		join_infiles = join_all_infiles(all, i, str);
// 		all->each_cmd[i].infile = ft_split(join_infiles, ' ');
// 	}
// 	else
// 	{
// 		all->each_cmd[i].infile = ft_split(str, ' ');
// 		//free(str);
// 	}
// 	//all->each_cmd[i].infile = ft_strdup(str);
// 	free(str);
// 	all->each_cmd[i].is_infile = true;
// 	while (line[j] == ' ' && line[j] != '\0')
// 		j++;
// 	return (j);
// }

// int	fill_outfile_name(char *line, int j, t_all *all, int i)
// {
// 	int		temp;
// 	int		old_j;
// 	char	*str;
// 	char	*join_outfiles;

// 	temp = 0;
// 	if (line[j] == '>')
// 		j++;
// 	while (line[j] == ' ')
// 		j++;
// 	old_j = j;
// 	while (line[j] != ' ' && line[j] != '|' && line[j] != '\0')
// 	{
// 		temp++;
// 		j++;
// 	}
// 	str = ft_substr(line, old_j, temp);
// 	//printf("str is (%s)\n", str);
// 	if (all->each_cmd[i].outfile[0] != NULL)
// 	{
// 		join_outfiles = join_all_outfiles(all, i, str);
// 		all->each_cmd[i].outfile = ft_split(join_outfiles, ' ');
// 	}
// 	else
// 		all->each_cmd[i].outfile = ft_split(str, ' ');
// 	free(str);
// 	while (line[j] == ' ' && line[j] != '\0')
// 		j++;
// 	return (j);
// }




// char	*join_all_flags(t_all *all, int i, char *str)
// {
// 	printf("first line join_all_falgs\n");
// 	int j = 0;
// 	char *whole_flags = NULL;
// 	char *temp = NULL;
// 	char *new_flags = NULL;
// 	char *final_flags = NULL;

// 	printf("first falg in array is (%s)\n", all->each_cmd[i].flag[0]);
// 	printf("str is (%s)\n", str);

// 	if (all->each_cmd[i].flag[j])
// 	{
// 		while (all->each_cmd[i].flag[j])
// 		{
// 			temp = ft_strjoin(all->each_cmd[i].flag[j], " ");
// 			printf("temp is (%s)\n", temp);
// 			if (!temp)
// 			{
// 				if (whole_flags)
// 					free(whole_flags);
// 				return (NULL);
// 			}
// 			if (whole_flags == NULL)
// 				whole_flags = ft_strdup(temp);
// 			else
// 			{
// 				new_flags = ft_strjoin(whole_flags, temp);
// 				printf("new_falgs isssssssssssssssssssssss (%s)\n", new_flags);
// 				if (!new_flags)
// 				{
// 					free(whole_flags);
// 					return (NULL);
// 				}
// 				free(whole_flags);
// 				whole_flags = ft_strdup(new_flags);
// 				free(new_flags);
// 			}
// 			free(temp);
// 			printf("whole_flags is (%s)\n", whole_flags);
// 			j++;
// 		}
// 	}
// 	final_flags = ft_strjoin(whole_flags, str);
// 	printf("final_flags is (%s)\n", final_flags);
// 	if (whole_flags)
// 		free(whole_flags);
// 	return (final_flags);
// }

// int	fill_flag(char *line, int j, t_all *all, int i)
// {
// 	int		temp;
// 	int		old_j;
// 	char	*str;
// 	char	*join_flags;

// 	temp = 0;
// 	printf("fill falg\n");
// 	while (line[j] == ' ')
// 		j++;
// 	if (line[j] == '|' || line[j] == '>' ||  (line[j] == '<' && line[j + 1] \
// 	== '<') || (line[j] == '>' && line[j + 1] == '>') || line[j] == '<')
// 		return (j);
// 	old_j = j;
// 	while (line[j] != '>' && line[j] != '<' && line[j] != '|' \
// 	&& line[j] != ' ' && line[j] != '\0')
// 	{
// 		temp++;
// 		j++;
// 	}
// 	str = ft_substr(line, old_j, temp);
// 	printf("before check\n");
// 	if (all->each_cmd[i].flag[0] != NULL)
// 	{
// 		printf("here hreree ehetet e ee e\n");
// 		join_flags = join_all_flags(all, i, str);
// 		printf("after join_flags func\n");
// 		all->each_cmd[i].flag = ft_split(join_flags, ' ');
// 		printf("after add all to struct\n");
// 	}
// 	//printf("str is (%s)\n", str);
// 	else
// 	{
// 		all->each_cmd[i].flag = ft_split(str, ' ');
// 		free(str);
// 	}
// 	while (line[j] == ' ' && line[j] != '\0')
// 		j++;
// 	printf("letter in flag is (%c)\n", line[j]);
// 	return (j);
// }

// int	fill_cmd(char *line, int j, t_all *all, int i)
// {
// 	int		temp;
// 	int		old_j;
// 	char	*str;

// 	temp = 0;
// 	if (all->each_cmd[i].cmd != NULL)
// 	{
// 		printf("here to flags\n");
// 		return (fill_flag(line, j, all, i));
// 	}
// 	while (line[j] == ' ')
// 		j++;
// 	if (line[j] == '|')
// 		return (j);
// 	old_j = j;
// 	while (line[j] != ' ' && line[j] != '|' && line[j] != '\0')
// 	{
// 		temp++;
// 		j++;
// 	}
// 	str = ft_substr(line, old_j, temp);
// 	//printf("str is (%s)\n", str);
// 	all->each_cmd[i].cmd = ft_strdup(str);
// 	free(str);
// 	while (line[j] == ' ' && line[j] != '\0')
// 		j++;
// 	return (fill_flag(line, j, all, i));
// }



// void	fill_array_cmd(char *curline, int total_cmd, t_all *all)
// {
// 	int		i;
// 	int		j;
// 	t_line	*line;
// 	line = all->line;

// 	i = 0;
// 	j = 0;
// 	while (i < total_cmd)
// 	{
// 		while ((curline[j] == ' ' || curline[j] == '\t') && curline[j] != '\0')
// 			j++;
// 		while (curline[j] != '\0')
// 		{
// 			if (curline[j] == '|')
// 				break ;
// 			if (curline[j] == '<' && curline[j + 1] == '<')
// 			{
// 				j = j + 2;
// 				printf("to delimiter and i is %d\n", i);
// 				j = fill_delimiter(curline, j, all, i);
// 			}
// 			if (curline[j] == '<' && curline[j + 1] != '<')
// 			{
// 				j++;
// 				printf("to name_infile and i is %d\n", i);
// 				j = fill_name_infile(curline, j, all, i);
// 			}
// 			if (curline[j] == '>' || (curline[j] == '>' && curline[j + 1] == '>'))
// 			{
// 				j++;
// 				printf("to outfile_name and i is %d\n", i);
// 				j = fill_outfile_name(curline, j, all, i);
// 			}
// 			else
// 			{
// 				printf("to fill_cmd and i is %d\n", i);
// 				j = fill_cmd(curline, j, all, i);
// 			}
// 		}
// 		i++;
// 		if (curline[j] == '|')
// 			j++;
// 	}
// }



int	skip_spaces(int temp_j, char *curline, t_line *line)
{
	int	wrong;

	wrong = 0;
	while (curline[temp_j] != '\0' && (curline[temp_j] == ' ' || curline[temp_j] == '\t'))
	{
		temp_j++;
	}
	if (ft_strchr("<>|$", curline[temp_j]))
		wrong = 1;
	return (wrong);
}

int	ft_search_next_specific(int temp_j, char *curline, t_line *line)
{
	int	old_temp;
	int curchar;

	if (curline[temp_j] == '|')
	{
		line->invalid = skip_spaces((temp_j + 1), curline, line);

	}
	if (curline[temp_j] == '<')
	{
		if (curline[temp_j + 1] == '<')
			temp_j + 1;
		line->invalid = skip_spaces((temp_j + 1), curline, line);
	}
	if (curline[temp_j] == '>')
	{
		if (curline[temp_j + 1] == '>')
			temp_j + 1;
		line->invalid = skip_spaces((temp_j + 1), curline, line);
	}
	if (line->invalid)
		exit;
	// if (curline[temp_j] == '$')
	// {
	// 	if(curline[temp_j + 1] == '?')
	// 		temp_j + 1;
	// 	line->invalid = skip_spaces((temp_j + 1), curline, line);
	// }



	// temp_j++;
	// old_temp = temp_j;
	// while (curline[temp_j] != '\0')
	// {
	// 	while (curline[temp_j] == ' ' || curline[temp_j] == '\t')
	// 	{
	// 		temp_j++;
	// 	}
	// 	if (curline[temp_j] == '|')
	// 	{
	// 		line->invalid = -1;
	// 		break ;
	// 	}
	// 	else if (curline[temp_j] == '<')
	// 	{
	// 		if (curline[old_temp - 1] == '<' && (old_temp + 1) == temp_j)
	// 		{
	// 			while (curline[temp_j] == ' ' || curline[temp_j] == '\t')
	// 			{
	// 				temp_j++;
	// 			}
	// 			if (curline[temp_j] == '<' 
	// 		}
	// 	}
	// 	else if (curline[temp_j] == '>')
	// 	{

	// 	}
		
	// }
	

}

void	fill_array_cmd(char *curline, int total_cmd, t_all *all)
{
	int		i;
	int		j;
	int		temp_j;
	t_line	*line;
	line = all->line;

	i = 0;
	j = 0;
	while (i < total_cmd)
	{
		while ((curline[j] == ' ' || curline[j] == '\t') && curline[j] != '\0')
			j++;
		while (curline[j] != '\0')
		{
			if (curline[j] == '|')
				break ;
			temp_j = j;
			while (curline[temp_j] != '|' || curline[temp_j] != '<' || curline[temp_j]\
			!= '>' || curline[temp_j] != '\0')
			{
				temp_j++;
			}
			if (curline[temp_j] == '|><&' || curline[temp_j] == '\0')
			{
				ft_search_next_specific(temp_j, curline, line);
			}
			if (curline[j] == '<' && curline[j + 1] == '<')
			{
				j = j + 2;
				printf("to delimiter and i is %d\n", i);
				j = fill_delimiter(curline, j, all, i);
			}
			if (curline[j] == '<' && curline[j + 1] != '<')
			{
				j++;
				printf("to name_infile and i is %d\n", i);
				j = fill_name_infile(curline, j, all, i);
			}
			if (curline[j] == '>' || (curline[j] == '>' && curline[j + 1] == '>'))
			{
				j++;
				printf("to outfile_name and i is %d\n", i);
				j = fill_outfile_name(curline, j, all, i);
			}
			else
			{
				printf("to fill_cmd and i is %d\n", i);
				j = fill_cmd(curline, j, all, i);
			}
		}
		i++;
		if (curline[j] == '|')
			j++;
	}
}


t_all	*initialize_t_all(int total_cmd, char *curline)
{
	int		i;
	t_all	*all;
	t_line	*line;


	i = 0;
	all = malloc(sizeof(t_all));
	line = all->line;
	if (!all)
		exit(EXIT_FAILURE);
	line->total_cmd = total_cmd;
	line->each_cmd = ft_calloc(total_cmd, sizeof(t_cmd));
	if (!line->each_cmd)
	{
		free(all);
		exit(EXIT_FAILURE);
	}
	while (i < total_cmd)
	{
		printf("before initialize_t_all\n\n");
		line->each_cmd[i].flag = malloc(sizeof(char *) * 2);
		line->each_cmd[i].infile = malloc(sizeof(char *) * 2);
		line->each_cmd[i].outfile = malloc(sizeof(char *) * 2);
		line->each_cmd[i].flag[0] = NULL;
		line->each_cmd[i].flag[1] = NULL;
		line->each_cmd[i].infile[0] = NULL;
		line->each_cmd[i].infile[1] = NULL;
		line->each_cmd[i].outfile[0] = NULL;
		line->each_cmd[i].outfile[1] = NULL;
		i++;
	}
	fill_array_cmd(curline, total_cmd, all);
	return (all);
}

// void	print_elements(t_all *all)
// {
// 	int	i;
// 	int	j;

// 	// t_line *line;
// 	// line = all->line;

// 	i = 0;
// 	while (i < line->total_cmd)
// 	{
// 		if (all->each_cmd[i].cmd != NULL)
// 			printf("cmd name (%s) and i %d\n", all->each_cmd[i].cmd, i);
// 		if (all->each_cmd[i].flag[0] != NULL)
// 		{
// 			j = 0;
// 			while (all->each_cmd[i].flag[j])
// 			{
// 				printf("all->each_cmd[i].flag[j] (%s) and i %d\n", all->each_cmd[i].flag[j], i);
// 				j++;
// 			}
// 		}
// 		if (all->each_cmd[i].infile[0] != NULL)
// 		{
// 			j = 0;
// 			while (all->each_cmd[i].infile[j])
// 			{
// 				printf("all->each_cmd[i].infile[j] (%s) and i %d\n", all->each_cmd[i].infile[j], i);
// 				j++;
// 			}
// 		}
// 		if (all->each_cmd[i].outfile != NULL)
// 		{
// 			j = 0;
// 			while (all->each_cmd[i].outfile[j])
// 			{
// 				printf("all->each_cmd[i].outfile[j] (%s) and i %d\n", all->each_cmd[i].outfile[j], i);
// 				j++;
// 			}
// 		}
// 		if (all->each_cmd[i].delimiter != NULL)
// 			printf("delimiter name (%s) and i %d\n", all->each_cmd[i].delimiter, i);
// 		i++;
// 	}
// }

int	main(int argc, char **argv, char **envp)
{
	//char	***my_array;
	char	*curline;
	int		amount_cmd;
	t_all	*all;
	char	*pwd;


	//line = NULL;
	//rl_initialize();
	curline = readline("Minishell >");
	pwd = get_current_dir();
	change_directory("35 3");
	while (curline)
	{
		if (ft_strlen(curline) > 1)
			add_history(curline);
		printf("line is (%s)\n", curline);
		//my_array = initializing_3d(argc, &line, envp);
		amount_cmd = count_cmd(curline);
		all = initialize_t_all(amount_cmd, curline);
		// printf("print element\n\n\n");
		// print_elements(all);
		printf(" after intializing \n");
		free(curline);
		curline = readline("Minishell >");
	}

	return (0);
}
