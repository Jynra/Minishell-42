/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ellucas <ellucas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 15:38:33 by ellucas           #+#    #+#             */
/*   Updated: 2025/04/09 15:45:07 by ellucas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/executor.h"

/*
** Initialise la structure executor à partir de la command table
*/
int	init_executor(t_executor *exec, t_command *cmd)
{
	int	i;

	exec->cmd_count = cmd->_numberOfSimpleCommands;
	exec->background = cmd->_background;
	exec->envp = get_env_array();
	exec->exit_status = 0;
	exec->here_doc = 0;
	exec->limiter = NULL;

	// Configurer les redirections
	if (cmd->_inputFile)
	{
		exec->infile = open(cmd->_inputFile, O_RDONLY);
		if (exec->infile < 0)
		{
			perror(cmd->_inputFile);
			return (1);
		}
	}
	else
		exec->infile = STDIN_FILENO;

	if (cmd->_outFile)
	{
		if (cmd->_append)
			exec->outfile = open(cmd->_outFile, O_WRONLY | O_CREAT | O_APPEND, 0644);
		else
			exec->outfile = open(cmd->_outFile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (exec->outfile < 0)
		{
			perror(cmd->_outFile);
			return (1);
		}
	}
	else
		exec->outfile = STDOUT_FILENO;

	if (cmd->_errFile)
	{
		exec->errfile = open(cmd->_errFile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (exec->errfile < 0)
		{
			perror(cmd->_errFile);
			return (1);
		}
	}
	else
		exec->errfile = STDERR_FILENO;

	// Allouer mémoire pour les commandes
	exec->cmds_args = malloc(sizeof(char **) * exec->cmd_count);
	exec->cmds_paths = malloc(sizeof(char *) * exec->cmd_count);
	exec->pids = malloc(sizeof(pid_t) * exec->cmd_count);
	if (!exec->cmds_args || !exec->cmds_paths || !exec->pids)
	{
		perror("Malloc failed");
		return (1);
	}

	// Convertir les SimpleCommands
	i = 0;
	while (i < exec->cmd_count)
	{
		exec->cmds_args[i] = convert_simple_command(cmd->_simpleCommands[i]);
		if (exec->cmds_args[i] && exec->cmds_args[i][0])
			exec->cmds_paths[i] = find_path(exec->cmds_args[i][0], exec->envp);
		else
			exec->cmds_paths[i] = NULL;
		i++;
	}

	return (0);
}

/*
** Exécute une commande complète (avec potentiellement plusieurs pipes)
*/
int	execute_command(t_command *cmd)
{
	t_executor	exec;
	int			i;
	int			j;
	int			tmpin;
	int			tmpout;
	int			tmperr;
	int			status;

	// Vérifier s'il y a des commandes à exécuter
	if (cmd->_numberOfSimpleCommands == 0)
		return (0);

	// Sauvegarder les descripteurs standard
	tmpin = dup(STDIN_FILENO);
	tmpout = dup(STDOUT_FILENO);
	tmperr = dup(STDERR_FILENO);

	// Initialiser la structure
	if (init_executor(&exec, cmd) != 0)
	{
		close(tmpin);
		close(tmpout);
		close(tmperr);
		return (1);
	}

	// Vérifier d'abord si c'est une commande builtin sans pipe
	if (exec.cmd_count == 1 && exec.cmds_args[0] && 
		is_builtin(exec.cmds_args[0][0]))
	{
		// Configurer les redirections
		if (exec.infile != STDIN_FILENO)
			dup2(exec.infile, STDIN_FILENO);
		if (exec.outfile != STDOUT_FILENO)
			dup2(exec.outfile, STDOUT_FILENO);
		if (exec.errfile != STDERR_FILENO)
			dup2(exec.errfile, STDERR_FILENO);

		// Exécuter le builtin
		status = execute_builtin(exec.cmds_args[0], &exec);

		// Restaurer les descripteurs
		dup2(tmpin, STDIN_FILENO);
		dup2(tmpout, STDOUT_FILENO);
		dup2(tmperr, STDERR_FILENO);

		// Nettoyer et retourner
		free_executor(&exec);
		close(tmpin);
		close(tmpout);
		close(tmperr);
		return (status);
	}

	// Créer les pipes
	create_pipes(&exec);

	// Fork et exécuter chaque commande
	i = 0;
	while (i < exec.cmd_count)
	{
		exec.pids[i] = fork();
		if (exec.pids[i] < 0)
		{
			perror("Fork failed");
			// Cleanup
			break;
		}

		if (exec.pids[i] == 0)
			child_process(&exec, i);

		i++;
	}

	// Fermer tous les pipes dans le processus parent
	j = 0;
	while (j < exec.cmd_count - 1)
	{
		close(exec.pipes[j][0]);
		close(exec.pipes[j][1]);
		j++;
	}

	// Restaurer les descripteurs standard
	dup2(tmpin, STDIN_FILENO);
	dup2(tmpout, STDOUT_FILENO);
	dup2(tmperr, STDERR_FILENO);
	close(tmpin);
	close(tmpout);
	close(tmperr);

	// Attendre les processus enfants si pas en arrière-plan
	if (!exec.background)
	{
		i = 0;
		while (i < exec.cmd_count)
		{
			waitpid(exec.pids[i], &status, 0);
			if (i == exec.cmd_count - 1)  // Dernier processus
			{
				if (WIFEXITED(status))
					exec.exit_status = WEXITSTATUS(status);
				else if (WIFSIGNALED(status))
					exec.exit_status = 128 + WTERMSIG(status);
			}
			i++;
		}
	}

	// Libérer la mémoire
	status = exec.exit_status;
	free_executor(&exec);
	return (status);
}

/*
** Libère toutes les ressources allouées pour l'exécuteur
*/
void	free_executor(t_executor *exec)
{
	int	i;

	// Libérer les arguments des commandes
	if (exec->cmds_args)
	{
		i = 0;
		while (i < exec->cmd_count)
		{
			if (exec->cmds_args[i])
				free_array(exec->cmds_args[i]);
			i++;
		}
		free(exec->cmds_args);
	}

	// Libérer les chemins des commandes
	if (exec->cmds_paths)
	{
		i = 0;
		while (i < exec->cmd_count)
		{
			if (exec->cmds_paths[i])
				free(exec->cmds_paths[i]);
			i++;
		}
		free(exec->cmds_paths);
	}

	// Libérer les pipes
	if (exec->pipes)
	{
		i = 0;
		while (i < exec->cmd_count - 1)
		{
			free(exec->pipes[i]);
			i++;
		}
		free(exec->pipes);
	}

	// Libérer les PIDs
	if (exec->pids)
		free(exec->pids);

	// Libérer le limiter si here_doc
	if (exec->limiter)
		free(exec->limiter);

	// Fermer les fichiers (s'ils ne sont pas stdin/stdout/stderr)
	if (exec->infile != STDIN_FILENO)
		close(exec->infile);
	if (exec->outfile != STDOUT_FILENO)
		close(exec->outfile);
	if (exec->errfile != STDERR_FILENO)
		close(exec->errfile);

	// Libérer envp si nécessaire (si c'est une copie)
	// Si vous utilisez directement l'envp du système, ne pas le libérer
	// free_array(exec->envp);
}