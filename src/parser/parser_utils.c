/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ellucas <ellucas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 17:58:42 by ellucas           #+#    #+#             */
/*   Updated: 2025/04/20 19:26:58 by ellucas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

int advance_token(t_parser *parser)
{
    if (!parser || !parser->current_token)
        return (1);
    parser->current_token = parser->current_token->next;
    return (0);
}

t_token_type get_current_token_type(t_parser *parser)
{
    if (!parser || !parser->current_token)
        return (EOF_TOKEN);
    return (parser->current_token->token.type);
}

char *get_current_token_value(t_parser *parser)
{
    if (!parser || !parser->current_token)
        return (NULL);
    return (parser->current_token->token.value);
}

int expect_token(t_parser *parser, t_token_type type)
{
    if (!parser || !parser->current_token)
        return (1);
    if (parser->current_token->token.type != type)
        return (1);
    return (0);
}