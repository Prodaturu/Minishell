# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sprodatu <sprodatu@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/06 13:33:58 by sprodatu          #+#    #+#              #
#    Updated: 2024/05/26 03:35:41 by sprodatu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.silent:

NAME = minishell

CC = gcc
CFLAGS = -Wall -Wextra -Werror -g -fsanitize=address
LDFLAGS = -L./libft -lft -lreadline

LIBFT = libft/libft.a
LIBFT_DIR = libft

SRCS = minishell.c \
		signals/signal_handler.c \
		parsing/parse.c parsing/lexing.c parsing/tokenizer.c parsing/tokenizer_helper.c \
		parsing/commands.c parsing/commands_helper.c parsing/syntax_check.c \
		parsing/expand.c parsing/expand_utils.c parsing/expand_utils_helper.c \
		parsing/redirections.c parsing/redirection_helper.c \
		parsing/h_doc.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LDFLAGS)

$(LIBFT):
	make -C $(LIBFT_DIR)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@
	
clean:
	rm -f $(OBJS) $(LIBFT_DIR)/*.o
	
fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
