/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebornand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 16:48:03 by ebornand          #+#    #+#             */
/*   Updated: 2025/04/15 16:48:05 by ebornand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	print_tokens(t_token_list *list)
{
    t_token_node *current = list->head;
    const char *type_names[] = {
        "CMD", "ARG", "PIPE", "REDIR_IN", "REDIR_OUT", 
        "APPEND", "HEREDOC", "VAR", "EOF"
    };
    
    printf("=== TOKENS ===\n");
    while (current)
    {
        printf("Type: %-8s | Value: %s\n", 
               type_names[current->token.type],
               current->token.value ? current->token.value : "NULL");
        current = current->next;
    }
    printf("==============\n");
}

int	main(int argc, char **argv)
{
    if (argc != 2)
    {
        printf("Usage: %s \"command to tokenize\"\n", argv[0]);
        return 1;
    }
	t_lexer	lexer;
	lexer = init_lexer(argv[1]);
	tokenize(&lexer);
	print_tokens(lexer.tokens);
	free_lexer(&lexer);
	return 0;
}
