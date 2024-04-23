
#include "minishell.h"





// int	count_cmd(char *curline, t_all *all)
// {
// 	int	i;
// 	int	j;

// 	i = 0;
// 	j = 1;
// 	while (curline[i] != '\0')
// 	{
// 		if (ft_strchr("|<>$", curline[i]))
// 		{
// 			while (curline[i] != '\0' && ft_strchr("|<>$", curline[i]))
// 				i++;
// 			j++;
// 		}
// 		i++;
// 	}
// 	all->line->total_cmd = j;
// 	return (j);

// }



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




// void	to_fill_struct(char *curline, t_all *all)
// {
// 	t_line	*line;
// 	int temp_j;*each_cmd;
// 	int	j;
// 	int	i;

// 	line = all->line;
// 	temp_j = 0;
// 	i = 0;
// 	printf("here \n");
// 	while (curline[temp_j] != '\0')
// 	{
// 		while (curline[temp_j] != '\0' && (curline[temp_j] == ' ' || curline[temp_j] == '\t'))
// 			temp_j++;
// 		j = temp_j;
// 		while (curline[temp_j] != '\0' && !ft_strchr("<>|$", curline[temp_j]))
// 			temp_j++;
// 		if (curline[temp_j + 1] == '\0')
// 		{
// 			// last part of line
// 			if (i - 1 > 0 && line->each_cmd[i - 1].cmd)
// 			{
// 				fill_cmd(&curline[j], line, ((temp_j - j) + 1), i);
// 			}
// 			if (i - 1 > 0 && line->each_cmd[i - 1].infile)
// 			{
// 				fill_infile(&curline[j], line, ((temp_j - j) + 1), i);
// 			}
// 			if (i - 1 > 0 && line->each_cmd[i - 1].outfile)
// 			{
// 				fill_outfile(&curline[j], line, ((temp_j - j) + 1), i);
// 			}
// 		}
		
// 		if (curline[temp_j] == '|')
// 		{
// 			fill_cmd(&curline[j], line, ((temp_j - j) + 1), i);
// 			temp_j++;
// 		}
// 		if (curline[temp_j] == '<')
// 		{
// 			if (curline[temp_j + 1] != '\0' && curline[temp_j + 1] == '<')
// 			{
// 				temp_j = temp_j + 1;
// 				fill_heredoc(&curline[j], line, ((temp_j - j) + 1), i);
// 			}
// 			else
// 				fill_infile(&curline[j], line, ((temp_j - j) + 1), i);
// 			temp_j = temp_j + 1;
// 		}
// 		if (curline[temp_j] == '>')
// 		{
// 			if (curline[temp_j + 1] != '\0' && curline[temp_j + 1] == '>')
// 			{	// if (curline[temp_j] == '$')
// 	// {
// 	// 	if(curline[temp_j + 1] == '?')
// 	// 		temp_j + 1;
// 				line->each_cmd[i].is_append = true;
// 				temp_j = temp_j + 1;
// 			}
// 			fill_outfile(&curline[j], line, ((temp_j - j) + 1), i);
// 			temp_j = temp_j + 1;
// 		}*each_cmd;;
// 	}
// 	printf("end of fill_struct\n");
// }










int check_quotes(char *curline, t_all *all)
{
	int i;
	char c;
	
	i = 0;
	c = 0;
	while(curline[i] != '\0')
	{
		if (curline[i] == 34 || curline[i] == 39)
		{
			c = curline[i];
			i++;
			if (curline[i] == '\0')
				break ;
			while (curline[i] != '\0' && curline[i] != c)
				i++;
			if (curline[i] == '\0' && curline[i - 1] == c)
			{
				c = 0;
				break ;
			}
			else if (curline[i] == c)
				c = 0;
		}
		i++;
	}
	if (c != 0)
		return (1);
	else
		return (0);
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
		while (curline[temp_j] != '\0' && (curline[temp_j] == ' ' || curline[temp_j] == '\t' || curline[temp_j] == '\n'))
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
	// 	// all->line->each_cmd[i].cmd = ft_calloc(2, sizeof(chwhile (check_quotes(curline, all) != 0)
		//check_line(curline, all);ar));
	// 	// all->line->each_cmd[i].infile = ft_calloc(2, sizeof(char));
	// 	// all->line->each_cmd[i].outfile = ft_calloc(2, sizeof(char));
	// 	i++;
	// }
	printf("after initialize_t_all\n\n");
}

