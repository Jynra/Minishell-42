/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ellucas <ellucas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 16:07:56 by ellucas           #+#    #+#             */
/*   Updated: 2025/04/04 02:57:04 by ellucas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	ft_error(char	*msg)
{
	perror(msg);
	exit (EXIT_FAILURE);
}

static void	free_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void	free_pipex(t_pipex *pipex)
{
	int	i;

	i = 0;
	if (pipex->cmds_args)
	{
		while (i < pipex->cmd_count && pipex->cmds_args[i])
		{
			free_array(pipex->cmds_args[i]);
			i++;
		}
		free(pipex->cmds_args);
	}
	if (pipex->cmds_paths)
	{
		i = 0;
		while (i < pipex->cmd_count && pipex->cmds_args[i])
		{
			free(pipex->cmds_paths[i]);
			i++;
		}
		free(pipex->cmds_paths);
	}
	if (pipex->pids)
		free(pipex->pids);
	if (pipex->pipes)
	{
		i = 0;
		while (i < pipex->cmd_count - 1)
			free(pipex->pipes[i++]);
		free(pipex->pipes);
	}
	if (pipex->limiter)
		free(pipex->limiter);
	close(pipex->infile);
	close(pipex->outfile);
}