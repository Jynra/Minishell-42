/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebornand <ebornand@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 11:25:31 by ebornand          #+#    #+#             */
/*   Updated: 2025/04/15 13:10:55 by ebornand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lexer.h"

char	*handle_quote_content(t_lexer *lexer, char quote_char)
{
	return (extract_quoted_word(lexer, quote_char));
}

char	*extract_quoted_word(t_lexer *lexer, char quote_char)
{
	int		start_pos;
	int		len;
	char	*word;
	int		i;

	start_pos = lexer->current_pos;
	len = count_quoted_word_length(lexer, quote_char);
	i = 0;
	if (len == -1)
		return (NULL);
	word = malloc(sizeof(char) * (len + 1));
	if (!word)
	{
		perror("malloc failed");
		return (NULL);
	}
	lexer->current_pos = start_pos + 1;
	while (i < len)
	{
		word[i++] = current_char(lexer);
		advance(lexer);
	}
	word[len] = '\0';
	return (word);
}

char	*extract_double_quoted_word(t_lexer *lexer)
{
	int		start_pos;
	int		len;
	char	*word;
	int		i;

	i = 0;
	start_pos = lexer->current_pos;
	len = count_double_quoted_word_length(lexer);
	if (len == -1)
		return (NULL);
	word = malloc(sizeof(char) * (len + 1));
	if (!word)
	{
		perror("malloc failed");
		return (NULL);
	}
	lexer->current_pos = start_pos + 1;
	while (i < len)
	{
		word[i++] = current_char(lexer);
		advance(lexer);
	}
	word[len] = '\0';
	return (word);
}

int	is_quote(char c)
{
	return (c == '\'' || c == '\"');
}
