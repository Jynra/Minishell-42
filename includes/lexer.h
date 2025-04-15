/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebornand <ebornand@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 11:30:27 by ebornand          #+#    #+#             */
/*   Updated: 2025/04/15 15:48:45 by ebornand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H
# include <stdlib.h>

typedef enum e_token_type
{
	CMD,
	ARG,
	PIPE,
	REDIR_IN,
	REDIR_OUT,
	APPEND,
	HEREDOC,
	VAR,
	EOF_TOKEN
}	t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
}	t_token;

typedef struct s_token_node
{
	t_token				token;
	struct s_token_node	*next;
}	t_token_node;

typedef struct s_token_list
{
	t_token_node	*head;
	t_token_node	*tail;
}	t_token_list;

typedef struct s_lexer
{
	t_token_list	*tokens;
	char			*input;
	int				current_pos;
}	t_lexer;

// error_msg.c
void			write_error(const char *msg);

// handle_pipe.c
void			handle_pipe(t_lexer *lexer);

// handle_quotes.c
char			*handle_quote_content(t_lexer *lexer, char quote_char);
char			*extract_quoted_word(t_lexer *lexer, char quote_char);
int				is_quote(char c);

// handle_redirection.c
int				is_redirection(t_lexer *lexer);
void			handle_input_redirection(t_lexer *lexer);
void			handle_output_redirection(t_lexer *lexer);
void			handle_redirection(t_lexer *lexer);

// handle_var.c
char			*extract_var_name(t_lexer *lexer, int len);
int				calculate_var_length(t_lexer *lexer);
t_token			*handle_special_var(t_lexer *lexer);
void			handle_variable(t_lexer *lexer);

// handle_word.c
t_token_type	determine_word_type(t_lexer *lexer);
void			handle_word(t_lexer *lexer);

// lexer_utils.c
char			current_char(t_lexer *lexer);
void			advance(t_lexer *lexer);
void			skip_whitespace(t_lexer *lexer);
int				count_quoted_word_length(t_lexer *lexer, char quote_char);

// lexer.c
t_lexer			init_lexer(char *input);
void			tokenize(t_lexer *lexer);
void			handle_quote(t_lexer *lexer);
void			free_lexer(t_lexer *lexer);

// special.c
int				is_special_char(char c);

// token_list.c
t_token_list	*create_token_list(void);
t_token_node	*create_token_node(t_token *token);
void			add_token(t_lexer *lexer, t_token *token);
void			free_token_list(t_token_list *list);

// token.c
t_token			*create_token(t_token_type type, char *value);
void			add_eof_token(t_lexer *lexer);

// main.c
void			print_tokens(t_token_list *list);

#endif
