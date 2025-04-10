/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_tester.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ellucas <ellucas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 09:09:32 by ellucas           #+#    #+#             */
/*   Updated: 2025/04/10 09:09:47 by ellucas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include "../includes/minishell.h"
#include "../includes/executor.h"

/*
** Fonction utilitaire pour créer une commande simple
*/
t_simple_command *create_test_simple_command(char **args, int argc)
{
	t_simple_command *cmd;
	int i;

	cmd = (t_simple_command *)malloc(sizeof(t_simple_command));
	if (!cmd)
		return (NULL);
	
	cmd->_numberOfArguments = argc;
	cmd->_numberOfAvailableArguments = argc + 5; // Un peu plus pour être sûr
	cmd->_arguments = (char **)malloc(sizeof(char *) * (cmd->_numberOfAvailableArguments));
	
	if (!cmd->_arguments)
	{
		free(cmd);
		return (NULL);
	}
	
	i = 0;
	while (i < argc)
	{
		cmd->_arguments[i] = strdup(args[i]);
		if (!cmd->_arguments[i])
		{
			// Nettoyage en cas d'erreur
			while (--i >= 0)
				free(cmd->_arguments[i]);
			free(cmd->_arguments);
			free(cmd);
			return (NULL);
		}
		i++;
	}
	cmd->_arguments[i] = NULL; // Terminaison NULL
	
	return (cmd);
}

/*
** Fonction utilitaire pour créer une commande complète
*/
t_command *create_test_command(void)
{
	t_command *cmd;
	
	cmd = (t_command *)malloc(sizeof(t_command));
	if (!cmd)
		return (NULL);
	
	cmd->_numberOfSimpleCommands = 0;
	cmd->_numberOfAvailableSimpleCommands = 10; // Pré-allouer de l'espace
	cmd->_simpleCommands = (t_simple_command **)malloc(sizeof(t_simple_command *) * cmd->_numberOfAvailableSimpleCommands);
	
	if (!cmd->_simpleCommands)
	{
		free(cmd);
		return (NULL);
	}
	
	cmd->_outFile = NULL;
	cmd->_inputFile = NULL;
	cmd->_errFile = NULL;
	cmd->_background = 0;
	cmd->_append = 0;
	
	return (cmd);
}

/*
** Fonction pour ajouter une commande simple à une commande
*/
void add_simple_command_to_test(t_command *cmd, t_simple_command *simple_cmd)
{
	if (cmd->_numberOfSimpleCommands >= cmd->_numberOfAvailableSimpleCommands)
	{
		// Réallouer si nécessaire
		cmd->_numberOfAvailableSimpleCommands *= 2;
		cmd->_simpleCommands = realloc(cmd->_simpleCommands, 
			sizeof(t_simple_command *) * cmd->_numberOfAvailableSimpleCommands);
		if (!cmd->_simpleCommands)
			return;
	}
	
	cmd->_simpleCommands[cmd->_numberOfSimpleCommands] = simple_cmd;
	cmd->_numberOfSimpleCommands++;
}

/*
** Fonction utilitaire pour nettoyer une commande
*/
void clean_test_command(t_command *cmd)
{
	int i, j;
	
	if (!cmd)
		return;
	
	// Libérer les commandes simples
	for (i = 0; i < cmd->_numberOfSimpleCommands; i++)
	{
		if (cmd->_simpleCommands[i])
		{
			// Libérer les arguments
			for (j = 0; j < cmd->_simpleCommands[i]->_numberOfArguments; j++)
			{
				if (cmd->_simpleCommands[i]->_arguments[j])
					free(cmd->_simpleCommands[i]->_arguments[j]);
			}
			free(cmd->_simpleCommands[i]->_arguments);
			free(cmd->_simpleCommands[i]);
		}
	}
	
	free(cmd->_simpleCommands);
	
	// Libérer les fichiers de redirection
	if (cmd->_outFile)
		free(cmd->_outFile);
	if (cmd->_inputFile)
		free(cmd->_inputFile);
	if (cmd->_errFile)
		free(cmd->_errFile);
	
	free(cmd);
}

