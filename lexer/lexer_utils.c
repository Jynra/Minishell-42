/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebornand <ebornand@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 11:25:40 by ebornand          #+#    #+#             */
/*   Updated: 2025/04/15 13:04:51 by ebornand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lexer.h"

char	current_char(t_lexer *lexer)
{
	return (lexer->input[lexer->current_pos]);
}

void	advance(t_lexer *lexer)
{
	if (lexer->input[lexer->current_pos] != '\0')
		lexer->current_pos++;
}

void	skip_whitespace(t_lexer *lexer)
{
	while (current_char(lexer) == ' ' || current_char(lexer) == '\t')
		advance(lexer);
}

int	count_quoted_word_length(t_lexer *lexer, char quote_char)
{
	int	len;

	len = 0;
	advance(lexer);
	while (current_char(lexer) != quote_char && current_char(lexer) != '\0')
	{
		advance(lexer);
		len++;
	}
	if (current_char(lexer) == '\0')
	{
		write_error("Syntax error: unclosed quote\n");
		return (-1);
	}
	return (len);
}
