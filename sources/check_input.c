/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_input.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: adakheel <adakheel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/06/25 13:17:04 by adakheel      #+#    #+#                 */
/*   Updated: 2024/06/27 07:55:59 by adakheel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	join_line_after_quotes(char *curline, t_all *all)
{
	char	*previous_line;
	char	*line_joined;
	char	*input;
	int		i;

	i = 0;
	previous_line = dup_protect(all->line->curline, all);
	free(all->line->curline);
	all->line->curline = NULL;
	input = readline("> ");
	if (!input)
	{
		free(previous_line);
		all->last_exit_status = 2;
		write(2, "Minishell: syntax error: unexpected end of file\n", 49);
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
	if (!line_joined && errno == 12)
		memory_allocation_failed(all);
	all->line->curline = dup_protect(line_joined, all);
	free(line_joined);
}

int	check_quotes(char *curline, t_all *all)
{
	int		i;
	char	c;

	i = 0;
	c = 0;
	while (curline && curline[i] != '\0')
	{
		if (curline[i] == 34 || curline[i] == 39)
		{
			c = curline[i];
			i++;
			while (curline[i] != '\0' && curline[i] != c)
				i++;
			if (curline[i] == '\0')
				break ;
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
	int		i;

	cur = all->line->chunks;
	prev = NULL;
	while (cur)
	{
		i = 0;
		if (cur->str[0] == '|')
		{
			if (prev == NULL || (prev && !check_space(prev->str)))
				return (2);
			if (cur->next == NULL)
				return (1);
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
			if (cur->next && cur->next->str[0] == '<')
				return (2);
			if (cur->next && cur->next->str[0] == '>')
				return (2);
			if (cur->next && cur->next->str[0] == '|')
				return (2);
			if (cur->next == NULL || (cur->next && !check_space(cur->next->str)))
			{
				return (2);
			}
		}
		prev = cur;
		cur = cur->next;
	}
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

	str = sub_protect(curline, all, *pos, all->i - *pos);
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
		str = sub_protect(curline, all, pos, all->i - pos);
		if (ft_strlen(str) != 0)
			ft_lstadd_back_chunk(&line->chunks, ft_lstnewchunkfree(all, str));
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
		if (check_quotes(all->line->curline, all))
		{
			join_line_after_quotes(all->line->curline, all);
			add_history(all->line->curline);
		}
		else
		{
			split_all(all->line->curline, all);
			i = check_meta(all, all->line->curline);
			if (i == 1)
			{
				join_line_after_quotes(all->line->curline, all);
				add_history(all->line->curline);
			}
			else if (i == 2)
			{
				lstclear(&all->line->chunks);
				free(all->line->curline);
				create_print_error(all, "", 6);
				all->last_exit_status = 2;
				current_path = get_current_dir(all);
				prompt = ft_strjoin(current_path, "$ ");
				free(current_path);
				current_path = NULL;
				all->line->curline = readline(prompt);
				free(prompt);
				prompt = NULL;
				if (!all->line->curline)
				{
					all->last_exit_status = 2;
					kill_process(all);
				}
				add_history(all->line->curline);
			}
			else if (i == 0)
			{
				temp = ft_strdup(all->line->curline);
				free(all->line->curline);
				return (temp);
			}

		}
	}
}
