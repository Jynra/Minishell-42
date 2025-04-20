/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_pipe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ellucas <ellucas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 16:47:24 by ebornand          #+#    #+#             */
/*   Updated: 2025/04/20 18:02:19 by ellucas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"

void	handle_pipe(t_lexer *lexer)
{
	t_token	*token;
	char	*value;

	value = ft_strdup("|");
	token = create_token(PIPE, value);
	add_token(lexer->tokens, token);
	free(token);
	advance(lexer);
}
