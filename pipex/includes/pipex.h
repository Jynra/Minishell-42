/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ellucas <ellucas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 14:28:14 by ellucas           #+#    #+#             */
/*   Updated: 2025/04/03 17:10:34 by ellucas          ###   ########.fr       */
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
	int	infile;
	int	outfile;
	int	pipe_fd[2];
	char	**cmd1_args;
	char	**cmd2_args;
	char	*cmd1_path;
	char	*cmd2_path;
	char	**envp;
}	t_pipex;

/* Pipex.c */
void	pipex(int ac, char **av, char **envp);

/* Errors */
void	ft_error(char	*msg);


#endif
