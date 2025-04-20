/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_msg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ellucas <ellucas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 11:25:20 by ebornand          #+#    #+#             */
/*   Updated: 2025/04/20 18:02:12 by ellucas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"

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
