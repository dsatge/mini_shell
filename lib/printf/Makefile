NAME = libftprintf.a

SRCS = ft_adress.c\
		ft_hexputnbr.c\
		ft_printf.c\
		ft_putchar.c\
		ft_putnbr.c\
		ft_putstr.c\
		ft_putunnbr.c\
					
OBJS =          ${SRCS:.c=.o}

CFLAGS =        -Wall -Wextra -Werror

all:            ${NAME}

${NAME}:
	@$(CC) $(CFLAGS) -c $(SRCS)
	@ar -rc $(NAME) $(OBJS)
	@echo "Compiled $(NAME) & .o."

${OBJS_BONUS}:
				cc ${CFLAGS} -c -I.

${OBJS}:
				cc ${CFLAGS} ${SRCS} -c -I.

clean:
	@rm -f $(OBJS) 
	@echo "Deleted .o files."

fclean:  		clean
	@rm -f $(NAME)
	@echo "Deleted $(NAME)."

re:             fclean all

.PHONY:         all clean fclean re