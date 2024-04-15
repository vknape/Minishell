
#include "minishell.h"

char	*get_current_dir(void)
{
	size_t	buf_size;
	char	*buf;
	char	*ptr;

	buf_size = 1024;
	buf = malloc(buf_size);
	if (!buf)
	{
		perror("malloc failed");
		exit(EXIT_FAILURE);
	}
	ptr = getcwd(buf, buf_size);
	if (!ptr)
	{
		 perror("getcwd failed");
		exit(EXIT_FAILURE);
	}
	printf("path is (%s)\n", buf);
	return (ptr);
}

void	change_directory(char *dir)
{
	if (access(dir, F_OK) == -1)
		perror("chdir() error");
	// if (chdir(dir) == -1)
	// 	perror("chdir() error");
	else
		get_current_dir();
}
