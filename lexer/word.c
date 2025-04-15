/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebornand <ebornand@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 11:25:58 by ebornand          #+#    #+#             */
/*   Updated: 2025/04/10 21:21:35 by ebornand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lexer.h"

char	*extract_word(t_lexer *lexer)
{
	int		start_pos;
	int		len;
	char	*word;
	int		i;

	len = 0;
	start_pos = lexer->current_pos;
	len = calculate_word_length(lexer);
	word = malloc(sizeof(char) * (len + 1));
	if (!word)
	{
		perror("Error : memory alloction for char *word failed");
		return (NULL);
	}
	lexer->current_pos = start_pos;
	i = 0;
	while (i < len)
	{
		word[i] = current_char(lexer);
		advance(lexer);
		i++;
	}
	word[len] = '\0';
	return (word);
}

int	calculate_word_length(t_lexer *lexer)
{
	int	len;

	len = 0;
	while (current_char(lexer) != '\0'
		&& !is_special_char(current_char(lexer))
		&& current_char(lexer) != ' ')
	{
		advance(lexer);
		len++;
	}
	return (len);
}
