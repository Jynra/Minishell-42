#include "lexer.h"

void	handle_pipe(t_lexer *lexer)
{
	t_token	*token;
	char	*value;

	value = ft_strdup("|");
	token = create_token(PIPE, value);
	add_token(lexer->tokens, token);
	free(token);
	advance(lexer);
}
