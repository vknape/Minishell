
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
	if (!input)
	{
		all->last_exit_status = 2;
		kill_process(all);
	}
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
		// dprintf(2, "cur = (%s)\n", cur->str);
		// if (cur->next)
		// 	dprintf(2, "cur = (%s)\n\n", cur->next->str);
		// dprintf(2, "cur = (%s)\n\n", cur->next->next->str);
		i = 0;
		if (cur->str[0] == '|')
		{
			if (prev == NULL || (prev && !check_space(prev->str)))
				return (2);
			if (cur->next == NULL)
				return (1);
			// dprintf(2, "cur->next = (%s)\n\n", cur->next->str);
			while (cur->next->str[i] && is_white_space(cur->next->str[i]))
				i++;
			if (!cur->next->str[i] || cur->next->str[i] == '|' || cur->next->str[i] == '<' || cur->next->str[i] == '>')
				return (2);
			if (cur->next->str[i])
				return (0);
			else
				return (1);

		}
		if (cur->str[0] == '<' || cur->str[0] == '>')
		{
			// dprintf(2, "this here\n\n");
			// if (cur->next)
				// dprintf(2, "cur = (%s)dprintf(2, "cur = (%s)\n\n", cur->next->str);\n\n", cur->next->str);
			if (cur->next && cur->next->str[0] == '<')
				return (2);
			if (cur->next && cur->next->str[0] == '>')
				return (2);
			if (cur->next && cur->next->str[0] == '|')
				return (2);
			if (cur->next == NULL || (cur->next && !check_space(cur->next->str)))
			{
				// dprintf(2, "here\n");
				return (2);
			}
		}
		prev = cur;
		cur = cur->next;
	}
	// all->line->saved_line = ft_strdup(curline);
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

void	split_all_substring(t_all *all, char *curline, t_line *line, int *pos)
{
	char	*str;

	// dprintf(2, "curline is (%s)\n", curline);
	str = ft_substr(curline, *pos, all->i - *pos);
	// dprintf(2, "substr is (%s)\n", str);
	*pos = all->i;
	if (ft_strlen(str) != 0)
		ft_lstadd_back_chunk(&line->chunks, ft_lstnewchunk(all, str));
	else
		free(str);
	if ((curline[all->i] == '<' && curline[all->i + 1] == '<') || (curline \
		[all->i] == '>' && curline[all->i + 1] == '>'))
		++all->i;
	if (curline[all->i] != '\0')
	{
		str = ft_substr(curline, *pos, all->i - *pos + 1);
		*pos = all->i + 1;
		ft_lstadd_back_chunk(&line->chunks, ft_lstnewchunk(all, str));
	}
}

void	split_all(char *curline, t_all *all)
{
	t_line	*line;
	int		pos;
	char	*str;

	line = all->line;
	pos = 0;
	all->i = 0;
	if (line->chunks)
		lstclear(&line->chunks);
	while (curline[all->i] != '\0')
	{
		if (curline[all->i] == 34 || curline[all->i] == 39)
			find_match_quote(curline, &all->i);
		if (curline[all->i] == '|' || curline[all->i] == '<'\
			|| curline[all->i] == '>')
			split_all_substring(all, curline, line, &pos);
		all->i++;
	}
	if (pos < all->i)
	{
		str = ft_substr(curline, pos, all->i - pos);
		if (ft_strlen(str) != 0)
			ft_lstadd_back_chunk(&line->chunks, ft_lstnewchunk(all, str));
	}
}

char	*check_input(char *curline, t_all *all)
{
	int		i;
	char	*temp;
	char	*prompt;
	char	*current_path;

	while (1)
	{
		if (check_quotes(curline, all))
		{
			curline = join_line_after_quotes(curline, all);
			add_history(curline);
		}
		else
		{
			split_all(curline, all);
			i = check_meta(all, curline);
			if (i == 1)
			{
				curline = join_line_after_quotes(curline, all);
				add_history(curline);
			}
			else if (i == 2)
			{
				lstclear(&all->line->chunks);
				free(curline);
				create_print_error(all, "", 6);
				//dprintf(2, "parse error near \n");
				all->last_exit_status = 2;
				current_path = get_current_dir(all);
				prompt = ft_strjoin(current_path, "$ ");
				free(current_path);
				current_path = NULL;
				curline = readline(prompt);
				free(prompt);
				prompt = NULL;
				if (!curline)
				{
					//dprintf(2, "exit\n");
					all->last_exit_status = 2;
					kill_process(all);
					// free_all(&all);
					// exit(0);
				}
				add_history(curline);
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
