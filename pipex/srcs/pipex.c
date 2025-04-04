/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ellucas <ellucas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 14:48:17 by ellucas           #+#    #+#             */
/*   Updated: 2025/04/04 13:05:07 by ellucas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

/* add ---->   static void create__pipes(t_pipex *pipex) */
static void	create_pipes(t_pipex *pipex)
{
	int	i;

	pipex->pipes = malloc(sizeof(int *) * (pipex->cmd_count - 1));
	if (!pipex->pipes)
		ft_error("Create_pipes Malloc failed");
	i = 0;
	while (i < pipex->cmd_count - 1)
	{
		pipex->pipes[i] = malloc(sizeof(int) * 2);
		if (!pipex->pipes[i])
			ft_error("Create_pipes Malloc failed");
		if (pipe(pipex->pipes[i]) < 0)
			ft_error("Pipe failed");
		i++;
	}
}

/* a modifier */
static void	init_pipex(t_pipex *pipex, int ac, char **av, char **envp)
{
	int	i;
	int	start_idx;

	pipex->here_doc = 0;
	pipex->limiter = NULL;
	if (ac >= 5 && !ft_strncmp(av[1], "here_doc", 9))
	{
		pipex->here_doc = 1;
		pipex->cmd_count = ac - 4;
		start_idx = 3;
		pipex->outfile = open(av[ac - 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (pipex->outfile < 0)
			ft_error("Cannot open outfile");
		here_doc_input(pipex);
	}
	else
	{
		pipex->cmd_count = ac - 3;
		start_idx = 2;
		pipex->infile = open(av[1], O_RDONLY);
		if (pipex->infile < 0)
			ft_error("Cannot open infile");
		pipex->outfile = open(av[ac - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (pipex->outfile < 0)
			ft_error("Cannot open outfile");
	}
	pipex->envp = envp;

	pipex->cmds_args = malloc(sizeof(char **) * pipex->cmd_count);
	pipex->cmds_paths = malloc(sizeof(char *) * pipex->cmd_count);
	pipex->pids = malloc(sizeof(pid_t) * pipex->cmd_count);
	if (!pipex->cmds_args || !pipex->cmds_paths || !pipex->pids)
		ft_error("init_pipex Malloc failed");
	
	i = 0;
	while (i < pipex->cmd_count)
	{
		pipex->cmds_args[i] = ft_split(av[start_idx + i], ' ');
		pipex->cmds_paths[i] = find_path(pipex->cmds_args[i][0], envp);
		i++;
	}
	create_pipes(pipex);
}

void	pipex(int ac, char **av, char **envp)
{
	t_pipex	pipex;
	int		i;
	int		j;

	init_pipex(&pipex, ac, av, envp);
	i = 0;
	while (i < pipex.cmd_count)
	{
		pipex.pids[i] = fork();
		if (pipex.pids[i] < 0)
			ft_error("Fork failed");
		if (pipex.pids[i] == 0)
			child_process(&pipex, i);
		i++;
	}
	j = 0;
	while (j < pipex.cmd_count - 1)
	{
		close(pipex.pipes[j][0]);
		close(pipex.pipes[j][1]);
		j++;
	}
	i = 0;
	while (i < pipex.cmd_count)
		waitpid(pipex.pids[i++], NULL, 0);
	if (pipex.here_doc)
		unlink(".tmp_heredoc");
	free_pipex(&pipex);
}

int	main(int ac, char **av, char **envp)
{
	if (ac < 5)
	{
		if (ac >= 2 && !ft_strncmp(av[1], "here_doc", 9) && ac < 6)
			ft_putstr_fd("Usage: ./pipex here_doc LIMITER cmd1 cmd2 file\n", 2);
		else
			ft_putstr_fd("Usage: ./pipex file1 cmd1 cmd2 ... cmdn file2\n", 2);
		return (1);
	}
	pipex(ac, av, envp);
	return (0);
}