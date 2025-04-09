/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ellucas <ellucas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 15:43:35 by ellucas           #+#    #+#             */
/*   Updated: 2025/04/09 15:45:02 by ellucas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/executor.h"

/*
** Crée les pipes nécessaires pour connecter les commandes
*/
void	create_pipes(t_executor *exec)
{
	int	i;

	// Si moins de 2 commandes, pas besoin de pipes
	if (exec->cmd_count < 2)
		return;

	exec->pipes = malloc(sizeof(int *) * (exec->cmd_count - 1));
	if (!exec->pipes)
		ft_error("Create_pipes Malloc failed");

	i = 0;
	while (i < exec->cmd_count - 1)
	{
		exec->pipes[i] = malloc(sizeof(int) * 2);
		if (!exec->pipes[i])
			ft_error("Create_pipes Malloc failed");

		if (pipe(exec->pipes[i]) < 0)
			ft_error("Pipe failed");
		i++;
	}
}

/*
** Gère l'entrée en mode here_doc (adapté de pipex)
*/
void	here_doc_input(t_executor *exec)
{
	int		tmp_fd;
	char	*line;
	size_t	limiter_len;

	if (!exec->limiter)
		ft_error("Error: No limiter specific for here_doc");
	limiter_len = ft_strlen(exec->limiter);

	tmp_fd = open(".tmp_heredoc", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (tmp_fd < 0)
		ft_error("Error: Cannot create temp file for heredoc");

	write(1, "heredoc> ", 9);
	line = get_next_line(0);

	while (line)
	{
		if (ft_strncmp(line, exec->limiter, limiter_len) == 0 &&
			(line[limiter_len] == '\n' || line[limiter_len] == '\0'))
		{
			free(line);
			break;
		}
		write(tmp_fd, line, ft_strlen(line));
		free(line);
		write(1, "heredoc> ", 9);
		line = get_next_line(0);
	}
	close(tmp_fd);
	exec->infile = open(".tmp_heredoc", O_RDONLY);
	if (exec->infile < 0)
	{
		unlink(".tmp_heredoc");
		ft_error("Error: Cannot open temp heredoc file");
	}
}