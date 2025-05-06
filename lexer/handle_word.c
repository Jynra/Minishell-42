/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_word.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebornand <ebornand@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 16:47:47 by ebornand          #+#    #+#             */
/*   Updated: 2025/04/23 11:01:21 by ebornand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lexer.h"

t_token_type	determine_word_type(t_lexer *lexer)
{
	if (!lexer->tokens->head
		|| lexer->tokens->tail->token.type == PIPE)
	{
		return (CMD);
	}
	else
	{
		return (ARG);
	}
}

void	handle_word(t_lexer *lexer)
{
	char			*word;
	t_token			*token;
	t_token_type	type;

	word = extract_word(lexer);
	if (!word)
		return ;
	type = determine_word_type(lexer);
	token = create_token(type, word);
	add_token(lexer, token);
	free(token);
	free(word);
}
