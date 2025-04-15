/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebornand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 16:47:43 by ebornand          #+#    #+#             */
/*   Updated: 2025/04/15 16:47:45 by ebornand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

char	*extract_var_name(t_lexer *lexer, int len)
{
	char	*var_name;
	int		i;

	i = 0;
	var_name = malloc(sizeof(char) * (len + 1));
	if (!var_name)
	{
		perror("Error: memory allocation for variable name failed");
		return (NULL);
	}
	while (i < len)
	{
		var_name[i] = current_char(lexer);
		i++;
		advance(lexer);
	}
	var_name[len] = '\0';
	return (var_name);
}

int	calculate_var_length(t_lexer *lexer)
{
	int	len;

	len = 0;
	while (ft_isalnum(current_char(lexer)) || current_char(lexer) == '_')
	{
		advance(lexer);
		len++;
	}
	return (len);
}

t_token	*handle_special_var(t_lexer *lexer)
{
	t_token	*token;
	char	*var_name;

	if (current_char(lexer) == '?')
	{
		advance(lexer);
		var_name = ft_strdup("?");
		token = create_token(VAR, var_name);
	}
	else
	{
		var_name = ft_strdup("$");
		token = create_token(ARG, var_name);
	}
	return (token);
}

void	handle_variable(t_lexer *lexer)
{
	int		start_pos;
	int		len;
	char	*var_name;
	t_token	*token;

	advance(lexer);
	start_pos = lexer->current_pos;
	len = calculate_var_length(lexer);
	if (len == 0)
	{
		token = handle_special_var(lexer);
	}
	else
	{
		lexer->current_pos = start_pos;
		var_name = extract_var_name(lexer, len);
		token = create_token(VAR, var_name);
		free(var_name);
	}
	add_token(lexer->tokens, token);
	free(token);
}
