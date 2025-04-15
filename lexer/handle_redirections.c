#include "lexer.h"

int	is_redirection(t_lexer *lexer)
{
	char	c;

	c = current_char(lexer);
	return (c == '<' || c == '>');
}

void	handle_input_redirection(t_lexer *lexer)
{
	t_token_type	type;
	char			*value;
	t_token			*token;

	advance(lexer);
	if (current_char(lexer) == '<')
	{
		type = HEREDOC;
		value = ft_strdup("<<");
		advance(lexer);
	}
	else
	{
		type = REDIR_IN;
		value = ft_strdup("<");
	}
	token = create_token(type, value);
	add_token(lexer->tokens, token);
	free(token);
}

void	handle_output_redirection(t_lexer *lexer)
{
	t_token_type	type;
	char			*value;
	t_token			*token;

	advance(lexer);
	if (current_char(lexer) == '>')
	{
		type = APPEND;
		value = ft_strdup(">>");
		advance(lexer);
	}
	else
	{
		type = REDIR_OUT;
		value = ft_strdup(">");
	}
	token = create_token(type, value);
	add_token(lexer->tokens, token);
	free(token);
}

void	handle_redirection(t_lexer *lexer)
{
	if (current_char(lexer) == '<')
		handle_input_redirection(lexer);
	else
		handle_output_redirection(lexer);
}
