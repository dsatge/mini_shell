# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: enschnei <enschnei@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/29 17:54:19 by dsatge            #+#    #+#              #
#    Updated: 2025/04/21 22:12:49 by enschnei         ###   ########.fr        #
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
			list_utils.c\
			free_utils.c\
			exec_utils_2.c\
			free_heredoc.c\
			exec_inchild.c\
			expand_utils.c\
			line_to_words.c\
			heredoc_utils.c\
			exec_only_cmd.c\
			expand_heredoc.c\
			tokenise_utils.c\
			exec_dup_redir.c\
			only_cmd_utils.c\
			ft_export_utils.c\
			signal_handling.c\
			split_word_utils.c\
			builtins_parents.c\
			exec_redir_types.c\
			builtins_handling.c\
			exec_only_cmd_utils.c\
			line_to_words_utils.c\
			redir_pipe_to_word_utils.c\

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