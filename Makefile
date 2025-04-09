# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ellucas <ellucas@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/09 15:52:25 by ellucas           #+#    #+#              #
#    Updated: 2025/04/09 23:50:38 by ellucas          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Nom de l'exécutable
NAME = minishell

# Compilateur et flags
CC = gcc
CFLAGS = -Wall -Wextra -Werror
INCLUDES = -I ./includes

# Dossiers
SRC_DIR = src
OBJ_DIR = obj
LIBFT_DIR = includes/libft

# Librairies
LIBS = -lreadline -L $(LIBFT_DIR) -lft

# Sources
SRC_FILES = main.c \
			$(SRC_DIR)/executor/executor.c \
			$(SRC_DIR)/executor/builtins/builtins.c \
			$(SRC_DIR)/executor/builtins/echo.c \
			$(SRC_DIR)/executor/pipex/pipes.c \
			$(SRC_DIR)/executor/pipex/process.c \
			$(SRC_DIR)/executor/pipex/path.c \
			$(SRC_DIR)/utils/errors.c \
#			$(SRC_DIR)/parser/parser.c \
			$(SRC_DIR)/parser/lexer.c \
			$(SRC_DIR)/parser/command.c \
			$(SRC_DIR)/executor/builtins/cd.c \
			$(SRC_DIR)/executor/builtins/pwd.c \
			$(SRC_DIR)/executor/builtins/export.c \
			$(SRC_DIR)/executor/builtins/unset.c \
			$(SRC_DIR)/executor/builtins/env.c \
			$(SRC_DIR)/executor/builtins/exit.c \
			$(SRC_DIR)/utils/signals.c \

# Objets
OBJ_FILES = $(SRC_FILES:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
# Ajout du dossier racine pour main.c
MAIN_OBJ = $(OBJ_DIR)/main.o

# Règles
all: $(NAME)

$(NAME): make_libft $(OBJ_FILES) $(MAIN_OBJ)
	$(CC) $(CFLAGS) $(OBJ_FILES) $(LIBS) -o $(NAME)

# Création des dossiers pour les objets et compilation
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Compilation de main.c qui est à la racine
$(MAIN_OBJ): main.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Compilation de libft
make_libft:
	@make -C $(LIBFT_DIR)

clean:
	@make -C $(LIBFT_DIR) clean
	@rm -rf $(OBJ_DIR)

fclean: clean
	@make -C $(LIBFT_DIR) fclean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re make_libft