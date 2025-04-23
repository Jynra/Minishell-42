/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_struct.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ellucas <ellucas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 13:48:36 by ellucas           #+#    #+#             */
/*   Updated: 2025/04/23 14:41:44 by ellucas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/parser.h"
t_command	*create_command(void)
{
	t_command	*cmd;

	cmd = malloc(sizeof(t_command));
	if (!cmd)
		return (NULL);
	cmd->_numberOfSimpleCommands = 0;
	cmd->_numberOfAvailableSimpleCommands = 10;
	cmd->_simpleCommands = malloc(sizeof(t_simple_command *) *
								cmd->_numberOfAvailableSimpleCommands);
	if (!cmd->_simpleCommands)
	{
		free(cmd);
		return (NULL);
	}
	cmd->_outFile = NULL;
	cmd->_inputFile = NULL;
	cmd->_errFile = NULL;
	cmd->_background = 0;
	cmd->_append = 0;
	return (cmd);
}

