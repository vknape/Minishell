/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   remove_whitespace_quotes.c                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: adakheel <adakheel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/14 11:16:06 by adakheel      #+#    #+#                 */
/*   Updated: 2024/06/27 09:01:19 by adakheel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// char	*remove_whitespace_cmd(char *str)
// {
// 	int		index;
// 	int		i;
// 	char	*whole;
// 	int		j;
// 	char	c;
// 	int		start;
// 	char	*temp;

// 	index = 0;
// 	i = 0;
// 	j = 0;
// 	start = 0;
// 	whole = NULL;
// 	//dprintf(2, "str here = (%s)\n", str);
// 	while (str[i])
// 	{
// 		if (str[i] == 34 || str[i] == 39)
// 		{
// 			start = i;
// 			c = str[i];
// 			i++;
// 			while (str[i] && str[i] != c)
// 				i++;
// 			if (!whole)
// 				whole = ft_substr(str, start, i - start);
// 			else
// 			{
// 				temp = ft_substr(str, start, i - start);
// 				whole = ft_strjoin_free(whole, temp);
// 				free(temp);
// 			}
// 			if (str[i])
// 				i++;
// 			if (!str[i])
// 				break;
// 		}
// 		if (str[i] && is_white_space(str[i]))
// 			i++;
// 		start = i;
// 		while (str[i] && !is_white_space(str[i]) && str[i] != 34 && str[i] != 39)
// 		{
// 			i++;
// 		}
// 		if (start < i)
// 		{
// 			if (!whole)
// 				whole = ft_substr(str, start, i - start);
// 			else
// 			{
// 				temp = ft_substr(str, start, i - start);
// 				whole = ft_strjoin_free(whole, temp);
// 				free(temp);
// 			}
// 		}
// 	}
// 	free(str);
// 	//dprintf(2, "str here = (%s)\n", whole);
// 	return (whole);
// }


// char	*remove_whitespace_cmd(char *str)
// {
// 	int		index;
// 	int		i;
// 	char	*des;
// 	int		j;
// 	char	c;
// 	int		start;
// 	char	*temp;

// 	index = 0;
// 	i = 0;
// 	j = 0;
// 	start = 0;
// 	des = NULL;
// 	dprintf(2, "str here = (%s)\n", str);
// 	while (str[i])
// 	{
// 		if (str[i] == 34 || str[i] == 39)
// 		{
// 			c = str[i];
// 			i++;
// 			while (str[i] && str[i] != c)
// 				i++;
// 			if (str[i])
// 				i++;
// 			if (!str[i])
// 				break;
// 		}
// 		if (str[i] && is_white_space(str[i]) && i > start)
// 		{
// 			temp = ft_substr(str, start, i - start);
// 			if (!des)
// 				des = ft_strdup(temp);
// 			else
// 				des = ft_strjoin_free(des, temp);
// 			free(temp);
// 			while (str[i] && is_white_space(str[i]))
// 				i++;
// 			if (!str[i])
// 			{
// 				free(str);
// 				dprintf(2, "str here end = (%s)\n", des);
// 				return (des);
// 			}
// 			start = i;
// 		}	
// 		i++;
// 	}
// 	temp = ft_substr(str, start, i - start);
// 	if (!des)
// 		des = ft_strdup(temp);
// 	else
// 		des = ft_strjoin_free(des, temp);
// 	free(temp);
// 	free(str);
// 	dprintf(2, "str here end = (%s)\n", des);
// 	return (des);
// 	// str = ft_strdup(des);
// 	// printf("str here = (%s)\n", str);
// 	// free(des);
// }

void	remove_whitespace_cmd_handle_quote(char *str, int *i, char **des, int *j)
{
	int	c;

	c = str[*i];
	(*des)[*j] = str[*i];
	(*i)++;
	(*j)++;
	while (str[*i] && str[*i] != c)
	{
		(*des)[*j] = str[*i];
		(*i)++;
		(*j)++;
	}
	(*des)[*j] = str[*i];
	(*i)++;
	(*j)++;
}

char	*remove_whitespace_cmd(char *str)
{
	int		i;
	char	*des;
	int		j;

	i = 0;
	j = 0;
	des = malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!des)
		return (NULL);
	while (str[i])
	{
		if (str[i] == 34 || str[i] == 39)
			remove_whitespace_cmd_handle_quote(str, &i, &des, &j);
		if (!str[i])
			break ;
		if (!is_white_space(str[i]))
		{
			des[j] = str[i];
			j++;
		}
		i++;
	}
	des[j] = '\0';
	free(str);
	str = ft_strdup(des);
	free(des);
	return (str);
}

// void	remove_whitespace_cmd(t_all *all, char **cmd_array)
// {
// 	int		index;
// 	char	*des;
// 	char	*src;

// 	index = 0;
// 	while (cmd_array[index])
// 	{
// 		src = cmd_array[index];
// 		des = cmd_array[index];
// 		while (*src)
// 		{
// 			if (!is_white_space(*src))
// 				*des++ = *src;
// 			src++;
// 		}
// 		*des = '\0';
// 		index++;
// 	}
// }

char	*remove_quotes_exp(char *str)
{
	char	*des;
	int		i;

	if (str && (str[0] == 34 || str[0] == 39))
	{
		i = ft_strlen(str);
		des = ft_substr(str, 1, i - 2);
		free(str);
		return (des);
	}
	else
	{
		des = ft_strdup(str);
		free(str);
		return (des);
	}
}

char	*reduce_whitespace_between_words2(char *str, char *des, int i, int j)
{
	int	count;

	while (str[i])
	{
		if (!str[i])
			break ;
		if (!is_white_space(str[i]))
			des[j++] = str[i++];
		else
		{
			count = 0;
			while (str[i] && is_white_space(str[i]))
			{
				count++;
				i++;
			}
			if (count > 0)
			{
				des[j] = ' ';
				j++;
			}
		}
	}
	des[j] = '\0';
	return (des);
}

char	*reduce_whitespace_between_words(char *str)
{
	char	*des;
	char	*temp;
	int		i;
	int		j;

	i = 0;
	j = 0;
	temp = malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!temp)
		return (NULL);
	des = reduce_whitespace_between_words2(str, temp, i, j);
	free(str);
	str = ft_strdup(des);
	free(des);
	if (!str)
		return (NULL);
	return (str);
}

char	*remove_whitespace_at_begin_end(char *str)
{
	int		i;
	int		j;
	char	*des;
	char	*end;

	i = 0;
	while (str && str[i] && is_white_space(str[i]))
		i++;
	des = ft_substr(str, i, ft_strlen(str));
	free(str);
	if (!des)
		return (NULL);
	if (!des[0])
		return (des);
	j = ft_strlen(des) - 1;
	while (des[j] && is_white_space(des[j]))
		j--;
	end = ft_substr(des, 0, j + 1);
	free(des);
	if (!end)
		return (NULL);
	end = reduce_whitespace_between_words(end);
	return (end);
}

char	*remove_quotes_cmd2(char *str, char *temp, int i, int j)
{
	int	c;

	while (str[i])
	{
		c = -1;
		if (str[i] == 34 || str[i] == 39)
		{
			c = str[i];
			i++;
			while (str[i] && str[i] != c)
				temp[j++] = str[i++];
			if (!str[i])
				break ;
			i++;
		}
		else
			temp[j++] = str[i++];
	}
	temp[j] = '\0';
	return (temp);
}

char	*remove_quotes_cmd(char *str, int option)
{
	char	*temp;
	int		i;
	int		j;

	i = 0;
	j = 0;
	temp = malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!temp)
		return (NULL);
	temp = remove_quotes_cmd2(str, temp, i, j);
	free(str);
	str = ft_strdup(temp);
	free(temp);
	if (!str)
		return (NULL);
	if (option)
		str = remove_whitespace_at_begin_end(str);
	return (str);
}

// char	*remove_quotes_cmd(char *str)
// {
// 	char	*chunk;
// 	char	*whole;
// 	int		i;
// 	int		start;
// 	int		c;

// 	// dprintf(2, "str in is (%s)\n", str);
// 	i = 0;
// 	start = 0;
// 	whole = NULL;
// 	while (str[i])
// 	{
// 		c = -1;
// 		if (str[i] == 34 || str[i] == 39)
// 		{
// 			c = str[i];
// 			if (!whole && i > start)
// 				whole = ft_substr(str, 0, i);
// 			else if (i > start)
// 			{
// 				chunk = ft_substr(str, start, i - start);
// 				whole = ft_strjoin_free(whole, chunk);
// 				free(chunk);
// 			}
// 			// dprintf(2, "str without quotes (%s)\n", whole);
// 			i++;
// 			start = i;
// 			while (str[i] && str[i] != c)
// 				i++;
// 			chunk = ft_substr(str, start, i - start);
// 			// dprintf(2, "chunk without quotes (%s)\n", chunk);
// 			if (!whole)
// 				whole = ft_strdup(chunk);
// 			else
// 				whole = ft_strjoin_free(whole, chunk);
// 			// dprintf(2, "str without quotes (%s)\n", whole);
// 			free(chunk);
// 			start = i + 1;
// 			if (!str[i])
// 				break;

// 		}
// 		i++;
// 		// dprintf(2, "str without quotes (%s)\n", whole);
// 	}
// 	// dprintf(2, "str without quotes (%s)\n", whole);
// 	if (!whole)
// 		whole = ft_strdup(str);
// 	else if (i > start)
// 	{
// 		chunk = ft_substr(str, start, i - start);
// 		whole = ft_strjoin_free(whole, chunk);
// 		free(chunk);
// 	}
// 	free(str);
// 	// dprintf(2, "str without quotes (%s)\n", whole);
// 	whole = remove_whitespace_at_begin_end(whole);
// 	// dprintf(2, "str after space (%s)\n", whole);
// 	return (whole);
// }

// void	remove_whitespace_nodes(t_all *all, t_chunk *nodes)
// {
// 	t_chunk	*temp;
// 	char	*src;
// 	char	*des;

// 	temp = nodes;
// 	while (temp)
// 	{
// 		src = temp->str;
// 		des = temp->str;
// 		while (*src)
// 		{
// 			if (!is_white_space(*src))
// 				*des++ = *src;
// 			src++;
// 		}
// 		*des = '\0';
// 		temp = temp->next;
// 	}
// }

// void	remove_quotes_nodes(t_all *all, t_chunk *nodes)
// {


// }

void	split_to_list(t_all *all, char *str)
{
	int		pos;
	int		start;
	char	*newstr;

	pos = 0;
	start = 0;
	while (str[pos])
	{
		while (str[pos] && is_white_space(str[pos]))
			pos++;
		while (str[pos] && !is_white_space(str[pos]))
			pos++;
		newstr = ft_substr(str, start, pos);
		if (!newstr)
			memory_allocation_failed(all);
		ft_lstadd_back_chunk(&all->line->tempchunk, ft_lstnewchunkfree(all, newstr));
		if (!str[pos])
			break ;
		start = pos + 1;
		pos++;
	}
}

void	merge_split(t_all *all, t_cmd *cmd)
{
	t_chunk	*temp;
	int		i;

	i = 0;
	if (!ft_strncmp("export", cmd->cmd[i], 7))
		return ;
	while (cmd->cmd[i])
		split_to_list(all, cmd->cmd[i++]);
	i = ft_lstsizechunk(all->line->tempchunk);
	free2d(cmd->cmd);
	cmd->cmd = ft_calloc(sizeof(char *), i + 1);
	if (!cmd->cmd)
		memory_allocation_failed(all);
	temp = all->line->tempchunk;
	i = 0;
	while (temp)
	{
		cmd->cmd[i] = ft_strdup(temp->str);
		temp = temp->next;
		i++;
	}
	free_chunk(&(*all).line->tempchunk);
}


void	remove_whitespace_quotes(t_all *all, t_cmd *cmd)
{
	t_cmd	*temp;
	t_chunk	*node;
	int		i;

	temp = cmd;
	i = 0;
	while (temp)
	{
		i = 0;
		while (temp->cmd && temp->cmd[i])
		{
			temp->cmd[i] = remove_whitespace_cmd(temp->cmd[i]);
			temp->cmd[i] = search_dollar_signe(all, temp->cmd[i]);
			temp->cmd[i] = remove_quotes_cmd(temp->cmd[i], 0);
			i++;
		}
		if (temp->cmd && temp->cmd[0])
		{
			merge_split(all, temp);
			if (check_space(temp->cmd[0]))
				temp->cmd[0] = remove_whitespace_at_begin_end(temp->cmd[0]);
		}
		node = temp->delimiter;
		while (node)
		{
			node->str = remove_whitespace_cmd(node->str);
			node->str = search_dollar_signe(all, node->str);
			node->str = remove_quotes_cmd(node->str, 1);
			node = node->next;
		}
		node = temp->infile;
		while (node)
		{
			node->str = remove_whitespace_cmd(node->str);
			node->str = search_dollar_signe(all, node->str);
			node->str = remove_quotes_cmd(node->str, 1);
			node = node->next;
		}
		node = temp->outfile;
		while (node)
		{
			node->str = remove_whitespace_cmd(node->str);
			node->str = search_dollar_signe(all, node->str);
			node->str = remove_quotes_cmd(node->str, 1);
			node = node->next;
		}
		temp = temp->next;
	}
}