int	count_cmd(char *curline, t_all *all)
{
	int i;
	int	j;
	char c;

	i = 0;
	j = 1;
	if (curline[i] == '\0')
		return (0);
	while (curline[i] != '\0')
	{
		if (curline[i] == 34 || curline[i] == 39)
		{
			c = curline[i];
			i++;
			while (curline[i] != c)
			{
				i++;
			}
		}
		if (curline[i] == '|')
			j++;
		i++;
	}
	all->line->total_cmd = j;
	return (j);
}

t_cmd	*ft_lstnewcmd(char *templine)
{
	t_cmd	*lst1;

	lst1 = (t_cmd *) malloc(sizeof(t_cmd));
	if (lst1 == NULL)
		return (NULL);
	(*lst1).next = NULL;
	lst1->templine = templine;
	return (lst1);
}
t_cmd	*ft_lstlast_cmd(t_cmd *lst)
{
	if (lst == NULL)
		return (lst);
	while ((*lst).next != NULL)
		lst = (*lst).next;
	return (lst);
}

void	ft_lstadd_back_cmd(t_cmd **lst, t_cmd *new)
{
	t_cmd	*ptr;

	if (!*lst)
	{
		*lst = new;
		return ;
	}
	ptr = ft_lstlast_cmd(*lst);
	if (new)
		(*ptr).next = new;
}

t_chunk	*ft_lstnewchunk(char *str)
{
	t_chunk	*lst1;

	lst1 = (t_chunk *) malloc(sizeof(t_chunk));
	if (lst1 == NULL)
		return (NULL);
	(*lst1).next = NULL;
	lst1->str = str;
	return (lst1);
}
t_chunk	*ft_lstlast_chunk(t_chunk *lst)
{
	if (lst == NULL)
		return (lst);
	while ((*lst).next != NULL)
		lst = (*lst).next;
	return (lst);
}

void	ft_lstadd_back_chunk(t_chunk **lst, t_chunk *new)
{
	t_chunk	*ptr;

	if (!*lst)
	{
		*lst = new;
		return ;
	}
	ptr = ft_lstlast_chunk(*lst);
	if (new)
		(*ptr).next = new;
}

void	split_cmds(char *curline, t_all *all)
{
	t_line	*line;
	int		i;
	int		pos;
	char	c;
	char	*str;

	line = all->line;
	pos = 0;
	i = 0;
	while (curline[i] != '\0')
	{
		if (curline[i] == 34 || curline[i] == 39)
		{
			c = curline[i];
			i++;
			while (curline[i] != c)
				i++;
		}
		if (curline[i] == '|' || curline[i + 1] == '\0')
		{
			//printf("%d\n%d\n%d\n", i, pos, ft_strlen(curline));
			if (curline[i + 1] == '\0')
				str = ft_substr(curline, pos, i - pos + 1);
			else
				str = ft_substr(curline, pos, i - pos);
			pos = i + 1;
			//printf("%s\n", str);
			//split_inside_cmds_piletjes(str, all);
			ft_lstadd_back_cmd(&line->each_cmd, ft_lstnewcmd(str));
		}
		i++;
	}
	// printf("%s\n", line->each_cmd->templine);
	// printf("%s\n", line->each_cmd->next->templine);
}

void	find_match_quote(char *curline, int *i)
{
	char	c;

	c = curline[*i];
	++*i;
	while (curline[*i] != c)
		++*i;
}

void	split_all_substring(char *curline, t_line *line, int *pos, int *i)
{
	char	*str;

	str = ft_substr(curline, *pos, *i - *pos);
	*pos = *i;
	if (ft_strlen(str) != 0)
		ft_lstadd_back_chunk(&line->chunks, ft_lstnewchunk(str));
	if ((curline[*i] == '<' && curline[*i + 1] == '<') || (curline \
		[*i] == '>' && curline[*i + 1] == '>'))
		++*i;
	if (curline[*i] != '\0')
	{
		str = ft_substr(curline, *pos, *i - *pos + 1);
		*pos = *i + 1;
		ft_lstadd_back_chunk(&line->chunks, ft_lstnewchunk(str));
	}
}


void	split_all(char *curline, t_all *all)
{
	t_line	*line;
	int		i;
	int		pos;
	char	*str;

	line = all->line;
	pos = 0;
	i = 0;
	while (curline[i] != '\0')
	{
		if (curline[i] == 34 || curline[i] == 39)
			find_match_quote(curline, &i);
		if (curline[i] == '|' || curline[i] == '<' || curline[i] == '>')
			split_all_substring(curline, line, &pos, &i);
		i++;
	}
	if (pos < i)
	{
		str = ft_substr(curline, pos, i - pos);
		if (ft_strlen(str) != 0)
			ft_lstadd_back_chunk(&line->chunks, ft_lstnewchunk(str));
	}
}






