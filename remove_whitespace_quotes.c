/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   remove_whitespace_quotes.c                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: adakheel <adakheel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/14 11:16:06 by adakheel      #+#    #+#                 */
/*   Updated: 2024/05/15 13:20:17 by adakheel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*remove_whitespace_cmd(char *str)
{
	int		index;
	int		i;
	char	*des;
	int		j;

	index = 0;
	i = 0;
	j = 0;
	if (str[i] && (str[i] == 34 || str[i] == 39))
	{
		des = ft_strdup(str);
		free(str);
		return (des);
	}
	des = malloc(sizeof(char) * (ft_strlen(str) + 1));
	while (str[i])
	{
		if (!is_white_space(str[i]))
		{
			des[j] = str[i];
			j++;
		}
		i++;
	}
	des[j] = '\0';
	free(str);
	return (des);
	// str = ft_strdup(des);
	// printf("str here = (%s)\n", str);
	// free(des);
}

// void	remove_whitespace_cmd(t_all *all, char **cmd_array)
// {
// 	int		index;
// 	int		i;
// 	char	*des;
// 	int		j;

// 	index = 0;
// 	while (cmd_array[index])
// 	{
// 		i = 0;
// 		j = 0;
// 		des = malloc(sizeof(char) * (ft_strlen(cmd_array[index]) + 1));
// 		while (cmd_array[index][i])
// 		{
// 			if (!is_white_space(cmd_array[index][i]))
// 			{
// 				des[j] = cmd_array[index][i];
// 				j++;
// 			}
// 			i++;
// 		}
// 		des[j] = '\0';
// 		free(cmd_array[index]);
// 		cmd_array[index] = ft_strdup(des);
// 		free(des);
// 		index++;
// 	}
// }

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

char	*remove_quotes_cmd(char *str)
{
	char	*des;
	int		i;

	// printf("%s\n", str);
	if (str && (str[0] == 34 || str[0] == 39))
	{
		i = ft_strlen(str);
		des = ft_substr(str, 1, i - 2);
		free(str);
		// printf("des = %s\n", des);
		return (des);
		// str = ft_strdup(des);
		// free(des);
		
	}
	else
		return (str);
}

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

void	remove_whitespace_quotes(t_all *all, t_cmd *cmd)
{
	t_cmd	*temp;
	t_chunk	*node;
	int		i;

	temp = cmd;
	i = 0;
	while (temp)
	{
		while (temp->cmd[i])
		{
			temp->cmd[i] = remove_whitespace_cmd(temp->cmd[i]);
			temp->cmd[i] = remove_quotes_cmd(temp->cmd[i]);
			// temp->cmd[i] = search_dollar_signe(all, temp->cmd[i]);
			// dprintf(2, "str here is (%s)\n", temp->cmd[i]);
			i++;
		}
		node = temp->delimiter;
		while (node)
		{
			node->str = remove_whitespace_cmd(node->str);
			node->str = remove_quotes_cmd(node->str);
			// node->str = search_dollar_signe(all, node->str);
			// dprintf(2, "str here is (%s)\n", node->str);
			node = node->next;
		}
		node = temp->infile;
		while (node)
		{
			node->str = remove_whitespace_cmd(node->str);
			node->str = remove_quotes_cmd(node->str);
			// node->str = search_dollar_signe(all, node->str);
			// dprintf(2, "str here is (%s)\n", node->str);
			node = node->next;
		}
		node = temp->outfile;
		while (node)
		{
			node->str = remove_whitespace_cmd(node->str);
			node->str = remove_quotes_cmd(node->str);
			// node->str = search_dollar_signe(all, node->str);
			// dprintf(2, "str here is (%s)\n", node->str);
			node = node->next;
		}
		temp = temp->next;
	}
}