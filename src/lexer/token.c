/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ellucas <ellucas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 11:25:49 by ebornand          #+#    #+#             */
/*   Updated: 2025/05/13 15:55:45 by ellucas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"

t_token	*create_token(t_token_type type, char *value)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
	{
		perror("Error: memory allocation for token failed");
		return (NULL);
	}
	token->type = type;
	token->value = value;
	return (token);
}

void	add_eof_token(t_lexer *lexer)
{
	t_token	*eof_token;

	eof_token = create_token(EOF_TOKEN, NULL);
	add_token(lexer, eof_token);
	free(eof_token);
}