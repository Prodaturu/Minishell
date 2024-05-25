/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sprodatu <sprodatu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 06:45:45 by sprodatu          #+#    #+#             */
/*   Updated: 2024/05/25 03:29:11 by sprodatu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * Handles the pipe token in the lexer.
 * 
 * @param lexer The lexer object.
 * @return A pointer to created token, or NULL if malloc fails.
 * 
 * Allocate memory for the token.
 * If token is NULL, return NULL.
 * Set the type of the token to PIPE.
 * Set the value of the token to "|".
 * Increment the position.
 * Return the token.
 * 
 * CHECKED & WORKING
 */

t_token	*pipe_token(t_lex *lexer)
{
	t_token	*token;

	token = (t_token *)malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->type = PIPE;
	token->value = ft_strdup("|");
	return (lexer->pos++, token);
}

/**
 * Handles the input token in the lexer.
 * 
 * @param lexer The lexer object.
 * 
 * @return A pointer to the created token.
 * 
 * Allocate memory for the token.
 * If token is NULL, return NULL.
 * If the next character is a less than sign
 * 		set token type to H_DOC.
 * 		Set the value of the token to "<<"
 * Else set the type of the token to IN.
 * 		Set the value of the token to "<".
 * Increment the position.
 * Return the token.
 * 
 * CHECKED & WORKING
*/

t_token	*in_token(t_lex *lexer)
{
	t_token	*token;

	token = (t_token *)malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	if (lexer->input[lexer->pos + 1] == '<')
	{
		token->type = H_DOC;
		token->value = ft_strdup("<<");
		return (lexer->pos += 2, token);
	}
	else
	{
		token->type = IN;
		token->value = ft_strdup("<");
		return (lexer->pos++, token);
	}
}

/**
 * Handles the output token in the lexer.
 * 
 * @param lexer The lexer object.
 * 
 * @return A pointer to the created token.
 * 
 * Allocate memory for the token.
 * If token is NULL, return NULL.
 * If the next character is a greater than sign
 * 		set token type to APPEND.
 * 		Set the value of the token to ">>"
 * Else set the type of the token to OUT.
 * 		Set the value of the token to ">".
 * Increment the position.
 * Return the token.
 * 
 * CHECKED & WORKING
*/

t_token	*out_token(t_lex *lexer)
{
	t_token	*token;

	token = (t_token *)malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	if (lexer->input[lexer->pos + 1] == '>')
	{
		token->type = APPEND;
		token->value = ft_strdup(">>");
		return (lexer->pos += 2, token);
	}
	else
	{
		token->type = OUT;
		token->value = ft_strdup(">");
		return (lexer->pos++, token);
	}
}

t_token	*empty_quotes_token(void)
{
	t_token	*token;

	token = (t_token *)malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->type = WORD;
	token->value = ft_strdup("");
	return (token);
}

/**
 * Handles a word token in the lexer.
 *
 * This function scans the input string starting from the current position and
 * identifies a word token. It takes into account quotes, spaces, and special
 * characters such as '|', '<', and '>'.
 *
 * @param lexer The lexer object.
 * @return A pointer to the word token.
 */

t_token	*word_token(t_lex *lex)
{
	int		start;

	start = lex->pos;
	while (lex->input[lex->pos])
	{
		if (lex->input[lex->pos] == '\'' || lex->input[lex->pos] == '\"')
			quote_token_value(lex, lex->input[lex->pos]);
		if ((ft_isspace(lex->input[lex->pos]) || lex->input[lex->pos] == '|'
				|| lex->input[lex->pos] == '<' || lex->input[lex->pos] == '>')
			&& !(lex->dq || lex->sq))
			break ;
		lex->pos++;
	}
	// if (lex->input[lex->pos] != lex->input[lex->pos - 1])
	// 	return (empty_quotes_token());
	if ((lex->dq || lex->sq))
		return (unclosed_quote_token());
	return (word_token_value(start, lex));
}

/**
 * Creates and returns a new token representing the end of file (EOF).
 *
 * @return pointer to the newly created token, NULL if malloc fails.
 */

t_token	*eof_token(void)
{
	t_token	*token;

	token = (t_token *)malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->type = END;
	token->value = NULL;
	token->next = NULL;
	return (token);
}
