/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sprodatu <sprodatu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 04:50:47 by sprodatu          #+#    #+#             */
/*   Updated: 2024/05/25 17:48:37 by sprodatu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * @brief Initialize the lexer object.
 * 
 * @param ms The main structure.
 * 
 * @return The lexer object.
 * 
 * Allocate memory for the lexer object.
 * If lexer is NULL, return NULL.
 * Set the input of the lexer to the input string.
 * Set the double quote flag to 0.
 * Set the single quote flag to 0.
 * Set the position to 0.
 * Return the lexer object.
 * 
 * CHECKED & WORKING
 */

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
 * 
 * Get the length of the input string.
 * Loop until the position is less than the length of the input string.
 * Get the current character.
 * If the current character is a space, increment the position.
 * Else if the current character is a pipe, return a pipe token.
 * Else if the current character is a less than sign, return an in token.
 * Else if the current character is a greater than sign, return an out token.
 * Else return a word token.
 * 
 * CHECKED & WORKING
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
		else if ((current_char == '\'' || current_char == '"' )
			&& lexer->input[lexer->pos + 1] == current_char)
			return (lexer->pos++, lexer->pos++, empty_quotes_token());
		else
			return (word_token(lexer));
	}
	return (eof_token());
}

/**
 * @brief create tokens for different types of input
 * 
 * @param lexer
 * 
 * @return The next token.
 * 
 * Get the length of the input string.
 * Loop until the position is less than the length of the input string.
 * Get the current character.
 * If the current character is a space, increment the position.
 * Else if the current character is a pipe, return a pipe token.
 * Else if the current character is a less than sign, return an in token.
 * 
 * CHECKED & WORKING
 */

int	lexing(t_ms *ms)
{
	t_lex	*lexer;
	t_token	*token;

	lexer = lexer_init(ms);
	if (!lexer || !lexer->input)
		return (0);
	ms->token = get_token(lexer);
	if (!ms->token)
		return (0);
	ms->token->prev = NULL;
	token = ms->token;
	while (token->type != END)
	{
		token->next = get_token(lexer);
		if (!token->next || token->type == ERR)
		{
			ms->exit_code = 258;
			ft_putstr_fd("Error! unclosed quotes\n", 2);
			return (free(lexer), 0);
		}
		token->next->prev = token;
		token = token->next;
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
