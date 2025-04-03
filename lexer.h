#ifndef LEXER_H
# define LEXER_H

typedef enum e_token_type {
	CMD,
	ARG,
	PIPE,
	REDIR_OUT,
	REDIR_IN,
	FILE,
	VAR
}	t_token_type;

typedef struct s_token {
	t_token_type	type;
	char			*value;
}	t_token;

typedef struct s_token_node {
	t_token				token;
	struct s_token_node	*next;
}	t_token_node;

typedef struct s_token_list {
	t_token_node	*head;
	t_token_node	*tail;
}	t_token_list;

typedef struct s_lexer {
	t_token_list	*tokens;
	char			*input;
	int				current_pos;
}	t_lexer;

#endif