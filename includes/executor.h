/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ellucas <ellucas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 15:33:05 by ellucas           #+#    #+#             */
/*   Updated: 2025/04/09 15:49:35 by ellucas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "minishell.h"  // Inclure le header principal de minishell
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <signal.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>

/*
** Structure pour l'executor - adapté de pipex
*/
typedef struct s_executor
{
	int		infile;         // descripteur de fichier pour l'entrée
	int		outfile;        // descripteur de fichier pour la sortie
	int		errfile;        // descripteur de fichier pour stderr
	int		**pipes;        // tableau de pipes pour connecter les commandes
	char	***cmds_args;   // tableau d'arguments pour chaque commande
	char	**cmds_paths;   // chemins exécutables pour chaque commande
	pid_t	*pids;          // PIDs des processus enfants
	int		cmd_count;      // nombre de commandes à exécuter
	int		here_doc;       // flag pour here_doc
	char	*limiter;       // délimiteur pour here_doc
	char	**envp;         // variables d'environnement
	int		background;     // exécution en arrière-plan (&)
	int		exit_status;    // code de sortie de la dernière commande
}	t_executor;

/*
** Fonctions principales d'exécution
*/
int		execute_command(t_command *cmd);
void	free_executor(t_executor *executor);

/*
** Fonctions de gestion des pipes et processus (adaptées de pipex)
*/
void	create_pipes(t_executor *exec);
void	child_process(t_executor *exec, int i);
char	*find_path(char *cmd, char **envp);
void	here_doc_input(t_executor *exec);

/*
** Fonctions pour les commandes intégrées (builtins)
*/
int		is_builtin(char *cmd);
int		execute_builtin(char **args, t_executor *exec);
int		builtin_echo(char **args);
int		builtin_cd(char **args);
int		builtin_pwd(void);
int		builtin_export(char **args, char ***envp);
int		builtin_unset(char **args, char ***envp);
int		builtin_env(char **envp);
int		builtin_exit(char **args, t_executor *exec);

/*
** Fonctions utilitaires
*/
void	ft_error(char *msg);
char	**get_env_array(void);
char	**convert_simple_command(t_simple_command *simple_cmd);
void	free_array(char **array);
int		init_executor(t_executor *exec, t_command *cmd);

#endif