/*
** Fonction utilitaire pour afficher une commande
*/
void print_test_command(t_command *cmd)
{
	int i, j;
	
	printf("===== DÉTAILS DE LA COMMANDE =====\n");
	printf("Nombre de commandes simples: %d\n", cmd->_numberOfSimpleCommands);
	
	for (i = 0; i < cmd->_numberOfSimpleCommands; i++)
	{
		printf("Commande simple #%d:\n", i + 1);
		printf("  Arguments: ");
		for (j = 0; j < cmd->_simpleCommands[i]->_numberOfArguments; j++)
		{
			printf("'%s' ", cmd->_simpleCommands[i]->_arguments[j]);
		}
		printf("\n");
	}
	
	printf("Redirection entrée: %s\n", cmd->_inputFile ? cmd->_inputFile : "stdin (défaut)");
	printf("Redirection sortie: %s\n", cmd->_outFile ? cmd->_outFile : "stdout (défaut)");
	printf("Redirection erreur: %s\n", cmd->_errFile ? cmd->_errFile : "stderr (défaut)");
	printf("Mode append: %s\n", cmd->_append ? "Oui" : "Non");
	printf("Arrière-plan: %s\n", cmd->_background ? "Oui" : "Non");
	printf("=================================\n\n");
}

/*
** Fonction utilitaire pour créer un fichier de test avec contenu
*/
int create_test_file(const char *filename, const char *content)
{
	int fd;
	
	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		perror("Erreur lors de la création du fichier de test");
		return (0);
	}
	
	if (content)
		write(fd, content, strlen(content));
	
	close(fd);
	return (1);
}

/*
** Test simple : une seule commande
*/
void test_single_command(void)
{
	t_command *cmd;
	t_simple_command *simple_cmd;
	char *args[] = {"ls", "-la"};
	
	printf("==== TEST 1: COMMANDE SIMPLE (ls -la) ====\n");
	
	cmd = create_test_command();
	if (!cmd)
	{
		fprintf(stderr, "Erreur lors de la création de la commande\n");
		return;
	}
	
	simple_cmd = create_test_simple_command(args, 2);
	if (!simple_cmd)
	{
		fprintf(stderr, "Erreur lors de la création de la commande simple\n");
		clean_test_command(cmd);
		return;
	}
	
	add_simple_command_to_test(cmd, simple_cmd);
	
	print_test_command(cmd);
	
	printf("Exécution de la commande...\n");
	execute_command(cmd);
	
	printf("Commande exécutée.\n\n");
	
	clean_test_command(cmd);
}

/*
** Test redirection de sortie
*/
void test_output_redirection(void)
{
	t_command *cmd;
	t_simple_command *simple_cmd;
	char *args[] = {"ls", "-la"};
	
	printf("==== TEST 2: REDIRECTION DE SORTIE (ls -la > test_output.txt) ====\n");
	
	cmd = create_test_command();
	if (!cmd)
	{
		fprintf(stderr, "Erreur lors de la création de la commande\n");
		return;
	}
	
	simple_cmd = create_test_simple_command(args, 2);
	if (!simple_cmd)
	{
		fprintf(stderr, "Erreur lors de la création de la commande simple\n");
		clean_test_command(cmd);
		return;
	}
	
	add_simple_command_to_test(cmd, simple_cmd);
	cmd->_outFile = strdup("test_output.txt");
	
	print_test_command(cmd);
	
	printf("Exécution de la commande...\n");
	execute_command(cmd);
	
	printf("Commande exécutée. Vérifiez le contenu de test_output.txt\n\n");
	
	clean_test_command(cmd);
}

