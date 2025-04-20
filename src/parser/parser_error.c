/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ellucas <ellucas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 18:00:43 by ellucas           #+#    #+#             */
/*   Updated: 2025/04/20 19:27:19 by ellucas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

void syntax_error(t_parser *parser, char *message)
{
    ft_putstr_fd("minishell: ", STDERR_FILENO);
    ft_putstr_fd(message, STDERR_FILENO);
    ft_putchar_fd('\n', STDERR_FILENO);
    parser->error = 1;
}

static int is_redirection_token(t_token_type type)
{
    return (type == REDIR_IN || type == REDIR_OUT || 
            type == APPEND || type == HEREDOC);
}

int check_syntax(t_token_list *tokens)
{
    t_token_node *current;
    int has_command_or_arg;
    
    current = tokens->head;
    has_command_or_arg = 0;
    
    while (current && current->token.type != EOF_TOKEN)
    {
        if (current->token.type == CMD || current->token.type == ARG)
            has_command_or_arg = 1;
            
        if (current->token.type == PIPE)
        {
            if (!has_command_or_arg)
            {
                ft_putstr_fd("minishell: syntax error near unexpected token `|'\n", 
                            STDERR_FILENO);
                return (1);
            }
            has_command_or_arg = 0;
        }
        
        if (is_redirection_token(current->token.type))
        {
            if (!current->next || current->next->token.type == EOF_TOKEN ||
                current->next->token.type == PIPE ||
                is_redirection_token(current->next->token.type))
            {
                ft_putstr_fd("minishell: syntax error near unexpected token\n", 
                            STDERR_FILENO);
                return (1);
            }
        }
        current = current->next;
    }
    
    if (!has_command_or_arg && tokens->head && 
        tokens->head->token.type != EOF_TOKEN)
    {
        ft_putstr_fd("minishell: syntax error: unexpected end of file\n", 
                    STDERR_FILENO);
        return (1);
    }
    
    return (0);
}
