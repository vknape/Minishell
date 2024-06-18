/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expaneded.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: adakheel <adakheel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/09 07:40:37 by adakheel      #+#    #+#                 */
/*   Updated: 2024/06/14 12:48:19 by adakheel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


// void	search_in_cmd(t_all *all, char **array_str)
// {
// 	int		index;
// 	int		i;
// 	int		start;
// 	char	*str;
// 	char	*dvalue;
// 	char	*temp;

// 	index = 0;
// 	start = 0;
// 	str = NULL;
// 	while (array_str[index] != NULL)
// 	{
// 		i = 0;
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
// 				if (array_str[index][i] && array_str[index][i] == '$' && !is_white_space(array_str[index][i + 1]))
// 				{
// 					start = i;
// 					if (!array_str[index][i + 1] || array_str[index][i + 1] == '"')
// 					{
// 						dvalue = ft_substr(&array_str[index][start], 0, 1);
// 						start += 2;
// 						i += 2;
// 					}
// 					else
// 					{
// 						while (array_str[index][i] && !is_white_space(array_str[index][i]) && array_str[index][i] != '"')
// 							i++;
// 						start++;
// 						dvalue = value_of_dollar_sign(all, &array_str[index][start], i - start);
// 					}
// 					if (dvalue)
// 					{
// 						str = ft_strjoin_free(str, dvalue);
// 						free(dvalue);
// 					}
// 					else if (!dvalue)
// 					{
// 						dvalue = ft_substr(&array_str[index][i], 0, 1);
// 						str = ft_strjoin_free(str, dvalue);
// 						free(dvalue);
// 					}
// 				}
// 				else if (array_str[index][i] && array_str[index][i] == '$' && is_white_space(array_str[index][i + 1]))
// 				{
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
// 		}
// 		else
// 		{
// 			i = 0;
// 			while (array_str[index][i])
// 			{
// 				if (array_str[index][i] == '$' && (!array_str[index][i + 1] || !is_white_space(array_str[index][i + 1])))
// 				{
// 					if (!array_str[index][i + 1])
// 					{
// 						dvalue = value_of_dollar_sign(all, &array_str[index][start], 1);
// 						i++;
// 					}
// 					else
// 					{
// 						i++;
// 						start = i;
// 						while (array_str[index][i] && !is_white_space(array_str[index][i]))
// 							i++;
// 						dvalue = value_of_dollar_sign(all, &array_str[index][start], i - start);
// 						if (!dvalue)
// 							dvalue = ft_substr(&array_str[index][i], 0, 1);
// 					}
// 					if (!str)
// 						str = ft_strdup(dvalue);
// 					else
// 					{
// 						str = ft_strjoin_free(str, " ");
// 						str = ft_strjoin_free(str, dvalue);
// 					}
// 					free(dvalue);
// 				}
// 				else
// 				{
// 					start = i;
// 					while (array_str[index][i] && array_str[index][i] != '$')
// 						i++;
// 					temp = ft_substr(&array_str[index][start], 0, i - start);
// 					if (!str)
// 						str = ft_strdup(temp);
// 					else
// 					{
// 						str = ft_strjoin_free(str, " ");
// 						str = ft_strjoin_free(str, temp);
// 					}
// 					free(temp);
// 				}
// 			}
// 			free(array_str[index]);
// 			array_str[index] = ft_strdup(str);
// 			free(str);
// 			str = NULL;
// 		}
// 		index++;
// 	}
// }



// void	search_in_nodes(t_all *all, t_chunk *chunks)
// {
// 	t_chunk	*temp;
// 	char	*dvalue;
// 	char	*t_str;
// 	int		i;
// 	int		start;

// 	temp = chunks;
// 	dvalue = NULL;
// 	t_str = NULL;
// 	while (temp)
// 	{
// 		i = 0;
// 		while (temp->str[i])
// 		{
// 			if (!is_white_space(temp->str[i]))
// 			{
// 				if (temp->str[i] == '$' && temp->str[i + 1] && !is_white_space(temp->str[i + 1]))
// 				{
// 					start = i + 1;
// 					while (temp->str[i] && !is_white_space(temp->str[i]))
// 						i++;
// 					t_str = value_of_dollar_sign(all, &temp->str[start], i - start);
// 					if (!t_str)
// 					{
// 						//t_str = ft_substr(&temp->str[start - 1], 0, (i - start) + 1);
// 						t_str = ft_substr(&temp->str[i], 0, 1);
// 					}
// 				}
// 				else if (temp->str[i] == '"')
// 				{
// 					while (temp->str[i])
// 					{
// 						if (temp->str[i] == '"')
// 							i++;
// 						start = i;
// 						while (temp->str[i] && temp->str[i] != '$' && temp->str[i] != '"')
// 							i++;
// 						t_str = ft_substr(&temp->str[start], 0, i - start);
// 						if (temp->str[i] && temp->str[i] == '$')
// 						{
// 							start = i + 1;
// 							while (temp->str[i] && temp->str[i] != '"' && !is_white_space(temp->str[i]))
// 								i++;
// 							dvalue = value_of_dollar_sign(all, &temp->str[start], i - start);
// 							if (!dvalue)
// 							{
// 								//dvalue = ft_substr(&temp->str[start - 1], 0, (i - start) + 1);
// 								dvalue = ft_substr(&temp->str[i], 0, 1);
// 							}
// 							t_str = ft_strjoin_free(t_str, dvalue);
// 							free(dvalue);
// 							dvalue = NULL;
// 						}
// 						if (temp->str[i] == '"')
// 							i++;
// 					}
// 				}
// 				else
// 				{
// 					t_str = ft_strdup(temp->str);
// 					while (temp->str[i])
// 						i++;
// 				}
// 			}
// 			else if (temp->str[i])
// 				i++;
// 		}
// 		free(temp->str);
// 		temp->str = ft_strdup(t_str);
// 		// printf("new str is (%s)\n", temp->str);
// 		free(t_str);
// 		temp = temp->next;
// 	}
// }

char	*dollar_found(t_all *all, char *str)
{
	int	i;

	i = 1;
	if (!str[i] || str[i] == '$' || str[i] == 34 || str[i] == 39)
		return (ft_substr(str, 0, i));
	if (str[i] == '?')
		return (ft_itoa(all->last_exit_status));
	if (is_white_space(str[i]))
	{
		while (str[i] && is_white_space(str[i]))
			i++;
		//dprintf(2, "substr is (%s)\n", ft_substr(str, 0, i));
		return (ft_substr(str, 0, i));
	}
	while (str[i] && ft_isalnum_under(str[i]))
		i++;
	return (value_of_dollar_sign(all, &str[1], i - 1));
}

int		find_quote(char *str)
{
	int i;
	
	i = 0;
	while (str[i])
	{
		if (str[i] == 39)
			return (i + 1);
		i++;
	}
	return (0);
}

void	handle_single_quotes(int *i, int start, char **whole, char *str)
{
	char	*dvalue;

	if (*i - start > 0 && !(*whole))
		(*whole) = ft_substr(str, start, *i - start);
	else if (i - start > 0 && (*whole))
	{
		dvalue = ft_substr(str, start, *i - start);
		(*whole) = ft_strjoin_free((*whole), dvalue);
		free(dvalue);
	}
	start = *i;
	(*i)++;
	while (str[*i] && str[*i] != 39)
		(*i)++;
	(*i)++;
	if (!(*whole))
		(*whole) = ft_substr(str, start, *i - start);
	else
	{
		dvalue = ft_substr(str, start, *i - start);
		(*whole) = ft_strjoin_free((*whole), dvalue);
		free(dvalue);
	}
}



int		is_double_quote(char current, int counter)
{
	if (current == 34)
	{
		if (counter == 0)
			counter = 34;
		else
			counter = 0;
	}
	return (counter);
}

void	dollar_signe_join(t_all *all, char **whole, char *str, int start)
{
	char	*dvalue;

	if (!*whole)
	{
		*whole = ft_substr(str, start, all->line->tempi - start);
		dvalue = dollar_found(all, &str[all->line->tempi]);
		// dprintf(2, "str is (%s)\n", dvalue);
		// dprintf(2 , "here\n");
		// if (!dvalue)
		// 	dprintf(2, "nuu\n");
		if (all->line->tempc)
			dvalue = remove_quotes_exp(dvalue);
		// dprintf(2 , "here\n");
		dvalue = remove_whitespace_cmd(dvalue);
		// dprintf(2 , "here\n");
		*whole = ft_strjoin_free(*whole, dvalue);
		free(dvalue);
		//dprintf(2, "*whole Is (%s)\n", *whole);
	}
	else
	{
		dvalue = ft_substr(str, start, all->line->tempi - start);
		*whole = ft_strjoin_free(*whole, dvalue);
		free(dvalue);
		dvalue = dollar_found(all, &str[all->line->tempi]);
		if (all->line->tempc)
			dvalue = remove_quotes_exp(dvalue);
		dvalue = remove_whitespace_cmd(dvalue);
		*whole = ft_strjoin_free(*whole, dvalue);
		free(dvalue);
	}
}

int		dollar_signe_pos(t_all *all, char *str, int i)
{
	all->line->tempc = is_double_quote(str[i], all->line->tempc);
	while (str[i] && str[i] != '$')
	{
		if (str[i] == 39)
		{
			i++;
			if (find_quote(&str[i]))
				i += find_quote(&str[i]);
			if (!str[i])
				break ;
		}
		i++;
		all->line->tempc = is_double_quote(str[i], all->line->tempc);
	}
	return (i);
}

int		dollar_signe_pos_update(char *str, int i)
{
	if (str[i] == '?')
		i++;
	else
	{
		while (str[i] && ft_isalnum_under(str[i]))
			i++;
	}
	return (i);
}

void	no_dollar_signe(char **whole, char *str, int i, int start)
{
	if (!*whole)
		*whole = ft_substr(str, start, i - start);
	else
		*whole = ft_strjoin_free(*whole, &str[start]);
}

char	*search_dollar_signe(t_all *all, char *str)
{
	int		i;
	int		start;
	char	*whole;

	i = 0;
	whole = NULL;
	all->line->tempc = 0;
	while (str[i])
	{
		start = i;
		i = dollar_signe_pos(all, str, i);
		if (!str[i])
			no_dollar_signe(&whole, str, i, start);
		else if (str[i] == 39)
			handle_single_quotes(&i, start, &whole, str);
		else
		{
			all->line->tempi = i;
			dollar_signe_join(all, &whole, str, start);
			i++;
			i = dollar_signe_pos_update(str, i);
		}
	}
	free(str);
	// dprintf(2, "str is (%s)\n", whole);
	return (whole);
}























// char	*search_dollar_signe(t_all *all, char *str)
// {
// 	int		i;
// 	int		start;
// 	char	*dvalue;
// 	char	*temp;
// 	char	*whole;

// 	i = 0;
// 	whole = NULL;
// 	//dprintf(2, "start\n");
// 	dprintf(2, "str at the begin is (%s)\n", str);
// 	// if (str[0] == 39)
// 	// {
// 	// 	whole = ft_strdup(str);
// 	// 	free(str);
// 	// 	remove_quotes_cmd(whole);
// 	// 	return (whole);
// 	// }
// 	while (str[i])
// 	{
// 		start = i;
// 		while (str[i] && str[i] != '$')
// 		{
// 			if (str[i] == 39)
// 			{
// 				i++;
// 				if (find_quote(&str[i]))
// 					i += find_quote(&str[i]);
// 				if (!str[i])
// 					break ;
// 			}
// 			i++;
// 		}
// 		if (!str[i])
// 		{
// 			if (!whole)
// 				whole = ft_substr(str, start, i - start);
// 			else
// 				whole = ft_strjoin_free(whole, &str[start]);
// 		}
// 		else if (str[i] == 39)
// 		{
// 			//dprintf(2, "char is (%c)\n", str[i]);
// 			if (i - start > 0 && !whole)
// 				whole = ft_substr(str, start, i - start);
// 			else if (i - start > 0 && whole)
// 			{
// 				dvalue = ft_substr(str, start, i - start);
// 				whole = ft_strjoin_free(whole, dvalue);
// 				free(dvalue);
// 			}
// 			start = i;
// 			i++;
// 			while (str[i] && str[i] != 39)
// 				i++;
// 			i++;
// 			if (!whole)
// 				whole = ft_substr(str, start, i - start);
// 			else
// 			{
// 				dvalue = ft_substr(str, start, i - start);
// 				whole = ft_strjoin_free(whole, dvalue);
// 				free(dvalue);
// 			}
// 			//dprintf(2, "str quotes is (%s)\n", whole);
// 		}
// 		else
// 		{
// 			//dprintf(2, "in else\n");
// 			if (!whole)
// 			{
// 				whole = ft_substr(str, start, i - start);
// 				dvalue = dollar_found(all, &str[i]);
// 				whole = ft_strjoin_free(whole, dvalue);
// 				free(dvalue);
// 				//dprintf(2, "whole Is (%s)\n", whole);
// 			}
// 			// else if (i - start > 0 && whole)
// 			// 	dvalue = dollar_found(all, &str[i]);
// 			else
// 			{
// 				dvalue = dollar_found(all, &str[i]);
// 				whole = ft_strjoin_free(whole, dvalue);
// 				free(dvalue);
// 			}
// 			i++;
// 			if (str[i] == '?')
// 				i++;
// 			else
// 			{
// 				while (str[i] && ft_isalnum_under(str[i]))
// 					i++;
// 			}
// 		}
// 	}
// 	free(str);
// 	dprintf(2, "str after expende is (%s)\n", whole);
// 	// remove_quotes_cmd(whole);
// 	return (whole);
// }











// char	*search_dollar_signe(t_all *all, char *str)
// {
// 	int		i;
// 	int		start;
// 	char	*dvalue;
// 	char	*temp;
// 	char	*whole;

// 	i = 0;
// 	whole = NULL;
// 	while (str[i])
// 	{
// 		if (str[0] == 39)
// 		{
// 			whole = ft_strdup(str);
// 			free(str);
// 			remove_quotes_cmd(whole);
// 			// dprintf(2, "str = (%s)\n", whole);
// 			return (whole);
// 		}
// 		start = i;
// 		while (str[i] && str[i] != '$')
// 			i++;
// 		if (str[i] && (!str[i + 1] || is_white_space(str[i + 1])))
// 			i++;
// 		if (!str[i])
// 		{
// 			whole = ft_strdup(str);
// 			free(str);
// 			remove_quotes_cmd(whole);
// 			// dprintf(2, "str = (%s)\n", whole);
// 			return (whole);
// 		}
// 		if (str[i] && !is_white_space(str[i]) && !is_white_space(str[i + 1]))
// 		{
// 			if (!whole)
// 				whole = ft_substr(str, start, i - start);
// 			else
// 			{
// 				temp = ft_substr(str, start, i - start);
// 				whole = ft_strjoin_free(whole, temp);
// 			}
// 			// dprintf(2, "whole = (%s)\n", whole);
// 			start = i;
// 			while (str[i] && str[i + 1] != '$' && !is_white_space(str[i]))
// 				i++;
// 			if (!whole)
// 			{
// 				// dprintf(2, "char = (%c)\n", str[start]);
// 				whole = value_of_dollar_sign(all, &str[start + 1], i - start);
// 				if (!whole)
// 					whole = ft_substr(str, i, 1);
// 			}
// 			else
// 			{
// 				// dprintf(2, "char = (%c)\n", str[start]);
// 				dvalue = value_of_dollar_sign(all, &str[start + 1], i - start);
// 				if (!dvalue)
// 					dvalue = ft_substr(str, i, 1);
// 				whole = ft_strjoin_free(whole, dvalue);
// 				free(dvalue);
// 			}
// 			// dprintf(2, "whole = (%s)\n", whole);
// 		}
// 		else
// 			whole = ft_substr(str, start, i - start);
// 	}
// 	free(str);
// 	remove_quotes_cmd(whole);
// 	return (whole);
// }



// void	expanded(t_all *all, t_cmd *cmd)
// {
// 	t_cmd	*temp;
// 	t_chunk	*node;
// 	int		i;

// 	temp = cmd;
// 	while (temp)
// 	{
// 		i = 0;
// 		while (temp->cmd[i])
// 		{
// 			//search_in_cmd(all, temp->cmd);
// 			temp->cmd[i] = search_dollar_signe(all, temp->cmd[i]);
// 			i++;
// 		}
// 		node = temp->delimiter;
// 		while (node)
// 		{
// 			//search_in_nodes(all, temp->delimiter);
// 			node->strsearch_dollar_signe(all, node->str);
// 			node = node->next;
// 		}
// 		node = temp->infile;
// 		while (node)
// 		{
// 			//search_in_nodes(all, temp->infile);
// 			search_dollar_signe(all, node->str);
// 			node = node->next;
// 		}
// 		node = temp->outfile;
// 		while (node)
// 		{
// 			//search_in_nodes(all, temp->outfile);
// 			search_dollar_signe(all, node->str);
// 			node = temp->next;
// 		}
// 		temp = temp->next;
// 	}
// }
