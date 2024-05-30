
#include "minishell.h"

char	*join_line_after_quotes(char *curline, t_all *all)
{
	char	*previous_line;
	char	*line_joined;
	char	*input;
	int		i;

	i = 0;
	previous_line = ft_strdup(curline);
	free(curline);
	curline = NULL;
	input = readline("> ");
	while (previous_line[i])
	{
		if (previous_line[i] == 10)
			previous_line[i] = 32;
		i++;
	}
	i = 0;
	while (input[i])
	{
		if (input[i] == 10)
			input[i] = 32;
		i++;
	}
	// i = ft_strlen(previous_line);
	// if (previous_line[i - 1] == ' ' && input)
	line_joined = ft_strjoin_free(previous_line, input);
	free(input);
	curline = ft_strdup(line_joined);
	free(line_joined);
	return (curline);
}

int	check_quotes(char *curline, t_all *all)
{
	int		i;
	char	c;

	i = 0;
	c = 0;
	while (curline[i] != '\0')
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
	return (0);
}

int	check_space(char *str)
{
	int	i;

	i = 0;
	while (str[i] && (str[i] == ' ' || str[i] == '\t' || str[i] == '\n'))
		i++;
	if (str[i] == '\0')
		return (0);
	else
		return (str[i]);
}

int	check_meta(t_all *all, char *curline)
{
	t_chunk	*prev;
	t_chunk	*cur;
	int i;

	cur = all->line->chunks;
	prev = NULL;

	//t_chunk *test_chunks = all->line->chunks;
	// while (test_chunks != NULL)
	// {
	// 	printf("test (%s)\n", test_chunks->str);
	// 	test_chunks = test_chunks->next;
	// }
	// printf("after print nodes\n");
	while (cur)
	{
		i = 0;
		if (cur->str[0] == '|')
		{
			if (prev == NULL || (prev && !check_space(prev->str)))
				return (2);
			if (cur->next == NULL)
				return (1);
			if (cur->next->str[0] == '|')
				return (2);
			while (cur->next->str[i] && is_white_space(cur->next->str[i]))
				i++;
			if (cur->next->str[i])
				return (0);
			else
				return (1);

		}
		if (cur->str[0] == '<' || cur->str[0] == '>')
		{
			// printf("here\n\n");
			if (cur->next && cur->next->str[0] == '<')
				return (2);
			if (cur->next && cur->next->str[0] == '>')
				return (2);
			if (cur->next == NULL || (cur->next && !check_space(cur->next->str)))
				return (2);
		}
		prev = cur;
		cur = cur->next;
	}
	all->line->saved_line = ft_strdup(curline);
	// printf("curline = %s\n", curline);
	return (0);
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
	if (line->chunks)
		lstclear(&line->chunks);
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

char	*check_input(char *curline, t_all *all)
{
	int	i;
	char	*temp;

	while (1)
	{
		if (check_quotes(curline, all))
			curline = join_line_after_quotes(curline, all);
		else
		{
			split_all(curline, all);
			i = check_meta(all, curline);
			if (i == 1)
				curline = join_line_after_quotes(curline, all);
			else if (i == 2)
			{
				lstclear(&all->line->chunks);
				free(curline);
				printf("parse error near \n");
				curline = readline("current working directory$");
			}
			else if (i == 0)
			{
				temp = ft_strdup(curline);
				free(curline);
				return (temp);
			}

		}
	}
}
