
#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <signal.h>
# include <stdlib.h>
# include <string.h>
# include <fcntl.h>
# include <errno.h>
# include "libft/libft.h"
# include <stdbool.h>

typedef struct s_all
{
	t_line	*line;
	char	*lastwd;
}	t_all;

typedef struct s_line
{
	int		total_cmd;
	t_cmd	*each_cmd;
}	t_line;

typedef struct s_pipex
{
	char	*delimiter;
	char	**infile;
	char	**outfile;
	char	*cmd;
	char	**flag;
	bool	is_builtin;
	bool	is_infile;
	bool	is_heredoc;
}	t_cmd;

int		main(int argc, char **argv, char **envm);

char	*get_current_dir(void);
void	change_directory(char *dir);


#endif
