# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ellucas <ellucas@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/07 15:14:40 by ellucas           #+#    #+#              #
#    Updated: 2025/03/12 14:37:34 by ellucas          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
PRINTF_DIR = printf/
GNL_DIR = gnl/
SECURE_DIR = secure/

PRINTF_SRCS = \
    ft_printf.c ft_printchar.c ft_printint.c ft_printstr.c \
    ft_uprintnbr.c ft_printhex_lower.c ft_printhex_up.c ft_printptr.c

GNL_SRCS = \
	get_next_line.c

SOURCES = \
	ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c \
	ft_strlen.c ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c \
	ft_strlcpy.c ft_strlcat.c ft_toupper.c ft_tolower.c ft_strchr.c \
	ft_strrchr.c ft_strncmp.c ft_memchr.c ft_memcmp.c ft_strnstr.c ft_atoi.c \
	ft_calloc.c ft_strdup.c ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c \
	ft_itoa.c ft_strmapi.c ft_striteri.c ft_putchar_fd.c ft_putstr_fd.c \
	ft_putendl_fd.c ft_putnbr_fd.c

BSOURCES = \
	ft_lstnew_bonus.c ft_lstadd_front_bonus.c ft_lstsize_bonus.c ft_lstlast_bonus.c ft_lstadd_back_bonus.c \
	ft_lstdelone_bonus.c ft_lstclear_bonus.c ft_lstiter_bonus.c ft_lstmap_bonus.c

PRINTF_SRCS := $(addprefix $(PRINTF_DIR), $(PRINTF_SRCS))
GNL_SRCS := $(addprefix $(GNL_DIR), $(GNL_SRCS))

OBJECTS = $(SOURCES:.c=.o)
BOBJECTS = $(BSOURCES:.c=.o)
PRINTF_OBJS = $(PRINTF_SRCS:.c=.o)
GNL_OBJS = $(GNL_SRCS:.c=.o)

CC = gcc
CFLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJECTS) $(PRINTF_OBJS) $(GNL_OBJS)
	$(AR) -r $@ $?

bonus: $(OBJECTS) $(BOBJECTS)
	$(AR) -r $(NAME) $?

$(PRINTF_DIR)%.o: $(PRINTF_DIR)%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(GNL_DIR)%.o: $(GNL_DIR)%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Création du dossier sécurisé
secure: $(NAME)
	@mkdir -p $(SECURE_DIR)
	@cp $(NAME) $(SECURE_DIR)
	@cp libft.h $(SECURE_DIR)
#	@echo "Bibliothèque sécurisée créée dans $(SECURE_DIR)"

clean:
	rm -f $(OBJECTS) $(BOBJECTS) $(PRINTF_OBJS) $(GNL_OBJS)

fclean: clean
	rm -f $(NAME)
	rm -rf $(SECURE_DIR)

#fclean_secure: fclean
#	rm -rf $(SECURE_DIR)

re: fclean all

.PHONY: all bonus clean fclean re secure