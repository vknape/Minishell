NAME	= Minishell
FLAGS	=
#FLAGS	= -Wall -Wextra -Werror #-g -fsanitize=address
LIBFTDIR  = ./libft/libft.a
LIBS = -lreadline

#HEADERS   := -I ./include -I $(LIBFTDIR)

SRCS	= main.c builtins.c ft_splite_modified.c ft_split_skip.c
objects	= $(SRCS:.c=.o)

all: $(NAME)

$(LIBFTDIR): 
	@make bonus -C ./libft

$(NAME): 	$(objects) $(LIBFTDIR)
	@cc $(FLAGS) -o $(NAME) $(objects) $(LIBFTDIR) $(LIBS)

%.o: %.c	
	cc -c $< -o $@

clean:
	rm -f $(objects) $(LIBFTDIR)/*.o
	make clean -C ./libft

fclean:	clean
	rm -f $(NAME)
	make fclean -C ./libft

re: fclean all

.PHONY: all clean fclean re