// void	spite_each_block(t_all *all)
// {
// 	int		i;
// 	t_line	*line;
// 	char	*block;

// 	line = all->line;
// 	i = 0;
// 	while (line->each_cmd. != NULL)
// 	{
// 		block = line->each_cmd[i];
// 	}
	
// }

// void	split_inside_cmds_piletjes(char *str, t_all *all)
// {
// 	t_line	*line;
// 	int		i;
// 	int		pos;
// 	char	c;
// 	char	*sub_str;

// 	line = all->line;
// 	pos = 0;
// 	i = 0;
// 	int	start;
// 	while (str[i] != '\0')
// 	{
// 		start = i;
// 		if (ft_strchr("<>", str[i]))
// 		{
// 			while (ft_strchr("<>", str[i]))
// 			{
// 				i++;
// 			}
// 			while (!ft_strchr("<>", str[i]) || str[i + 1] == '\0')
// 			{
// 				i++;
// 			}
// 			while (line->each_cmd->next != NULL)
// 			{
// 				line->each_cmd->next = line->each_cmd->next->next;
// 			}
			
// 			if (str[start] == '<' && str[start + 1] == '<')
// 				line->each_cmd->next->delimiter = ft_substr(&str[start], start, i - start);
// 			if (str[start] == '<')
// 				line->each_cmd->next->infile = ft_substr(&str[start], start, i - start);
// 			if (str[start] == '>' && str[start + 1] == '>')
// 			{
// 				line->each_cmd->next->outfile = ft_substr(&str[start], start, i - start);
// 				line->each_cmd->next->is_append = true;
// 			}
// 			if (str[start] == '>')
// 				line->each_cmd->next->outfile = ft_substr(&str[start], start, i - start);
// 		}
// 		else
// 		{
// 			start = i;
// 			while (!ft_strchr("<>", str[i]) && str[i + 1] != '\0')
// 			{
// 				i++;
// 			}
// 			while (line->each_cmd->next != NULL)
// 			{
// 				line->each_cmd->next = line->each_cmd->next->next;
// 			}
// 			line->each_cmd->next->cmd = ft_substr(&str[start], start, i - start);
// 		}
// }


void	init_each_command(t_all *all)
{
	t_line *line;
	int i;

	line = all->line;
	line->each_cmd = ft_calloc(line->total_cmd + 1, sizeof(t_cmd));
	if (!line->each_cmd)
		exit(1);
}

// void	to_fill_struct(int pos, t_all *all)
// {
// 	t_line	*line;
// 	int temp_j;
// 	int	j;
// 	int	i;
free(previous_line);
	line_joined = ft_strjoin(with_newline, input);
// 	while (curline[temp_j] != '\0')
// 	{
// 		while (curline[temp_j] != '\0' && (curline[temp_j] == ' ' || curline[temp_j] == '\t'))
// 			temp_j++;while (check_quotes(curline, all) != 0)
	// 	join_line_after_quotes(&curline);
	// printf("curline after while is %s\n", curline);
	// add_history(curline);
	// printf("line is (%s)\n", curline);
		//check_line(curline, all);
// 			{
// 				fill_cmd(&curline[j], line, ((temp_j - j) + 1), i);
// 			}
// 			if (i - 1 > 0 && line->each_cmd[i - 1].infile)
// 			{
// 				fill_infile(&curline[j], line, ((temp_j - j) + 1), i);
// 			}
// 			if (i - 1 > 0 && line->each_cmd[i - 1].outfile)
// 			{
// 				fill_outfile(&curline[j], line, ((temp_j - j) + 1), i);
// 			}
// 		}
		
// 		if (curline[temp_j] == '|')
// 		{
// 			fill_cmd(&curline[j], line, ((temp_j - j) + 1), i);
// 			temp_j++;
// 		}
// 		if (curline[temp_j] == '<')
// 		{
// 			if (curline[temp_j + 1] != '\0' && curline[temp_j + 1] == '<')
// 			{
// 				temp_j = temp_j + 1;
// 				fill_heredoc(&curline[j], line, ((temp_j - j) + 1), i);
// 			}
// 			else
// 				fill_infile(&curline[j], line, ((temp_j - j) + 1), i);
// 			temp_j = temp_j + 1;
// 		}
// 		if (curline[temp_j] == '>')
// 		{
// 			if (curline[temp_j + 1] != '\0' && curline[temp_j + 1] == '>')
// 			{	// if (curline[temp_j] == '$')
// 	// {
// 	// 	if(curline[temp_j + 1] == '?')
// 	// 		temp_j + 1;
// 				line->each_cmd[i].is_append = true;
// 				temp_j = temp_j + 1;
// 			}
// 			fill_outfile(&curline[j], line, ((temp_j - j) + 1), i);
// 			temp_j = temp_j + 1;
// 		}
// 		i++;
// 	}
// 	printf("end of fill_struct\n");
// }

