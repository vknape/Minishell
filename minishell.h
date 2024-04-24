
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

typedef struct s_chunk
{
	char	*str;
	struct s_chunk *next;
}	t_chunk;

typedef struct s_pipex
{
	char	*delimiter;
	char	**infile;
	char	**outfile;
	char	**cmd;
	char 	*templine;
	// char	**flag;
	bool	is_builtin;
	bool	is_infile;
	bool	is_outfile;
	bool	is_heredoc;
	bool	is_append;
	struct s_pipex	*next;

}	t_cmd;

typedef struct s_line
{
	int		invalid;
	int		total_cmd;
	char	**splits;
	t_chunk	*chunks;
	t_cmd	*each_cmd;
}	t_line;

typedef struct s_all
{
	t_line	*line;
	char	*lastwd;
	t_chunk	*envp;
	t_chunk	*export;
	t_chunk	*set;
}	t_all;

int		main(int argc, char **argv, char **envm);

char	*get_current_dir(void);
void	change_directory(char *dir);
char	**ft_split_until(char const *s, char c, int max_position);
char	**ft_split_quotes(char const *s, char c);
t_chunk	*ft_lstnewchunk(char *str);
t_chunk	*ft_lstlast_chunk(t_chunk *lst);
void	ft_lstadd_back_chunk(t_chunk **lst, t_chunk *new);


#endif