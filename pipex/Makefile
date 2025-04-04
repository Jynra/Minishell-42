# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ellucas <ellucas@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/03 14:28:12 by ellucas           #+#    #+#              #
#    Updated: 2025/04/04 00:09:40 by ellucas          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

SRCS_DIR = srcs
INCS_DIR = includes
OBJS_DIR = objs
LIBFT_DIR = $(INCS_DIR)/libft

SRCS = $(SRCS_DIR)/pipex.c \
		$(SRCS_DIR)/process.c \
		$(SRCS_DIR)/errors.c

OBJS = $(OBJS_DIR)/pipex.o \
		$(OBJS_DIR)/process.o \
		$(OBJS_DIR)/errors.o

LIBFT = $(LIBFT_DIR)/libft.a

CC = gcc
CFLAGS = -Wall -Wextra -Werror -I$(INCS_DIR)

all: $(OBJS_DIR) $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -L$(LIBFT_DIR) -lft -o $(NAME)

$(OBJS_DIR):
	mkdir -p $(OBJS_DIR)

$(LIBFT):
	make -C $(LIBFT_DIR)

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c | $(OBJS_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	make -C $(LIBFT_DIR) clean
	rm -rf $(OBJS_DIR)

fclean: clean
	make -C $(LIBFT_DIR) fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re