# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: enschnei <enschnei@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/29 17:54:19 by dsatge            #+#    #+#              #
#    Updated: 2025/04/04 12:45:45 by enschnei         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

C_FILES = main.c\
			exec.c\
			free.c\
			list.c\
			error.c\
			ft_cd.c\
			expand.c\
			ft_env.c\
			ft_pwd.c\
			ft_echo.c\
			ft_exit.c\
			heredoc.c\
			ft_unset.c\
			tokenise.c\
			ft_export.c\
			exec_init.c\
			exec_utils.c\
			exec_redir.c\
			line_to_words.c\
			tokenise_utils.c\
			print_test_list.c\
			signal_handling.c\
			builtins_handling.c\
			line_to_words_utils.c\

BOLD = \033[1m
RED = \033[31m
RESET = \033[0m
BLACK  = \033[30m
GREEN  = \033[32m
YELLOW = \033[33m
BLUE   = \033[34m
MAGENTA= \033[35m
CYAN   = \033[36m
WHITE  = \033[37m

SRCS = $(addprefix src/, $(C_FILES))

CFLAGS = -Wall -Wextra -Werror -I includes/ -g

LIB = libft/libft.a printf/libftprintf.a

DEPS = $(addprefix lib/,${LIB})

all: ${NAME}

$(NAME): $(SRCS)
	@echo "$(BOLD)$(RED)Compilation des libs...$(RESET)"
	@$(MAKE) --no-print-directory -C lib/libft
	@echo "$(BLUE)////////////////////////////////$(RESET)"
	@echo "$(BLUE)||$(RESET)$(GREEN)compilation de la libft fini$(RESET)$(BLUE)||$(RESET)"
	@echo "$(BLUE)////////////////////////////////$(RESET)"
	@$(MAKE) --no-print-directory -C lib/printf
	@echo "$(BLUE)////////////////////////////////$(RESET)"
	@echo "$(BLUE)|||$(RESET)$(GREEN)compilation de Printf fini$(RESET)$(BLUE)|||$(RESET)"
	@echo "$(BLUE)////////////////////////////////$(RESET)"
	@echo "$(BOLD)$(RED)Creation de $(NAME)...$(RESET)"
	@cc $(CFLAGS) $(SRCS) -o $(NAME) $(DEPS) -lreadline
	@echo "$(BOLD)$(YELLOW) COMPILATION TERMINE $(RESET)"

clean:
	@echo "$(RED)Cleaning up object files...$(RESET)"
	@$(MAKE) --no-print-directory -C lib/libft fclean
	@$(MAKE) --no-print-directory -C lib/printf fclean

fclean: clean
	@echo "Removing executable..."
	@rm -rf $(NAME)

re:	fclean all

.PHONY: all clean fclean re