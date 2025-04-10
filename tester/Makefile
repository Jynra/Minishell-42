# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ellucas <ellucas@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/10 09:09:40 by ellucas           #+#    #+#              #
#    Updated: 2025/04/10 09:09:43 by ellucas          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Nom de l'exécutable de test
NAME_TEST = minishell_tester

# Compilateur et flags
CC = gcc
CFLAGS = -Wall -Wextra -Werror
INCLUDES = -I ../includes

# Dossiers
SRC_DIR = ../src
OBJ_DIR = obj
LIBFT_DIR = ../includes/libft

# Librairies
LIBS = -lreadline -L $(LIBFT_DIR) -lft

# Sources du testeur
TEST_SRC = minishell_tester.c

# Sources du projet original nécessaires pour les tests
PROJECT_SRC = $(SRC_DIR)/executor/executor.c \
			$(SRC_DIR)/executor/builtins/builtins.c \
			$(SRC_DIR)/executor/builtins/echo.c \
			$(SRC_DIR)/executor/pipex/pipes.c \
			$(SRC_DIR)/executor/pipex/process.c \
			$(SRC_DIR)/executor/pipex/path.c \
			$(SRC_DIR)/utils/errors.c

# Objets
TEST_OBJ = $(OBJ_DIR)/minishell_tester.o
PROJECT_OBJ = $(PROJECT_SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# Règles
all: $(NAME_TEST)

$(NAME_TEST): make_libft $(TEST_OBJ) $(PROJECT_OBJ)
	$(CC) $(CFLAGS) $(TEST_OBJ) $(PROJECT_OBJ) $(LIBS) -o $(NAME_TEST)

# Création des dossiers pour les objets et compilation
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Compilation du fichier de test
$(TEST_OBJ): $(TEST_SRC)
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
	@rm -f $(NAME_TEST)

re: fclean all

run: $(NAME_TEST)
	./$(NAME_TEST)

.PHONY: all clean fclean re make_libft run