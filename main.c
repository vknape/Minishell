
#include "minishell.h"



int	count_cmd(char *curline, t_all *all)
{
	int	i;
	int	j;

	i = 0;
	j = 1;
	while (curline[i] != '\0')
	{
		if (ft_strchr("|<>$", curline[i]))
		{
			while (curline[i] != '\0' && ft_strchr("|<>$", curline[i]))
				i++;
			j++;
		}
		i++;
	}
	all->line->total_cmd = j;
	return (j);

}



int	skip_spaces(int temp_j, char *curline, t_line *line)
{
	int	wrong;

	wrong = 0;
	printf("curline[temp_j] is %c\n", curline[temp_j]);
	while (curline[temp_j] != '\0' && (curline[temp_j] == ' ' || curline[temp_j] == '\t'))
	{
		temp_j++;
	}
	if (ft_strchr("<>|$", curline[temp_j]))
	{
		wrong = 1;
		printf("found wrong input\n");
	}
	return (wrong);
}

void	fill_cmd(char *curline, t_line *line, int max_p, int i)
{
	printf("fill cmd\n");
	line->each_cmd[i].cmd = ft_split_until(curline, ' ', max_p);
	printf("cmd in fill_cmd is %s\n", line->each_cmd[i].cmd[0]);

}

void	fill_infile(char *curline, t_line *line, int max_p, int i)
{
	printf("fill cmd\n");
	line->each_cmd[i].infile = ft_split_until(curline, ' ', max_p);
	line->each_cmd[i].is_infile = true;
}

void	fill_outfile(char *curline, t_line *line, int max_p, int i)
{
	printf("fill cmd\n");
	line->each_cmd[i].outfile = ft_split_until(curline, ' ', max_p);
	line->each_cmd[i].is_outfile = true;
}

void	fill_heredoc(char *curline, t_line *line, int max_p, int i)
{
	printf("fill cmd\n");
	line->each_cmd[i].delimiter = ft_substr(curline, 0, max_p);
	line->each_cmd[i].is_heredoc = true;
}




void	to_fill_struct(char *curline, t_all *all)
{
	t_line	*line;
	int temp_j;
	int	j;
	int	i;

	line = all->line;
	temp_j = 0;
	i = 0;
	printf("here \n");
	while (curline[temp_j] != '\0')
	{
		while (curline[temp_j] != '\0' && (curline[temp_j] == ' ' || curline[temp_j] == '\t'))
			temp_j++;
		j = temp_j;
		while (curline[temp_j] != '\0' && !ft_strchr("<>|$", curline[temp_j]))
			temp_j++;
		if (curline[temp_j + 1] == '\0')
		{
			// last part of line
			if (i - 1 > 0 && line->each_cmd[i - 1].cmd)
			{
				fill_cmd(&curline[j], line, ((temp_j - j) + 1), i);
			}
			if (i - 1 > 0 && line->each_cmd[i - 1].infile)
			{
				fill_infile(&curline[j], line, ((temp_j - j) + 1), i);
			}
			if (i - 1 > 0 && line->each_cmd[i - 1].outfile)
			{
				fill_outfile(&curline[j], line, ((temp_j - j) + 1), i);
			}
		}
		
		if (curline[temp_j] == '|')
		{
			fill_cmd(&curline[j], line, ((temp_j - j) + 1), i);
			temp_j++;
		}
		if (curline[temp_j] == '<')
		{
			if (curline[temp_j + 1] != '\0' && curline[temp_j + 1] == '<')
			{
				temp_j = temp_j + 1;
				fill_heredoc(&curline[j], line, ((temp_j - j) + 1), i);
			}
			else
				fill_infile(&curline[j], line, ((temp_j - j) + 1), i);
			temp_j = temp_j + 1;
		}
		if (curline[temp_j] == '>')
		{
			if (curline[temp_j + 1] != '\0' && curline[temp_j + 1] == '>')
			{	// if (curline[temp_j] == '$')
	// {
	// 	if(curline[temp_j + 1] == '?')
	// 		temp_j + 1;
				line->each_cmd[i].is_append = true;
				temp_j = temp_j + 1;
			}
			fill_outfile(&curline[j], line, ((temp_j - j) + 1), i);
			temp_j = temp_j + 1;
		}
		i++;
	}
	printf("end of fill_struct\n");
}













