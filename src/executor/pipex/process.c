/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ellucas <ellucas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 15:44:33 by ellucas           #+#    #+#             */
/*   Updated: 2025/04/09 22:22:29 by ellucas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/executor.h"

/*
** Gère le processus enfant pour exécuter une commande
*/
void	child_process(t_executor *exec, int i)
{
	int	j;

	// Gérer la redirection d'entrée
	if (i == 0)
	{
		// Premier processus: prend l'entrée du fichier/stdin
		dup2(exec->infile, STDIN_FILENO);
	}
	else
	{
		// Processus intermédiaire: prend l'entrée du pipe précédent
		dup2(exec->pipes[i - 1][0], STDIN_FILENO);
	}

	// Gérer la redirection de sortie
	if (i == exec->cmd_count - 1)
	{
		// Dernier processus: écrit vers le fichier/stdout
		dup2(exec->outfile, STDOUT_FILENO);
	}
	else
	{
		// Processus intermédiaire: écrit vers le pipe suivant
		dup2(exec->pipes[i][1], STDOUT_FILENO);
	}

	// Gérer la redirection d'erreur si nécessaire
	if (exec->errfile != STDERR_FILENO)
		dup2(exec->errfile, STDERR_FILENO);

	// Fermer tous les pipes
	j = 0;
	while (j < exec->cmd_count - 1)
	{
		close(exec->pipes[j][0]);
		close(exec->pipes[j][1]);
		j++;
	}

	// Fermer les fichiers
	if (exec->infile != STDIN_FILENO)
		close(exec->infile);
	if (exec->outfile != STDOUT_FILENO)
		close(exec->outfile);
	if (exec->errfile != STDERR_FILENO)
		close(exec->errfile);

	// Exécuter la commande
	if (!exec->cmds_args[i] || !exec->cmds_args[i][0])
		exit(0);

	if (!exec->cmds_paths[i])
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(exec->cmds_args[i][0], 2);
		ft_putstr_fd(": command not found\n", 2);
		exit(127);
	}

	execve(exec->cmds_paths[i], exec->cmds_args[i], exec->envp);
	perror("execve");
	exit(126);
}

/*
** Trouve le chemin complet d'une commande dans PATH
*/
char	*find_path(char *cmd, char **envp)
{
//	char	*path;
	char	*dir;
	char	*cmd_path;
	char	**dirs;
	int		i;

	// Vérifier si la commande est un chemin absolu ou relatif
	if (cmd[0] == '/' || cmd[0] == '.')
	{
		if (access(cmd, X_OK) == 0)
			return (ft_strdup(cmd));
		return (NULL);
	}

	// Chercher dans PATH
	i = 0;
	while (envp[i] && ft_strncmp(envp[i], "PATH=", 5))
		i++;
	if (!envp[i])
		return (NULL);

	dirs = ft_split(envp[i] + 5, ':');
	i = 0;
	while (dirs[i])
	{
		dir = ft_strjoin(dirs[i], "/");
		cmd_path = ft_strjoin(dir, cmd);
		free(dir);
		if (access(cmd_path, X_OK) == 0)
		{
			free_array(dirs);
			return (cmd_path);
		}
		free(cmd_path);
		i++;
	}
	free_array(dirs);
	return (NULL);
}