/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ellucas <ellucas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 17:54:14 by ellucas           #+#    #+#             */
/*   Updated: 2025/04/20 19:26:31 by ellucas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

static int is_redirection_token(t_token_type type)
{
    return (type == REDIR_IN || type == REDIR_OUT || 
            type == APPEND || type == HEREDOC);
}

int parse_command(t_parser *parser)
{
    t_simple_command *current_cmd;
    
    current_cmd = NULL;
    while (parser->current_token && 
           parser->current_token->token.type != EOF_TOKEN)
    {
        if (get_current_token_type(parser) == CMD || 
            get_current_token_type(parser) == ARG)
        {
            if (!current_cmd)
            {
                current_cmd = create_simple_command();
                if (!current_cmd)
                    return (1);
            }
            if (add_argument_to_command(current_cmd, 
                get_current_token_value(parser)) != 0)
                return (1);
            advance_token(parser);
        }
        else if (get_current_token_type(parser) == PIPE)
        {
            if (!current_cmd)
            {
                syntax_error(parser, "syntax error near unexpected token `|'");
                return (1);
            }
            add_simple_command(parser->command_table, current_cmd);
            current_cmd = NULL;
            advance_token(parser);
        }
        else if (is_redirection_token(get_current_token_type(parser)))
        {
            if (parse_redirections(parser) != 0)
                return (1);
        }
        else
        {
            advance_token(parser);
        }
    }
    
    if (current_cmd)
        add_simple_command(parser->command_table, current_cmd);
        
    return (0);
}

int add_argument_to_command(t_simple_command *cmd, char *arg)
{
    if (!cmd || !arg)
        return (1);
        
    add_argument(cmd, arg);
    return (0);
}