/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebornand <ebornand@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 11:25:49 by ebornand          #+#    #+#             */
/*   Updated: 2025/04/15 13:38:03 by ebornand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lexer.h"

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
	add_token(lexer->tokens, eof_token);
	free(eof_token);
}
