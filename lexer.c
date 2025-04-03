#include "lexer.h"

t_lexer	init_lexer(char *input)
{
	t_lexer	lexer;

	lexer.input = input;
	lexer.current_pos = 0;
	lexer.tokens = create_token_list();
	return (lexer);
}

t_token_list	*create_token_list(void)
{
	t_token_list	*list;

	list = malloc(sizeof(t_token_list));
	if (!list)
	{
		perror("Error : memory alloction for t_token_list *list failed :(");
		return (NULL);
	}
	list->head = NULL;
	list->tail = NULL;
	return (list);
}
