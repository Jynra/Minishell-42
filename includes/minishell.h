/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ellucas <ellucas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 15:50:11 by ellucas           #+#    #+#             */
/*   Updated: 2025/04/09 15:50:13 by ellucas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <signal.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>

// Variable globale pour les signaux (limitée à un entier)
extern int g_signal;

/*
** Structure pour les commandes simples
*/
typedef struct s_simple_command
{
    int     _numberOfArguments;       // Nombre d'arguments
    int     _numberOfAvailableArguments; // Taille allouée
    char    **_arguments;             // Arguments (commande + paramètres)
} t_simple_command;

/*
** Structure pour la table de commandes complète
*/
typedef struct s_command
{
    int     _numberOfSimpleCommands;  // Nombre de commandes simples
    int     _numberOfAvailableSimpleCommands; // Taille allouée
    t_simple_command **_simpleCommands; // Tableau des commandes simples
    char    *_outFile;                // Fichier de redirection de sortie
    char    *_inputFile;              // Fichier de redirection d'entrée
    char    *_errFile;                // Fichier de redirection d'erreur
    int     _background;              // 1 si exécution en arrière-plan
    int     _append;                  // 1 si redirection en mode append (>>)
} t_command;

/*
** Fonctions pour t_simple_command
*/
t_simple_command   *create_simple_command(void);
void                add_argument(t_simple_command *cmd, char *argument);
void                free_simple_command(t_simple_command *cmd);

/*
** Fonctions pour t_command
*/
t_command          *create_command(void);
void                add_simple_command(t_command *cmd_table, t_simple_command *simple_cmd);
void                set_input_redirection(t_command *cmd_table, char *file);
void                set_output_redirection(t_command *cmd_table, char *file, int append);
void                set_error_redirection(t_command *cmd_table, char *file);
void                set_background(t_command *cmd_table, int background);
void                free_command(t_command *cmd_table);

/*
** Fonctions principales
*/
void                prompt_loop(void);
void                setup_signals(void);
void                handle_signal(int sig);

/*
** Fonctions du parser
*/
int                 parse_line(char *line, t_command *cmd_table);

/*
** Fonctions de l'executor (prototypes basiques, détails dans executor.h)
*/
int                 execute_command(t_command *cmd);

/*
** Fonctions utilitaires
*/
char                *ft_strdup(const char *s);
char                **ft_split(const char *s, char c);
int                 ft_strcmp(const char *s1, const char *s2);
int                 ft_strncmp(const char *s1, const char *s2, size_t n);
size_t              ft_strlen(const char *s);
void                ft_putchar_fd(char c, int fd);
void                ft_putstr_fd(const char *s, int fd);
void                ft_putendl_fd(const char *s, int fd);
char                *ft_strjoin(char const *s1, char const *s2);
char                *get_next_line(int fd);

#endif