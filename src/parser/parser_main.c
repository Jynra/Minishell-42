/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ellucas <ellucas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 17:51:13 by ellucas           #+#    #+#             */
/*   Updated: 2025/04/20 19:23:16 by ellucas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

t_parser *init_parser(t_token_list *tokens)
{
	t_parser *parser;
	
	parser = malloc(sizeof(t_parser));
	if (!parser)
		return (NULL);
	parser->current_token = tokens->head;
	parser->command_table = NULL;
	parser->error = 0;
	return (parser);
}

void free_parser(t_parser *parser)
{
	if (!parser)
		return;
	free(parser);
}

int parse_line(char *line, t_command *cmd_table)
{
	t_lexer     lexer;
	t_parser    *parser;
	int         result;

	lexer = init_lexer(line);
	tokenize(&lexer);
	
	if (check_syntax(lexer.tokens) != 0)
	{
		free_lexer(&lexer);
		return (1);
	}
	
	parser = init_parser(lexer.tokens);
	if (!parser)
	{
		free_lexer(&lexer);
		return (1);
	}
	
	parser->command_table = cmd_table;
	result = parse_command(parser);
	
	free_parser(parser);
	free_lexer(&lexer);
	
	return (result);
}