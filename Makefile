# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dsatge <dsatge@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/29 17:54:19 by dsatge            #+#    #+#              #
#    Updated: 2024/10/29 17:56:48 by dsatge           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRC_FILES = main.c\

FLAGS = -Wall -Wextra -Werror -I includes/ -g

LIB = libft/libft.a printf/libftprintf.a

DEPS = $(addprefix lib/,${LIB:%.c=%.o})

SRC = $(addprefix src/,${SRC_FILES})

all: ${NAME}

${NAME} : ${SRC}
	make -C lib/libft
	make -C lib/printf
	cc ${FLAGS} ${SRC} -o ${NAME} ${DEPS}

clean:
	make -C lib/libft clean
	make -C lib/printf clean

fclean: clean
	rm -rf ${NAME}

re: fclean all
	make -C lib/libft re
	make -C lib/printf re

.PHONY: all clean fclean re%  