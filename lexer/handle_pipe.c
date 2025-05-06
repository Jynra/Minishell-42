/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_pipe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebornand <ebornand@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 16:47:24 by ebornand          #+#    #+#             */
/*   Updated: 2025/04/23 10:57:13 by ebornand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lexer.h"

void	handle_pipe(t_lexer *lexer)
{
	t_token	*token;
	char	*value;

	value = ft_strdup("|");
	token = create_token(PIPE, value);
	add_token(lexer, token);
	free(token);
	advance(lexer);
}
