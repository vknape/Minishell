
#include "minishell.h"

int	is_one_of_builtins(char *str)
{
	if (!ft_strncmp("echo", str, 5))
		return (1);
	if (!ft_strncmp("cd", str, 3))
		return (1);
	if (!ft_strncmp("pwd", str, 4))
		return (1);
	if (!ft_strncmp("export", str, 7))
		return (1);
	if (!ft_strncmp("unset", str, 6))
		return (1);
	if (!ft_strncmp("env", str, 4))
		return (1);
	if (!ft_strncmp("exit", str, 5))
		return (1);
	else
		return (0);
}

char	**join_arrays(t_all *all, char **array1, char **array2)
{
	int		i;
	int		j;
	char	**temp;

	i = 0;
	while (array1 && array1[i])
		i++;
	j = 0;
	while (array2 && array2[j])
		j++;
	temp = ft_calloc(sizeof(char *), i + j + 1);
	if (!temp)
	{
		free2d(array2);
		memory_allocation_failed(all);
	}
	i = 0;
	while (array1 && array1[i])
	{
		temp[i] = array1[i];
		array1[i] = NULL;
		i++;
	}
	j = 0;
	while (array2 && array2[j])
	{
		temp[i] = array2[j];
		array2[j] = NULL;
		j++;
		i++;
	}
	free(array1);
	free(array2);
	return (temp);
}

char	*add_file(t_all *all, t_cmd *each_cmd, t_chunk *chunks)
{
	int		i;
	char	**temp;
	char	*str;

	i = 0;
	temp = NULL;
	while (chunks->next->str[i] && is_white_space(chunks->next->str[i]))
		i++;
	while (chunks->next->str[i] && !is_white_space(chunks->next->str[i]))
		i++;
	while (chunks->next->str[i] && is_white_space(chunks->next->str[i]))
		i++;
	if (chunks->next->str[i])
		temp = ft_split_quotes(&chunks->next->str[i], ' ');
	if (!temp && errno == 12)
		memory_allocation_failed(all);
	if (temp && temp[0] && !each_cmd->cmd)
		each_cmd->cmd = temp;
	else if (temp && temp[0] && each_cmd->cmd)
		each_cmd->cmd = join_arrays(all, each_cmd->cmd, temp);
	str = ft_substr(chunks->next->str, 0, i);
	if (!str && errno == 12)
		memory_allocation_failed(all);
	return (str);
}

void	other_redirections(t_all *all, t_cmd *each_cmd, \
	t_chunk *chunks, char *str)
{
	if (!ft_strncmp("<", chunks->str, 2))
	{
		ft_lstadd_back_chunk(&each_cmd->infile, ft_lstnewchunk(all, str));
		ft_lstlast_chunk(each_cmd->infile)->is_infile = true;
	}
	else if (!ft_strncmp("<<", chunks->str, 2))
	{
		ft_lstadd_back_chunk(&each_cmd->infile, ft_lstnewchunk(all, str));
		ft_lstlast_chunk(each_cmd->infile)->is_heredoc = true;
	}
	else
	{
		each_cmd->cmd = ft_split_quotes(chunks->str, ' ');
		if (is_one_of_builtins(each_cmd->cmd[0]))
			each_cmd->is_builtin = true;
	}
}

void	fill_cmd_nodes(t_all *all, t_chunk *chunks)
{
	t_cmd	*each_cmd;
	int		i;
	char	**temp;
	char	*str;

	temp = NULL;
	each_cmd = ft_lstlast_cmd(all->line->each_cmd);
	if (!ft_strncmp(">", chunks->str, 2) || !ft_strncmp(">>", chunks->str, 3) \
	|| !ft_strncmp("<", chunks->str, 2) || !ft_strncmp("<<", chunks->str, 2))
		str = add_file(all, each_cmd, chunks);
	if (!ft_strncmp(">", chunks->str, 2))
	{
		ft_lstadd_back_chunk(&each_cmd->outfile, ft_lstnewchunk(all, str));
		ft_lstlast_chunk(each_cmd->outfile)->is_outfile = true;
	}
	else if (!ft_strncmp(">>", chunks->str, 3))
	{
		ft_lstadd_back_chunk(&each_cmd->outfile, ft_lstnewchunk(all, str));
		ft_lstlast_chunk(each_cmd->outfile)->is_append = true;
	}
	else
		other_redirections(all, each_cmd, chunks, str);
}

void	split_cmd_nodes(t_all *all)
{
	t_chunk	*chunks;
	t_cmd	*temp;

	chunks = all->line->chunks;
	ft_lstadd_back_cmd(&all->line->each_cmd, ft_lstnewcmd());
	temp = all->line->each_cmd;
	while (chunks)
	{
		if (chunks->str[0] == '|')
			ft_lstadd_back_cmd(&all->line->each_cmd, ft_lstnewcmd());
		else
		{
			fill_cmd_nodes(all, chunks);
			if (ft_strchr("<>", chunks->str[0]))
				chunks = chunks->next;
		}
		chunks = chunks->next;
	}
	while (temp)
	{
		all->line->total_cmd++;
		temp = temp->next;
	}
}
