
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
	bool	is_heredoc;
	bool	is_infile;
	bool	is_outfile;
	bool	is_append;
	char	*lim;
	struct s_chunk *next;
}	t_chunk;

typedef struct s_pipex
{
	t_chunk	*delimiter;
	t_chunk	*infile;
	t_chunk	*outfile;
	char	**cmd;
	char 	*templine;
	bool	is_builtin;
	// bool	is_infile;
	// bool	is_outfile;
	// bool	is_heredoc;
	// bool	is_append;
	struct s_pipex	*next;

}	t_cmd;

typedef struct s_line
{
	int		invalid;
	int		total_cmd;
	char	**splits;
	char	*saved_line;
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
int		check_input(char *curline, t_all *all);
void	make_envp_and_set(t_all *all, char *envp[]);
void	make_export(t_all *all, char *envp[]);

// char	*get_current_dir(void);
// void	change_directory(char *dir);
// char	**ft_split_until(char const *s, char c, int max_position);
// char	**ft_split_quotes(char const *s, char c);
// t_chunk	*ft_lstnewchunk(char *str);
// t_chunk	*ft_lstlast_chunk(t_chunk *lst);
// void	ft_lstadd_back_chunk(t_chunk **lst, t_chunk *new);
// char	*join_line_after_quotes(char *curline, t_all *all);
// int		check_meta(t_all *all, char *curline);

// list of link list t_cmd
t_cmd	*ft_lstnewcmd(void);
t_cmd	*ft_lstlast_cmd(t_cmd *lst);
void	ft_lstadd_back_cmd(t_cmd **lst, t_cmd *new);
void	lstclear_cmd(t_cmd **lst);

// list of link list t_chunk
t_chunk	*ft_lstnewchunk(char *str);
t_chunk	*ft_lstlast_chunk(t_chunk *lst);
void	ft_lstadd_back_chunk(t_chunk **lst, t_chunk *new);
void	lstclear(t_chunk **lst);

// list of function of fill_each_cmd
//void	split_cmds(char *curline, t_all *all);
void	split_cmd_nodes(t_all *all);

//parsing utils
int	check_space(char *str);
char	**ft_split_quotes(char const *s, char c);

// bultins function
//void	ft_echo(t_all *all, char **str);
void	ft_echo_quotes(t_all *all, char **array_str);
char	*get_current_dir(void);
void	ft_env(t_all *all);
void	ft_cd(t_all *all);
void	ft_unset(t_all *all, char *str);
void	ft_export(t_all	*all);
void	sorter_export(t_all *all);

#endif