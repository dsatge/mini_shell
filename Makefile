# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: baiannon <baiannon@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/29 17:54:19 by dsatge            #+#    #+#              #
#    Updated: 2025/01/31 18:29:49 by baiannon         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = minishell

SRC_FILES = main.c\
			line_to_words.c\
			line_to_words_utils.c\
			tokenise.c\
			tokenise_utils.c\
			signal_handling.c\
			builtins_handling.c\
			ft_echo.c\
			ft_pwd.c\
			ft_cd.c\
			print_test_list.c\
			free.c\
			list.c\
			exec.c\
			exec_utils.c\
			ft_env.c\
			ft_unset.c\

FLAGS = -Wall -Wextra -Werror -I includes/ -g

LIB = libft/libft.a printf/libftprintf.a

DEPS = $(addprefix lib/,${LIB:%.c=%.o})

SRC = $(addprefix src/,${SRC_FILES})

all: ${NAME}

${NAME} : ${SRC}
	make -C lib/libft
	make -C lib/printf
	cc ${FLAGS} ${SRC} -o ${NAME} ${DEPS} -lreadline

clean:
	make -C lib/libft clean
	make -C lib/printf clean

fclean: clean
	rm -rf ${NAME}

re: fclean all
	make -C lib/libft re
	make -C lib/printf re

.PHONY: all clean fclean re%  