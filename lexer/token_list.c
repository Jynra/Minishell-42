/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebornand <ebornand@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 11:25:53 by ebornand          #+#    #+#             */
/*   Updated: 2025/04/15 13:37:22 by ebornand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lexer.h"

t_token_list	*create_token_list(void)
{
	t_token_list	*list;

	list = malloc(sizeof(t_token_list));
	if (!list)
	{
		perror("Error : memory alloction for t_token_list *list failed");
		return (NULL);
	}
	list->head = NULL;
	list->tail = NULL;
	return (list);
}

t_token_node	*create_token_node(t_token *token)
{
	t_token_node	*new_node;

	new_node = malloc(sizeof(t_token_node));
	if (!new_node)
	{
		perror("Error: memory allocation for t_token_node failed");
		return (NULL);
	}
	new_node->token.type = token->type;
	if (token->value)
		new_node->token.value = ft_strdup(token->value);
	else
		new_node->token.value = NULL;
	new_node->next = NULL;
	return (new_node);
}

void	add_token(t_lexer *lexer, t_token *token)
{
	t_token_node	*new_node;

	if (!token || !lexer || !lexer->tokens)
		return ;
	new_node = create_token_node(token);
	if (!new_node)
		return ;
	if (!lexer->tokens->head)
	{
		lexer->tokens->head = new_node;
		lexer->tokens->tail = new_node;
	}
	else
	{
		lexer->tokens->tail->next = new_node;
		lexer->tokens->tail = new_node;
	}
}

void	free_token_list(t_token_list *list)
{
	t_token_node	*current;
	t_token_node	*next;

	if (!list)
		return ;
	current = list->head;
	while (current)
	{
		next = current->next;
		if (current->token.value)
			free(current->token.value);
		free(current);
		current = next;
	}
	free(list);
}
