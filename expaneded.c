/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expaneded.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: adakheel <adakheel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/09 07:40:37 by adakheel      #+#    #+#                 */
/*   Updated: 2024/05/15 10:02:54 by adakheel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void	search_in_cmd(t_all *all, char **array_str)
{
	int		index;
	int		i;
	int		start;
	char	*str;
	char	*dvalue;
	char	*temp;

	index = 0;
	start = 0;
	str = NULL;
	while (array_str[index] != NULL)
	{
		i = 0;
		if (array_str[index][0] == '"')
		{
			while (array_str[index][i])
			{
				if (i == 0)
					i++;
				start = i;
				while (array_str[index][i] && array_str[index][i] != '$' && array_str[index][i] != '"')
					i++;
				temp = ft_substr(&array_str[index][start], 0, i - start);
				if (!str)
					str = ft_strdup(temp);
				else
					str = ft_strjoin_free(str, temp);
				free(temp);
				if (array_str[index][i] && array_str[index][i] == '$' && !is_white_space(array_str[index][i + 1]))
				{
					start = i;
					if (!array_str[index][i + 1] || array_str[index][i + 1] == '"')
					{
						dvalue = ft_substr(&array_str[index][start], 0, 1);
						start += 2;
						i += 2;
					}
					else
					{
						while (array_str[index][i] && !is_white_space(array_str[index][i]) && array_str[index][i] != '"')
							i++;
						start++;
						dvalue = value_of_dollar_sign(all, &array_str[index][start], i - start);
					}
					if (dvalue)
					{
						str = ft_strjoin_free(str, dvalue);
						free(dvalue);
					}
					else if (!dvalue)
					{
						dvalue = ft_substr(&array_str[index][i], 0, 1);
						str = ft_strjoin_free(str, dvalue);
						free(dvalue);
					}
				}
				else if (array_str[index][i] && array_str[index][i] == '$' && is_white_space(array_str[index][i + 1]))
				{
					temp = ft_substr(&array_str[index][i], 0, 1);
					str = ft_strjoin_free(str, temp);
					free(temp);
					i++;
				}
				if (array_str[index][i] == '"')
					i++;
			}
			free(array_str[index]);
			array_str[index] = ft_strdup(str);
			free(str);
			str = NULL;
		}
		else
		{
			i = 0;
			while (array_str[index][i])
			{
				if (array_str[index][i] == '$' && (!array_str[index][i + 1] || !is_white_space(array_str[index][i + 1])))
				{
					if (!array_str[index][i + 1])
					{
						dvalue = value_of_dollar_sign(all, &array_str[index][start], 1);
						i++;
					}
					else
					{
						i++;
						start = i;
						while (array_str[index][i] && !is_white_space(array_str[index][i]))
							i++;
						dvalue = value_of_dollar_sign(all, &array_str[index][start], i - start);
						if (!dvalue)
							dvalue = ft_substr(&array_str[index][i], 0, 1);
					}
					if (!str)
						str = ft_strdup(dvalue);
					else
					{
						str = ft_strjoin_free(str, " ");
						str = ft_strjoin_free(str, dvalue);
					}
					free(dvalue);
				}
				else
				{
					start = i;
					while (array_str[index][i] && array_str[index][i] != '$')
						i++;
					temp = ft_substr(&array_str[index][start], 0, i - start);
					if (!str)
						str = ft_strdup(temp);
					else
					{
						str = ft_strjoin_free(str, " ");
						str = ft_strjoin_free(str, temp);
					}
					free(temp);
				}
			}
			free(array_str[index]);
			array_str[index] = ft_strdup(str);
			free(str);
			str = NULL;
		}
		index++;
	}
}



void	search_in_nodes(t_all *all, t_chunk *chunks)
{
	t_chunk	*temp;
	char	*dvalue;
	char	*t_str;
	int		i;
	int		start;

	temp = chunks;
	dvalue = NULL;
	t_str = NULL;
	while (temp)
	{
		i = 0;
		while (temp->str[i])
		{
			if (!is_white_space(temp->str[i]))
			{
				if (temp->str[i] == '$' && temp->str[i + 1] && !is_white_space(temp->str[i + 1]))
				{
					start = i + 1;
					while (temp->str[i] && !is_white_space(temp->str[i]))
						i++;
					t_str = value_of_dollar_sign(all, &temp->str[start], i - start);
					if (!t_str)
					{
						//t_str = ft_substr(&temp->str[start - 1], 0, (i - start) + 1);
						t_str = ft_substr(&temp->str[i], 0, 1);
					}
				}
				else if (temp->str[i] == '"')
				{
					while (temp->str[i])
					{
						if (temp->str[i] == '"')
							i++;
						start = i;
						while (temp->str[i] && temp->str[i] != '$' && temp->str[i] != '"')
							i++;
						t_str = ft_substr(&temp->str[start], 0, i - start);
						if (temp->str[i] && temp->str[i] == '$')
						{
							start = i + 1;
							while (temp->str[i] && temp->str[i] != '"' && !is_white_space(temp->str[i]))
								i++;
							dvalue = value_of_dollar_sign(all, &temp->str[start], i - start);
							if (!dvalue)
							{
								//dvalue = ft_substr(&temp->str[start - 1], 0, (i - start) + 1);
								dvalue = ft_substr(&temp->str[i], 0, 1);
							}
							t_str = ft_strjoin_free(t_str, dvalue);
							free(dvalue);
							dvalue = NULL;
						}
						if (temp->str[i] == '"')
							i++;
					}
				}
				else
				{
					t_str = ft_strdup(temp->str);
					while (temp->str[i])
						i++;
				}
			}
			else if (temp->str[i])
				i++;
		}
		free(temp->str);
		temp->str = ft_strdup(t_str);
		printf("new str is (%s)\n", temp->str);
		free(t_str);
		temp = temp->next;
	}
}

char	*search_dollar_signe(t_all *all, char *str)
{
	int		i;
	int		start;
	char	*dvalue;
	char	*temp;
	char	*whole;

	i = 0;
	whole = NULL;
	while (str[i])
	{
		if (str[0] == 39)
		{
			whole = ft_strdup(str);
			free(str);
			remove_quotes_cmd(whole);
			// dprintf(2, "str = (%s)\n", whole);
			return (whole);
		}
		start = i;
		while (str[i] && str[i] != '$')
			i++;
		if (!str[i])
		{
			whole = ft_strdup(str);
			free(str);
			remove_quotes_cmd(whole);
			// dprintf(2, "str = (%s)\n", whole);
			return (whole);
		}
		if (str[i] && !is_white_space(str[i + 1]))
		{
			if (!whole)
				whole = ft_substr(str, start, i - start);
			else
			{
				temp = ft_substr(str, start, i - start);
				whole = ft_strjoin_free(whole, temp);
			}
			// dprintf(2, "whole = (%s)\n", whole);
			start = i;
			while (str[i] && !is_white_space(str[i])
			)
				i++;
			if (!whole)
			{
				// dprintf(2, "char = (%c)\n", str[start]);
				whole = value_of_dollar_sign(all, &str[start + 1], i - start);
				if (!whole)
					whole = ft_substr(str, i, 1);
			}
			else
			{
				// dprintf(2, "char = (%c)\n", str[start]);
				dvalue = value_of_dollar_sign(all, &str[start + 1], i - start);
				if (!dvalue)
					dvalue = ft_substr(str, i, 1);
				whole = ft_strjoin_free(whole, dvalue);
			}
			// dprintf(2, "whole = (%s)\n", whole);
		}
	}
	// dprintf(2, "str = (%s)\n", str);
	free(str);
	remove_quotes_cmd(whole);
	// dprintf(2, "str = (%s)\n", whole);
	return (whole);
}



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
