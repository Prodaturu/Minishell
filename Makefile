# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: trosinsk <trosinsk@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/06 13:33:58 by sprodatu          #+#    #+#              #
#    Updated: 2024/05/27 21:15:49 by trosinsk         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.silent:

NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror #-g -fsanitize=address
LDFLAGS = -L./libft -lft -lreadline

LIBFT = libft/libft.a
LIBFT_DIR = libft

SRCS = minishell.c \
		signals/signal_handler.c \
		parsing/parse.c parsing/lexing.c parsing/tokenizer.c parsing/tokenizer_helper.c \
		parsing/commands.c parsing/commands_helper.c parsing/syntax_check.c \
		parsing/expand.c parsing/expand_utils.c parsing/expand_utils_helper.c \
		parsing/redirections.c parsing/redirection_helper.c \
		parsing/h_doc.c \
		executor/builtins.c \
		executor/executor.c \
		executor/executor_utils.c \
		executor/ft_execve.c \
		executor/multi_exec.c \
		executor/simple_exec.c \
		executor/ft_cd.c \
		executor/ft_cd_utils.c \
		executor/ft_echo.c \
		executor/ft_env.c \
		executor/ft_exit.c \
		executor/ft_export.c \
		executor/ft_export_utils.c \
		executor/ft_pwd.c \
		executor/ft_unset.c \
		executor/save_env_in_struct.c \

OBJS = $(SRCS:.c=.o)

all: $(LIBFT) $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LDFLAGS)

$(LIBFT):
	@echo "Making Libft..."
	make -sC $(LIBFT_DIR)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@
	
clean:
	rm -f $(OBJS) $(LIBFT_DIR)/*.o
	@make -sC $(LIBFT_DIR) clean
	
fclean: clean
	rm -f $(NAME)
	@make -sC $(LIBFT_DIR) fclean

re: fclean all

ac: all clean

.PHONY: all clean fclean re
