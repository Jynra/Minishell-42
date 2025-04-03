/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ellucas <ellucas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 14:48:17 by ellucas           #+#    #+#             */
/*   Updated: 2025/04/03 17:18:01 by ellucas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

static void	init_pipex()
{
	
}

void	pipex(int ac, char **av, char **envp)
{
		
}

int	main(int ac, char **av, char **envp)
{
	if (ac != 5)
	{
		ft_error("Invalid number of arguments");
		return (1);
	}
	pipex(ac, av, envp);
	return (0);
}