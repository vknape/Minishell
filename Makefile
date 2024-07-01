NAME	= Minishell
FLAGS	= -g #-fsanitize=address
# FLAGS	= -Wall -Wextra -Werror -g -fsanitize=address
LIBFTDIR  = ./libft/libft.a
LIBS = -lreadline

#HEADERS   := -I ./include -I $(LIBFTDIR)

SRCS	= sources/main.c sources/builtins.c sources/link_list_chunk.c sources/link_list_chunk2.c sources/link_list_cmd.c sources/check_input.c \
		sources/fill_each_cmd.c sources/ft_split_skip.c sources/envp.c sources/exec.c sources/access.c sources/expaneded.c\
		sources/remove_whitespace_quotes.c sources/ft_signal.c sources/free.c sources/utils1.c sources/builtins_env_pwd_exit.c \
		sources/builtins_cd.c sources/builtins_echo_value_dollar.c sources/builtins_export.c sources/builtins_export2.c \
		sources/exec_check_heredoc.c sources/exec_heredoc_text.c sources/exec_handle_file.c sources/exec_start_fork.c sources/free2.c sources/free3.c
objects	= $(SRCS:.c=.o)

all: $(NAME)

$(LIBFTDIR): 
	@make bonus -C ./libft

$(NAME): 	$(objects) $(LIBFTDIR)
	@cc $(FLAGS) -o $(NAME) $(objects) $(LIBFTDIR) $(LIBS)

sources%.o: sources%.c	
	cc $(FLAGS) -c $< -o $@

clean:
	rm -f $(objects) $(LIBFTDIR)/*.o
	make clean -C ./libft

fclean:	clean
	rm -f $(NAME)
	make fclean -C ./libft

re: fclean all

test:
	bash ./tester/run.sh

.PHONY: all clean fclean re