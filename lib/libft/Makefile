NAME = libft.a

HEADER = includes/libft.h
##################

SRC = ft_isalpha.c\
	ft_memchr.c\
	ft_memset.c\
	ft_strlen.c\
	ft_tolower.c\
	ft_atoi.c\
	ft_atol.c\
	ft_isascii.c\
	ft_memcmp.c\
	ft_strchr.c\
	ft_strncmp.c\
	ft_strcmp.c\
	ft_toupper.c\
	ft_bzero.c\
	ft_freetab.c\
	ft_isdigit.c\
	ft_memcpy.c\
	ft_strlcat.c\
	ft_strnstr.c\
	ft_isalnum.c\
	ft_isprint.c\
	ft_iseven.c\
	ft_memmove.c\
	ft_strlcpy.c\
	ft_strrchr.c\
	ft_calloc.c\
	ft_strdup.c\
	ft_substr.c\
	ft_strjoin.c\
	ft_strtrim.c\
	ft_split.c\
	ft_count_line_split.c\
	ft_putchar_fd.c\
	ft_putstr_fd.c\
	ft_putendl_fd.c\
	ft_putnbr_fd.c\
	ft_itoa.c\
	ft_strmapi.c\
	ft_striteri.c\
	get_next_line.c\
	get_next_line_bonus.c\
	ft_strncpy.c\

CC = cc

OBJ = $(SRC:.c=.o)

FLAGS = -Wall -Wextra -Werror

#########ACTION######################################
all: $(NAME)

$(NAME): 
	@$(CC) $(FLAGS) -c $(SRC)
	@ar -rc $(NAME) $(OBJ)
	@echo "Compiled $(NAME) & .o."

#### Va creer archives
#
#	#$<: the name of the first prerequisite
#	#$^:the name of the first prerequisite separated by spaces
#	#$?: prerequisites newer than the target separated by spaces
#	#$@:call for the name of the executable name

%.o:	%.c
	cc $(FLAGS) -c $< -o $@
#### Va recompiler si .c different du .o

# so:
# 	$(CC) -nostartfiles -fPIC -c $(CFLAGS) $(SRC)
# 	cc -nostartfiles -shared -o libft.so $(OBJ) -ldl

clean:
	@rm -f $(OBJ) 
	@echo "Deleted .o files."

fclean: clean
	@rm -f $(NAME)
	@echo "Deleted $(NAME)."

re: fclean all

.PHONY: all clean fclean re
