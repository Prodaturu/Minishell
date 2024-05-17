/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sprodatu <sprodatu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 04:50:47 by sprodatu          #+#    #+#             */
/*   Updated: 2024/05/16 21:46:08 by sprodatu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_lex	*lexer_init(t_ms *ms)
{
	t_lex	*lexer;

	lexer = (t_lex *)malloc(sizeof(t_lex));
	if (!lexer)
		return (NULL);
	lexer->input = ms->input;
	lexer->dq = 0;
	lexer->sq = 0;
	lexer->pos = 0;
	return (lexer);
}

/**
 * Retrieves the next token from the input string.
 *
 * @param lexer The lexer object.
 * @return The next token.
 */

t_token	*get_token(t_lex *lexer)
{
	int		input_len;
	char	current_char;

	input_len = ft_strlen(lexer->input);
	while (lexer->pos < input_len)
	{
		current_char = lexer->input[lexer->pos];
		if (ft_isspace(current_char))
			lexer->pos++;
		else if (current_char == '|')
			return (pipe_token(lexer));
		else if (current_char == '<')
			return (in_token(lexer));
		else if (current_char == '>')
			return (out_token(lexer));
		else
			return (word_token(lexer));
	}
	return (eof_token());
}

int	lexing(t_ms *ms)
{
	t_lex	*lexer;

	lexer = lexer_init(ms);
	if (!lexer || !lexer->input)
		return (free(lexer), 0);
	ms->token = get_token(lexer);
	ms->token->prev = NULL;
	ms->token->next = NULL;
	while (ms->token->type != END)
	{
		ms->token->next = get_token(lexer);
		if (!ms->token->next)
		{
			ms->exit_code = 258;
			return (printf("Syntax Error!\tunclosed quotes"), free(lexer), 0);
		}
		ms->token->next->prev = ms->token;
		ms->token = ms->token->next;
	}
	return (free(lexer), 1);
}

// lexer function:
// 1. Initialize the lexer with the input string.
// 2. If lexer or input is NULL, return NULL.
// 3. Get the first token.
// 4. If token is NULL, return 0.
// 5. Set the previous token to NULL.
// 6. Loop until the token type is END.
// 7. Get the next token.
// 8. If next token is NULL, set exit code to 258,
//		print "Syntax Error! unclosed quotes", free lexer and return 0.
// 9. Set the previous token to the current token.
// 10. Set the current token to the next token.
// 11. free lexer and return 1.

// get_token function:
