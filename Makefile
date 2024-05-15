# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sprodatu <sprodatu@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/06 13:33:58 by sprodatu          #+#    #+#              #
#    Updated: 2024/05/15 08:42:51 by sprodatu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.silent:

NAME = minishell

CC = gcc
CFLAGS = -Wall -Wextra -Werror
LDFLAGS = -L./libft -lft -lreadline

LIBFT = libft/libft.a
LIBFT_DIR = libft

SRCS = minishell.c \
		signals/signal_handler.c \
		parsing/parse.c parsing/lexing.c parsing/token_redirect.c \

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(OBJS) -o $(NAME) $(LDFLAGS)

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
