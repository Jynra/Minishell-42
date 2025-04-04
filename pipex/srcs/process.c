/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ellucas <ellucas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 17:12:02 by ellucas           #+#    #+#             */
/*   Updated: 2025/04/04 17:15:59 by ellucas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	here_doc_input(t_pipex *pipex)
{
	int	tmp_fd;
	char	*line;
	size_t	limiter_len;

	if (!pipex->limiter)
		ft_error("Error: No limiter specific for here_doc");
	limiter_len = ft_strlen(pipex->limiter);

	tmp_fd = open(".tmp_heredoc", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (tmp_fd < 0)
		ft_error("Error: Cannot create temp file for heredoc");

	write(1, "heredoc> ", 9);
	line = get_next_line(0);

	while (line)
	{
		if (ft_strncmp(line, pipex->limiter, limiter_len) == 0 &&
			(line[limiter_len] == '\n' || line[limiter_len] == '\0'))
		{
			free(line);
			break ;
		}
		write(tmp_fd, line, ft_strlen(line));
		free(line);
		write(1, "heredoc> ", 9);
		line = get_next_line(0);
	}
	close(tmp_fd);
	pipex->infile = open(".tmp_heredoc", O_RDONLY);
	if (pipex->infile < 0)
	{
		unlink(".tmp_heredoc");
		ft_error("Error: Cannot open temp heredoc file");
	}
}

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
