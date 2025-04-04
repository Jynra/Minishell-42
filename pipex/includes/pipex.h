/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ellucas <ellucas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 14:28:14 by ellucas           #+#    #+#             */
/*   Updated: 2025/04/04 02:56:46 by ellucas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

/* Libraries */
# include "libft/libft.h"
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <sys/wait.h>

/* Structure */
typedef struct s_pipex
{
	int		infile;
	int		outfile;
	int		**pipes;
	char	***cmds_args;
	char	*cmds_paths;
	pid_t	*pids;
	int		cmd_count;
	int		here_doc;
	char	*limiter;
	char	**envp;
}	t_pipex;

/* Pipex.c */
void	pipex(int ac, char **av, char **envp);

/* process.c */
void	child_process(t_pipex *pipex, int i);
char	*find_path(char *cmd, char	**envp);
void	here_doc_input(t_pipex *pipex);

/* Errors */
void	ft_error(char	*msg);
void	free_pipex(t_pipex *pipex);

#endif