/*
** Test redirection d'entrée
*/
void test_input_redirection(void)
{
	t_command *cmd;
	t_simple_command *simple_cmd;
	char *args[] = {"cat"};
	const char *test_content = "Ceci est un fichier de test.\nIl contient quelques lignes.\nPour tester la redirection.\n";
	
	printf("==== TEST 3: REDIRECTION D'ENTRÉE (cat < test_input.txt) ====\n");
	
	// Création du fichier de test
	if (!create_test_file("test_input.txt", test_content))
	{
		return;
	}
	
	cmd = create_test_command();
	if (!cmd)
	{
		fprintf(stderr, "Erreur lors de la création de la commande\n");
		return;
	}
	
	simple_cmd = create_test_simple_command(args, 1);
	if (!simple_cmd)
	{
		fprintf(stderr, "Erreur lors de la création de la commande simple\n");
		clean_test_command(cmd);
		return;
	}
	
	add_simple_command_to_test(cmd, simple_cmd);
	cmd->_inputFile = strdup("test_input.txt");
	
	print_test_command(cmd);
	
	printf("Exécution de la commande...\n");
	execute_command(cmd);
	
	printf("Commande exécutée.\n\n");
	
	clean_test_command(cmd);
}

/*
** Test pipe simple
*/
void test_simple_pipe(void)
{
	t_command *cmd;
	t_simple_command *simple_cmd1, *simple_cmd2;
	char *args1[] = {"ls", "-la"};
	char *args2[] = {"grep", "tester"};
	
	printf("==== TEST 4: PIPE SIMPLE (ls -la | grep tester) ====\n");
	
	cmd = create_test_command();
	if (!cmd)
	{
		fprintf(stderr, "Erreur lors de la création de la commande\n");
		return;
	}
	
	simple_cmd1 = create_test_simple_command(args1, 2);
	if (!simple_cmd1)
	{
		fprintf(stderr, "Erreur lors de la création de la première commande simple\n");
		clean_test_command(cmd);
		return;
	}
	
	simple_cmd2 = create_test_simple_command(args2, 2);
	if (!simple_cmd2)
	{
		fprintf(stderr, "Erreur lors de la création de la deuxième commande simple\n");
		free(simple_cmd1);
		clean_test_command(cmd);
		return;
	}
	
	add_simple_command_to_test(cmd, simple_cmd1);
	add_simple_command_to_test(cmd, simple_cmd2);
	
	print_test_command(cmd);
	
	printf("Exécution de la commande...\n");
	execute_command(cmd);
	
	printf("Commande exécutée.\n\n");
	
	clean_test_command(cmd);
}

/*
** Test pipe multiple
*/
void test_multiple_pipe(void)
{
	t_command *cmd;
	t_simple_command *cmd1, *cmd2, *cmd3;
	char *args1[] = {"ls", "-la"};
	char *args2[] = {"grep", ".c"};
	char *args3[] = {"wc", "-l"};
	
	printf("==== TEST 5: PIPE MULTIPLE (ls -la | grep .c | wc -l) ====\n");
	
	cmd = create_test_command();
	if (!cmd)
	{
		fprintf(stderr, "Erreur lors de la création de la commande\n");
		return;
	}
	
	cmd1 = create_test_simple_command(args1, 2);
	cmd2 = create_test_simple_command(args2, 2);
	cmd3 = create_test_simple_command(args3, 2);
	
	if (!cmd1 || !cmd2 || !cmd3)
	{
		fprintf(stderr, "Erreur lors de la création des commandes\n");
		if (cmd1) free(cmd1);
		if (cmd2) free(cmd2);
		if (cmd3) free(cmd3);
		clean_test_command(cmd);
		return;
	}
	
	add_simple_command_to_test(cmd, cmd1);
	add_simple_command_to_test(cmd, cmd2);
	add_simple_command_to_test(cmd, cmd3);
	
	print_test_command(cmd);
	
	printf("Exécution de la commande...\n");
	execute_command(cmd);
	
	printf("Commande exécutée.\n\n");
	
	clean_test_command(cmd);
}