void	check_line(char *curline, t_all *all)
{
	t_line	*line;
	int temp_j;

	line = all->line;
	temp_j = 0;
	printf("here \n");
	while (curline[temp_j] != '\0')
	{
		while (curline[temp_j] != '\0' && (curline[temp_j] == ' ' || curline[temp_j] == '\t'))
		{
			temp_j++;
		}
		if (curline[temp_j] == '|')
		{
			line->invalid = skip_spaces((temp_j + 1), curline, line);
		}
		if (curline[temp_j] == '<')
		{
			if (curline[temp_j + 1] != '\0' && curline[temp_j + 1] == '<')
				temp_j = temp_j + 1;
			line->invalid = skip_spaces((temp_j + 1), curline, line);
		}
		if (curline[temp_j] == '>')
		{
			if (curline[temp_j + 1] != '\0' && curline[temp_j + 1] == '>')
				temp_j = temp_j + 1;
			line->invalid = skip_spaces((temp_j + 1), curline, line);
		}
		if (line->invalid)
		{
			printf("here %c\n", curline[temp_j]);
			exit(EXIT_FAILURE);
		}
		else
		{
			//printf("here %c\n", curline[temp_j]);
			temp_j++;
		}
	}
	printf("end of check_line\n");
}



void	initialize_each_cmd(t_all *all)
{
	int		i;

	i = 0;
	printf("all->line->total_cmd is %d\n", all->line->total_cmd);
	all->line->each_cmd = ft_calloc(all->line->total_cmd + 1, sizeof(t_cmd));
	// while (i < all->line->total_cmd)
	// {
	// 	printf("before initialize_t_all\n\n");
	// 	// all->line->each_cmd[i].cmd = ft_calloc(2, sizeof(char));
	// 	// all->line->each_cmd[i].infile = ft_calloc(2, sizeof(char));
	// 	// all->line->each_cmd[i].outfile = ft_calloc(2, sizeof(char));
	// 	i++;
	// }
	printf("after initialize_t_all\n\n");
}



int	main(int argc, char **argv, char **envp)
{
	//char	***my_array;
	char	*curline;
	int		amount_cmd;
	t_all	*all;
	char	*pwd;

	//line = NULL;
	//rl_initialize();
	// all = initialize_t_all(amount_cmd, curline);
	all = ft_calloc(1, sizeof(t_all));
	all->line = ft_calloc(1, sizeof(t_line));
	if (!all)
		return (NULL);
	curline = readline("Minishell >");
	// pwd = get_current_dir();
	// change_directory("35 3");
	while (curline)
	{
		if (ft_strlen(curline) > 1)
			add_history(curline);
		printf("line is (%s)\n", curline);
		// printf("line is (%c)\n", curline[4]);
		//my_array = initializing_3d(argc, &line, envp);
		
		check_line(curline, all);
		amount_cmd = count_cmd(curline, all);
		printf("totall cmd is %d\n", amount_cmd);
		initialize_each_cmd(all);
		to_fill_struct(curline, all);
		printf("%s\n", all->line->each_cmd[0].cmd[0]);
 		printf("%s\n", all->line->each_cmd[0].cmd[1]);
		printf("%s\n", all->line->each_cmd[1].cmd[0]);
		printf("%s\n", all->line->each_cmd[1].cmd[1]);
		printf("%s\n", all->line->each_cmd[2].cmd[0]);
		// printf("print element\n\n\n");
		// print_elements(all);
		// free(curline);
		// curline = readline("Minishell >");
		exit(0);
	}

	return (0);
}
