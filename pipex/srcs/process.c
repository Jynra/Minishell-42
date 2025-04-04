/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ellucas <ellucas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 17:12:02 by ellucas           #+#    #+#             */
/*   Updated: 2025/04/04 03:00:03 by ellucas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

static char	*get_env_path(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			return (envp[i] + 5);
		i++;
	}
	return (NULL);
}

void	child_process(t_pipex *pipex, int i)
{
	int	j;

	if (i == 0)
		dup2(pipex->infile, STDIN_FILENO);
	else
		dup2(pipex->pipes[i - 1][0], STDIN_FILENO);
	if (i == pipex->cmd_count - 1)
		dup2(pipex->outfile, STDOUT_FILENO);
	else
		dup2(pipex->pipes[i][1], STDOUT_FILENO);
	j = 0;
	while (j < pipex->cmd_count - 1)
	{
		close(pipex->pipes[j][0]);
		close(pipex->pipes[j][1]);
		j++;
	}
	if (!pipex->cmds_paths[i])
		ft_error("Command not found");
	execve(pipex->cmds_paths[i], pipex->cmds_args[i], pipex->envp);
	ft_error("Command execution failed");
}

char	*find_path(char *cmd, char **envp)
{
	char	*path;
	char	*dir;
	char	*cmd_path;
	char	**dirs;
	int		i;

	path = get_env_path(envp);
	if (!path)
		return (NULL);
	dirs = ft_split(path, ':');
	i = 0;
	while (dirs[i])
	{
		dir = ft_strjoin(dirs[i], "/");\
		cmd_path = ft_strjoin(dir, cmd);
		free(dir);
		if (access(cmd_path, X_OK) == 0)
			return (cmd_path);
		free(cmd_path);
		i++;
	}
	return (NULL);
}