
#include "minishell.h"

// void	split_cmds(char *curline, t_all *all)
// {
// 	t_line	*line;
// 	int		i;
// 	int		pos;
// 	char	c;
// 	char	*str;

// 	line = all->line;
// 	pos = 0;
// 	i = 0;
// 	while (curline[i] != '\0')
// 	{
// 		if (curline[i] == 34 || curline[i] == 39)
// 		{
// 			c = curline[i];
// 			i++;
// 			while (curline[i] != c)
// 				i++;
// 		}
// 		if (curline[i] == '|' || curline[i + 1] == '\0')
// 		{
// 			if (curline[i + 1] == '\0')
// 				str = ft_substr(curline, pos, i - pos + 1);
// 			else
// 				str = ft_substr(curline, pos, i - pos);
// 			pos = i + 1;
// 			ft_lstadd_back_cmd(&line->each_cmd, ft_lstnewcmd(str));
// 		}
// 		i++;
// 	}
// }

void	fill_cmd_nodes(t_all *all, t_chunk *chunks)
{
	t_cmd	*each_cmd;

	each_cmd = ft_lstlast_cmd(all->line->each_cmd);
	if (!ft_strncmp(">", chunks->str, 2))
	{
		ft_lstadd_back_chunk(&each_cmd->outfile, ft_lstnewchunk(ft_strdup(chunks->next->str)));
		ft_lstlast_chunk(each_cmd->outfile)->is_outfile = true;
	}
	else if (!ft_strncmp(">>", chunks->str, 3))
	{
		ft_lstadd_back_chunk(&each_cmd->outfile, ft_lstnewchunk(ft_strdup(chunks->next->str)));
		ft_lstlast_chunk(each_cmd->outfile)->is_append = true;
	}
	else if (!ft_strncmp("<", chunks->str, 2))
	{
		ft_lstadd_back_chunk(&each_cmd->infile, ft_lstnewchunk(ft_strdup(chunks->next->str)));
		ft_lstlast_chunk(each_cmd->infile)->is_infile = true;
	}
	else if (!ft_strncmp("<<", chunks->str, 2))
	{
		ft_lstadd_back_chunk(&each_cmd->infile, ft_lstnewchunk(ft_strdup(chunks->next->str)));
		ft_lstlast_chunk(each_cmd->infile)->is_heredoc = true;
	}
	else
	{
		each_cmd->cmd = ft_split_quotes(chunks->str, ' ');
	}
}

void	split_cmd_nodes(t_all *all)
{
	t_chunk	*chunks;

	chunks = all->line->chunks;
	ft_lstadd_back_cmd(&all->line->each_cmd, ft_lstnewcmd());
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
	while (all->line->each_cmd)
	{
		if (all->line->each_cmd->cmd)
		{
			ft_echo_quotes(all, all->line->each_cmd->cmd);
		}
		// while (all->line->each_cmd->cmd[i])
		// {
		// 	printf("cmd = %s\n", all->line->each_cmd->cmd[i]);
		// 	i++;
		// }
		// i = 0;
		// while (all->line->each_cmd->infile)
		// {
		// 	printf("str = %s\n", all->line->each_cmd->infile->str);
		// 	printf("infile = %d\n", all->line->each_cmd->infile->is_infile);
		// 	printf("outfile = %d\n", all->line->each_cmd->infile->is_outfile);
		// 	printf("heredoc = %d\n", all->line->each_cmd->infile->is_heredoc);
		// 	printf("append = %d\n", all->line->each_cmd->infile->is_append);
		// 	all->line->each_cmd->infile = all->line->each_cmd->infile->next;
		// }
		// while (all->line->each_cmd->outfile)
		// {
		// 	printf("str = %s\n", all->line->each_cmd->outfile->str);
		// 	printf("infile = %d\n", all->line->each_cmd->outfile->is_infile);
		// 	printf("outfile = %d\n", all->line->each_cmd->outfile->is_outfile);
		// 	printf("heredoc = %d\n", all->line->each_cmd->outfile->is_heredoc);
		// 	printf("append = %d\n", all->line->each_cmd->outfile->is_append);
		// 	all->line->each_cmd->outfile = all->line->each_cmd->outfile->next;
		// }
		// printf("\n");
		all->line->each_cmd = all->line->each_cmd->next;
	}
}
