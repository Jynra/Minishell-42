/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ellucas <ellucas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 16:07:56 by ellucas           #+#    #+#             */
/*   Updated: 2025/04/03 17:10:45 by ellucas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	ft_error(char	*msg)
{
	ft_printf("ERROR: %s\n", msg);
	exit;
}

void	free_pipex(t_pipex *pipex)
{
	
}