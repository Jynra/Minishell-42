/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ellucas <ellucas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 14:48:17 by ellucas           #+#    #+#             */
/*   Updated: 2025/04/04 03:10:37 by ellucas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

/* add ---->   static void create__pipes(t_pipex *pipex) */


/* a modifier */
static void	init_pipex(t_pipex *pipex, int ac, char **av, char **envp)
{
	(void) ac;
	
	pipex->infile = open(av[1], O_RDONLY);
	if  (pipex->infile < 0)
		ft_error("Cannot open infile");
	pipex->outfile = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (pipex->outfile < 0)
		ft_error("Cannot open outfile");
	if (pipe(pipex->pipe_fd) < 0)
		ft_error("Pipe failed");
	pipex->envp = envp;
	pipex->cmd1_args = ft_split(av[2], ' ');
	pipex->cmd2_args = ft_split(av[3], ' ');
	pipex->cmd1_path = find_path(pipex->cmd1_args[0], envp);
	pipex->cmd2_path = find_path(pipex->cmd2_args[0], envp);
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