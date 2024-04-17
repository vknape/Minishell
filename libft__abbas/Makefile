
sourcefiles = ft_strjoin.c ft_strlen.c ft_strlcpy.c ft_strtrim.c  \
	ft_strdup.c ft_itoa.c ft_putendl_fd.c ft_putchar_fd.c ft_putnbr_fd.c \
	ft_putstr_fd.c ft_strrchr.c ft_striteri.c ft_strlcat.c ft_strmapi.c \
	ft_strncmp.c ft_strnstr.c ft_substr.c ft_tolower.c ft_toupper.c ft_isprint.c \
	ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memmove.c ft_memset.c ft_atoi.c \
	ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c ft_isascii.c ft_split.c \
	ft_isdigit.c ft_strchr.c ft_nbrlength.c ft_void_hex.c ft_printf.c ft_hexnum.c \
	ft_unsigned_nbrlength.c ft_printf_putstr.c ft_printf_putchar.c get_next_line.c \
	get_next_line_utils.c

objects = 	$(sourcefiles:.c=.o)

NAME = 		libft.a

all: 		$(NAME)

$(NAME): 	$(objects)
	ar rcs libft.a $(objects)
%.o: %.c	
	cc -Wall -Wextra -Werror -c $< -o $@

clean:
	rm -f $(objects)
fclean:
	rm -f $(objects) $(NAME)
re: fclean all	
