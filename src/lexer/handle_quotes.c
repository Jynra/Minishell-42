/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ellucas <ellucas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 11:25:31 by ebornand          #+#    #+#             */
/*   Updated: 2025/05/13 15:08:06 by ellucas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"

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
	lexer->current_pos = start_pos;
	while (i < len)
	{
		word[i] = current_char(lexer);
		advance(lexer);
		i++;
	}
	word[len] = '\0';
	return (word);
}

int	is_quote(char c)
{
	return (c == '\'' || c == '\"');
}