/*
** Test redirection avec pipe
*/
void test_redirection_with_pipe(void)
{
	t_command *cmd;
	t_simple_command *cmd1, *cmd2;
	char *args1[] = {"cat", "test_input.txt"};
	char *args2[] = {"grep", "test"};
	const char *test_content = "Ceci est un fichier de test.\nIl ne contient pas le mot test ici.\nMais il contient test sur cette ligne.\n";
	
	printf("==== TEST 6: REDIRECTION AVEC PIPE (cat test_input.txt | grep test > result.txt) ====\n");
	
	// Création du fichier de test
	if (!create_test_file("test_input.txt", test_content))
	{
		return;
	}
	
	cmd = create_test_command();
	if (!cmd)
	{
		fprintf(stderr, "Erreur lors de la création de la commande\n");
		return;
	}
	
	cmd1 = create_test_simple_command(args1, 2);
	cmd2 = create_test_simple_command(args2, 2);
	
	if (!cmd1 || !cmd2)
	{
		fprintf(stderr, "Erreur lors de la création des commandes\n");
		if (cmd1) free(cmd1);
		if (cmd2) free(cmd2);
		clean_test_command(cmd);
		return;
	}
	
	add_simple_command_to_test(cmd, cmd1);
	add_simple_command_to_test(cmd, cmd2);
	cmd->_outFile = strdup("result.txt");
	
	print_test_command(cmd);
	
	printf("Exécution de la commande...\n");
	execute_command(cmd);
	
	printf("Commande exécutée. Vérifiez le contenu de result.txt\n\n");
	
	clean_test_command(cmd);
}

/*
** Test commande en arrière-plan
*/
void test_background_command(void)
{
	t_command *cmd;
	t_simple_command *simple_cmd;
	char *args[] = {"sleep", "3"};
	
	printf("==== TEST 7: COMMANDE EN ARRIÈRE-PLAN (sleep 3 &) ====\n");
	
	cmd = create_test_command();
	if (!cmd)
	{
		fprintf(stderr, "Erreur lors de la création de la commande\n");
		return;
	}
	
	simple_cmd = create_test_simple_command(args, 2);
	if (!simple_cmd)
	{
		fprintf(stderr, "Erreur lors de la création de la commande simple\n");
		clean_test_command(cmd);
		return;
	}
	
	add_simple_command_to_test(cmd, simple_cmd);
	cmd->_background = 1;
	
	print_test_command(cmd);
	
	printf("Exécution de la commande...\n");
	execute_command(cmd);
	
	printf("La commande a été lancée en arrière-plan.\n");
	printf("Continuons sans attendre...\n\n");
	
	clean_test_command(cmd);
}

/*
** Test erreurs
*/
void test_command_errors(void)
{
	t_command *cmd;
	t_simple_command *simple_cmd;
	char *args[] = {"commande_inexistante", "arg1"};
	
	printf("==== TEST 8: GESTION DES ERREURS (commande inexistante) ====\n");
	
	cmd = create_test_command();
	if (!cmd)
	{
		fprintf(stderr, "Erreur lors de la création de la commande\n");
		return;
	}
	
	simple_cmd = create_test_simple_command(args, 2);
	if (!simple_cmd)
	{
		fprintf(stderr, "Erreur lors de la création de la commande simple\n");
		clean_test_command(cmd);
		return;
	}
	
	add_simple_command_to_test(cmd, simple_cmd);
	
	print_test_command(cmd);
	
	printf("Exécution de la commande...\n");
	execute_command(cmd);
	
	printf("Commande exécutée. Vérifiez la gestion de l'erreur.\n\n");
	
	clean_test_command(cmd);
}

int main(void)
{
	printf("=================================================\n");
	printf("= OUTIL DE TEST POUR L'EXÉCUTEUR DE MINISHELL   =\n");
	printf("=================================================\n\n");
	
	// Exécution des tests
	test_single_command();
	test_output_redirection();
	test_input_redirection();
	test_simple_pipe();
	test_multiple_pipe();
	test_redirection_with_pipe();
	test_background_command();
	test_command_errors();
	
	// Suppression des fichiers de test
	unlink("test_input.txt");
	unlink("test_output.txt");
	unlink("result.txt");
	
	printf("Tous les tests ont été exécutés.\n");
	return (0);
}