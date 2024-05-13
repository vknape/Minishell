/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expaneded.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: adakheel <adakheel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/09 07:40:37 by adakheel      #+#    #+#                 */
/*   Updated: 2024/05/13 11:41:42 by adakheel      ########   odam.nl         */
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
						dvalue = ft_substr(&array_str[index][start - 1], 0, (i - start) + 1);
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
							dvalue = ft_substr(&array_str[index][start - 1], 0, (i - start) + 1);
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
						t_str = ft_substr(&temp->str[start - 1], 0, (i - start) + 1);
				}
				else if (temp->str[i] == '"')
				{
					while (temp->str[i])
					{
						i++;
						start = i;
						while (temp->str[i] && temp->str[i] != '$' && temp->str[i] != '"')
							i++;
						t_str = ft_substr(&temp->str[start], 0, i - start);
						// printf("here str is (%s)\n", t_str);
						if (temp->str[i] && temp->str[i] == '$')
						{
							start = i + 1;
							while (temp->str[i] && temp->str[i] != '"' && !is_white_space(temp->str[i]))
								i++;
							dvalue = value_of_dollar_sign(all, &temp->str[start], i - start);
							if (!dvalue)
							{
								dvalue = ft_substr(&temp->str[start - 1], 0, (i - start) + 1);
							}
						}
						if (dvalue)
						{
							t_str = ft_strjoin_free(t_str, dvalue);
							free(dvalue);
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
		// printf("new str is (%s)\n", temp->str);
		free(t_str);
		temp = temp->next;
	}
}

void	expanded(t_all *all, t_cmd *cmd)
{
	t_cmd	*temp;

	temp = cmd;
	while (temp)
	{
		if (temp->cmd)
		{
			// printf("before temp->cmd(%s)\n", temp->cmd[0]);
			// printf("before temp->cmd[1](%s)\n", temp->cmd[1]);
			search_in_cmd(all, temp->cmd);
			// printf("aftre temp->cmd(%s)\n", temp->cmd[0]);
			// printf("aftre temp->cmd[1](%s)\n", temp->cmd[1]);
		}
		if (temp->delimiter)
		{
			// printf("before temp->del(%s)\n", temp->delimiter->str);
			search_in_nodes(all, temp->delimiter);
			// printf("after temp->del(%s)\n", temp->delimiter->str);
		}
		if (temp->infile)
		{
			// printf("before temp->infile(%s)\n", temp->infile->str);
			search_in_nodes(all, temp->infile);
			// printf("after temp->infile(%s)\n", temp->infile->str);
		}
		if (temp->outfile)
		{
			// printf("before temp->outfile(%s)\n", temp->outfile->str);
			search_in_nodes(all, temp->outfile);
			// printf("after temp->outfile(%s)\n", temp->outfile->str);
		}
		temp = temp->next;
	}
}
