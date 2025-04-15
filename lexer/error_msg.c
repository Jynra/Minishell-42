/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_msg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebornand <ebornand@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 11:25:20 by ebornand          #+#    #+#             */
/*   Updated: 2025/04/10 21:14:30 by ebornand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	write_error(const char *msg)
{
	int	i;

	i = 0;
	if (!msg)
		return ;
	while (msg[i])
		i++;
	write(2, msg, i);
}
