/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebornand <ebornand@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 11:25:35 by ebornand          #+#    #+#             */
/*   Updated: 2025/04/15 13:35:23 by ebornand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lexer.h"

t_lexer	init_lexer(char *input)
{
	t_lexer	lexer;

	lexer.input = input;
	lexer.current_pos = 0;
	lexer.tokens = create_token_list();
	return (lexer);
}

void	tokenize(t_lexer *lexer)
{
	while (current_char(lexer) != '\0')
	{
		if (current_char(lexer) == ' ' || current_char(lexer) == '\t')
			skip_whitespace(lexer);
		else if (is_quote(current_char(lexer)))
			handle_quote(lexer);
		else if (is_redirection(lexer))
			handle_redirection(lexer);
		else if (current_char(lexer) == '|')
			handle_pipe(lexer);
		else if (current_char(lexer) == '$')
			handle_variable(lexer);
		else
			handle_word(lexer);
	}
	add_eof_token(lexer);
}

void	handle_quote(t_lexer *lexer)
{
	char	quote_char;
	char	*word;
	t_token	*token;

	quote_char = current_char(lexer);
	advance(lexer);
	word = handle_quote_content(lexer, quote_char);
	if (!word)
		return ;
	token = create_token(ARG, word);
	add_token(lexer->tokens, token);
	free(token);
	advance(lexer);
}

void	free_lexer(t_lexer *lexer)
{
	if (!lexer)
		return ;
	free_token_list(lexer->tokens);
}
