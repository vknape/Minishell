
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
	// if (each_cmd)
	// {
	// 	printf("isNULL\n");
	// 	exit (1);
	// }
	// each_cmd = ft_lstlastcmd(all->line->each_cmd);
	if (!each_cmd)
	{
		printf("NULL\n");
		exit (1);
	}
	printf("444\n");
	if (!ft_strncmp(">", chunks->str, 2))
	{
		ft_lstadd_back_chunk(&each_cmd->outfile, ft_lstnewchunk(ft_strdup(chunks->next->str)));
		// each_cmd->outfile->str = ft_strdup(chunks->next->str);
		ft_lstlast_chunk(each_cmd->outfile)->is_outfile = true;
		// if (each_cmd->outfile->is_append == true)
		// 	each_cmd->is_append == false;
	}
	else if (!ft_strncmp(">>", chunks->str, 3))
	{
		ft_lstadd_back_chunk(&each_cmd->outfile, ft_lstnewchunk(ft_strdup(chunks->next->str)));
		// each_cmd->outfile->str = ft_strdup(chunks->next->str);
		ft_lstlast_chunk(each_cmd->outfile)->is_append = true;
		// if (each_cmd->is_outfile == true)
		// 	each_cmd->is_outfile == false;
	}
	else if (!ft_strncmp("<", chunks->str, 2))
	{
		printf("666\n");
		ft_lstadd_back_chunk(&each_cmd->infile, ft_lstnewchunk(ft_strdup(chunks->next->str)));
		// each_cmd->infile->str = ft_strdup(chunks->next->str);
		ft_lstlast_chunk(each_cmd->infile)->is_infile = true;
		printf("after\n");
		// if (each_cmd->is_heredoc == true)
		// 	each_cmd->is_heredoc == false;
	}
	else if (!ft_strncmp("<<", chunks->str, 2))
	{
		ft_lstadd_back_chunk(&each_cmd->infile, ft_lstnewchunk(ft_strdup(chunks->next->str)));
		// each_cmd->infile->str = ft_strdup(chunks->next->str);
		ft_lstlast_chunk(each_cmd->infile)->is_heredoc = true;
	}
	else
	{
		printf("555\n");
		each_cmd->cmd = ft_split_quotes(chunks->str, ' ');

	}

}

void	split_cmd_nodes(t_all *all)
{
	t_chunk	*chunks;
	// t_cmd	*each_cmd;

	chunks = all->line->chunks;
	if (!all->line->each_cmd)
	{
		printf("NULLbefore\n");
	}
	ft_lstadd_back_cmd(&all->line->each_cmd, ft_lstnewcmd());
	if (!all->line->each_cmd)
	{
		printf("NULLafter\n");
		exit (1);
	}
	printf("111\n");
	while (chunks)
	{
		if (chunks->str[0] == '|')
		{
			printf("here\n");
			ft_lstadd_back_cmd(&all->line->each_cmd, ft_lstnewcmd());
			printf("222\n");
		}
		else
		{
			printf("333\n");
			if (!all->line->each_cmd)
			{
				printf("NULL\n");
				exit (1);
			}
			fill_cmd_nodes(all, chunks);
			if (ft_strchr("<>", chunks->str[0]))
				chunks = chunks->next;
		}
		chunks = chunks->next;
	}
	int i = 0;
	while (all->line->each_cmd)
	{
		while (all->line->each_cmd->cmd[i])
		{
			printf("cmd = %s\n", all->line->each_cmd->cmd[i]);
			i++;
		}
		i = 0;
		while (all->line->each_cmd->infile)
		{
			printf("str = %s\n", all->line->each_cmd->infile->str);
			printf("infile = %d\n", all->line->each_cmd->infile->is_infile);
			printf("outfile = %d\n", all->line->each_cmd->infile->is_outfile);
			printf("heredoc = %d\n", all->line->each_cmd->infile->is_heredoc);
			printf("append = %d\n", all->line->each_cmd->infile->is_append);
			all->line->each_cmd->infile = all->line->each_cmd->infile->next;
		}
		while (all->line->each_cmd->outfile)
		{
			printf("str = %s\n", all->line->each_cmd->outfile->str);
			printf("infile = %d\n", all->line->each_cmd->outfile->is_infile);
			printf("outfile = %d\n", all->line->each_cmd->outfile->is_outfile);
			printf("heredoc = %d\n", all->line->each_cmd->outfile->is_heredoc);
			printf("append = %d\n", all->line->each_cmd->outfile->is_append);
			all->line->each_cmd->outfile = all->line->each_cmd->outfile->next;
		}
		printf("\n");
		all->line->each_cmd = all->line->each_cmd->next;
	}
	
	// while (all->line->each_cmd->infile)
	// {
	// 	printf("str = %s\n", all->line->each_cmd->infile->str);
	// 	printf("infile = %d\n", all->line->each_cmd->infile->is_infile);
	// 	printf("outfile = %d\n", all->line->each_cmd->infile->is_outfile);
	// 	printf("heredoc = %d\n", all->line->each_cmd->infile->is_heredoc);
	// 	printf("append = %d\n", all->line->each_cmd->infile->is_append);
	// 	all->line->each_cmd->infile = all->line->each_cmd->infile->next;
	// }
}
