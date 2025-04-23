/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_redirections.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ellucas <ellucas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 17:56:07 by ellucas           #+#    #+#             */
/*   Updated: 2025/04/23 15:31:42 by ellucas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

int parse_redirections(t_parser *parser)
{
    t_token_type type;
    
    type = get_current_token_type(parser);
    if (type == REDIR_IN)
        return (parser_handle_input_redirection(parser));
    else if (type == REDIR_OUT || type == APPEND)
        return (parser_handle_output_redirection(parser));
    else if (type == HEREDOC)
        return (parser_handle_heredoc_redirection(parser));
    return (0);
}

int parser_handle_input_redirection(t_parser *parser)
{
    advance_token(parser);
    if (!parser->current_token || 
        (get_current_token_type(parser) != CMD &&
         get_current_token_type(parser) != ARG))
    {
        syntax_error(parser, "syntax error near unexpected token `newline'");
        return (1);
    }
    
    set_input_redirection(parser->command_table, 
                         get_current_token_value(parser));
    advance_token(parser);
    return (0);
}

int parser_handle_output_redirection(t_parser *parser)
{
    int append;
    
    append = (get_current_token_type(parser) == APPEND);
    advance_token(parser);
    
    if (!parser->current_token || 
        (get_current_token_type(parser) != CMD &&
         get_current_token_type(parser) != ARG))
    {
        syntax_error(parser, "syntax error near unexpected token `newline'");
        return (1);
    }
    
    set_output_redirection(parser->command_table, 
                          get_current_token_value(parser), 
                          append);
    advance_token(parser);
    return (0);
}