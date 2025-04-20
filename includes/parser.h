/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ellucas <ellucas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 17:06:33 by ellucas           #+#    #+#             */
/*   Updated: 2025/04/20 19:31:17 by ellucas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "minishell.h"
# include "lexer.h"

typedef struct s_parser
{
    t_token_node    *current_token;
    t_command       *command_table;
    int             error;
}   t_parser;

// parser_main.c
int         parse_line(char *line, t_command *cmd_table);
t_parser    *init_parser(t_token_list *tokens);
void        free_parser(t_parser *parser);

// parser_cmd.c
int         parse_command(t_parser *parser);
int         parse_simple_command(t_parser *parser);
int         add_argument_to_command(t_simple_command *cmd, char *arg);

// parser_redirections.c
int         parse_redirections(t_parser *parser);
int         parser_handle_input_redirection(t_parser *parser);  // Renommé
int         parser_handle_output_redirection(t_parser *parser); // Renommé

// parser_pipes.c
int         parse_pipe(t_parser *parser);
int         check_pipe_syntax(t_parser *parser);

// parser_utils.c
int         advance_token(t_parser *parser);
int         expect_token(t_parser *parser, t_token_type type);
t_token_type get_current_token_type(t_parser *parser);
char        *get_current_token_value(t_parser *parser);

// parser_error.c
void        syntax_error(t_parser *parser, char *message);
int         check_syntax(t_token_list *tokens);

#endif