// static int	words_counter(char const *s, char c)
// {
// 	int	count;
// 	char q;

// 	count = 0;
// 	while (*s)
// 	{
// 		while (*s == c)
// 			s++;
// 		if (*s == 34 || *s == 39)
// 		{
// 			q = *s;
// 			s++;
// 			while(*s != q)
// 				s++;
// 			// count++;
// 		}
// 		if (*s)
// 			count++;
// 		while ((*s != c) && (*s))
// 			s++;
// 	}
// 	return (count);
// }

void	join_line_after_quotes(char **curline)
{
	char	*previous_line;
	char	*line_joined;
	char	*input;
	char	*with_newline;

	previous_line = ft_strdup(*curline);
	free(*curline);
	*curline = NULL;
	input = readline("quotes> ");
	with_newline = ft_strjoin(previous_line, "\n");
	free(previous_line);
	line_joined = ft_strjoin(with_newline, input);
	free(input);
	free(with_newline);
	*curline = ft_strdup(line_joined);
	free(line_joined);
	printf("curline is %s\n", *curline);
}

int	main(int argc, char **argv, char **envp)
{
	char	*curline;
	int		amount_cmd;
	t_all	*all;
	char	*pwd;
	int		i = 0;

	//line = NULL;
	//rl_initialize();
	// all = initialize_t_all(amount_cmd, curline);
	all = ft_calloc(1, sizeof(t_all));
	all->line = ft_calloc(1, sizeof(t_line));
	if (!all)
		return (1);
	curline = readline("Minishell> ");
	// pwd = get_current_dir();
	// change_directory("35 3");
	while (check_quotes(curline, all) != 0)
		join_line_after_quotes(&curline);
	// printf("curline after while is %s\n", curline);
	add_history(curline);
	// printf("line is (%s)\n", curline);
		//check_line(curline, all);
	// count_cmd(curline, all);
	// init_each_command(all);
	// split_cmds(curline, all);
	// printf("%s\n", all->line->chunks);
	split_all(curline, all);
	// printf("test here %s\n", all->line->each_cmd->templine);
	// printf("test %s\n", all->line->chunks->str);
	t_chunk *chunks = all->line->chunks;
	while (chunks != NULL)
	{
		printf("test %s\n", chunks->str);
		chunks = chunks->next;
	}
	while(1)
	{
		curline = readline("Minishell> ");
	}
	
	// 	// printf("line is (%c)\n", curline[4]);
	// 	//my_array = initializing_3d(argc, &line, envp);
	// 	char **str = ft_split_quotes(curline, ' ');
	// 	int i = 0;
	// 	while (str[i])
	// 	{
	// 		printf("%s\n", str[i]);
	// 		i++;
	// 	}
	// 	// printf("%s\n", str[4]);
	// 	printf("%d\n", words_counter(curline, ' '));
	// 	// check_quotes(curline, all);
	
	// 	// amount_cmd = count_cmd(curline, all);
	// 	// printf("totall cmd is %d\n", amount_cmd);
	// 	// init_each_command(all);
	// 	// // initialize_each_cmd(all);
	// 	// to_fill_struct(curline, all);
	// 	// printf("%s\n", all->line->each_cmd[0].cmd[0]);
 	// 	// printf("%s\n", all->line->each_cmd[0].cmd[1]);
	// 	// printf("%s\n", all->line->each_cmd[1].cmd[0]);
	// 	// printf("%s\n", all->line->each_cmd[1].cmd[1]);
	// 	// printf("%s\n", all->line->each_cmd[2].cmd[0]);
	// 	// printf("print element\n\n\n");
	// 	// print_elements(all);
	// 	// free(curline);
	// 	// curline = readline("Minishell >");
	// 	exit(0);
	// }
	free(all->line->chunks->str);
	free(all->line->chunks->next->str);
	free(all->line->chunks->next);
	free(all->line->chunks);
	free(all->line);
	free(all);
	free(curline);

	return (0);
}
