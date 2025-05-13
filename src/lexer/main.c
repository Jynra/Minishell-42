/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ellucas <ellucas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 16:48:03 by ebornand          #+#    #+#             */
/*   Updated: 2025/05/13 15:55:18 by ellucas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"

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

int	main(void)
{
	char	*line;

	while (1)
	{
		line = get_input();
		if (!line)
		{
			write(1, "exit\n", 1);
			break;
		}
		if (*line)
		{
			t_lexer	lexer;
			lexer = init_lexer(line);
			tokenize(&lexer);
			printf("=== INPUT ===\n");
			printf("%s\n", lexer.input);
			printf("=============\n");
			print_tokens(lexer.tokens);
			free_lexer(&lexer);
		}
		free(line);
	}
	return 0;
}