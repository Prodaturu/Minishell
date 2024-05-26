/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_helper.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sprodatu <sprodatu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 19:35:32 by sprodatu          #+#    #+#             */
/*   Updated: 2024/05/26 05:04:29 by sprodatu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

/**
 * Creates a word token with the specified value.
 *
 * @param start The starting index of the word in the input string.
 * @param lex The lexical analyzer structure.
 * @return A pointer to created word token, or NULL if malloc fails.
 * 
 * The word token is created by copying substring of input string
 * starting from the specified index and ending at the current position.
 * The token type is set to the WORD and
 * The value is set to the copied substring.
 * Then the created token is returned.
 */

t_token	*word_token_value(int start, t_lex *lex)
{
	t_token	*token;
	char	*value;

	value = ft_substr(lex->input, start, lex->pos - start);
	token = (t_token *)malloc(sizeof(t_token));
	if (!value || !token)
		return (free(value), NULL);
	token->type = WORD;
	token->value = value;
	return (token);
}

/**
 * @brief Handles the quoting of token values.
 * 
 * Toggles flags of single quotes (') and double quotes (") 
 * based on the input character and the current state of the lexer.
 * 
 * @param l The lexer object.
 * @param q The input character representing the quote type.
 * 
 * Quote modes:
 * 1. Single quote mode: l->sq = 1
 * 2. Double quote mode: l->dq = 1
 * 3. Exit single quote mode: l->sq = 0
 * 4. Exit double quote mode: l->dq = 0
 * 
 * If the input character is a single quote (') and
 * the lexer is not in quote mode and
 * the previous character is not an escape character,
 * then enter single quote mode.
 * 
 * If the input character is a single quote (') and
 * the lexer is in single quote mode and
 * the lexer is not in double quote mode and
 * the previous character is not an escape character,
 * then exit single quote mode.
 * 
 * If the input character is a double quote (") and
 * the lexer is not in quote mode and
 * the previous character is not an escape character,
 * then enter double quote mode.
 * 
 * If the input character is a double quote (") and
 * the lexer is not in single quote mode and
 * the lexer is in double quote mode and
 * the previous character is not an escape character,
 * then exit double quote mode.
 */

void	quote_token_value(t_lex *l, char q)
{
	if (q == '\'' && !l->sq && !l->dq)
		l->sq = 1;
	else if (q == '\'' && l->sq && !l->dq
		&& (l->input[l->pos + 1] == '\''))
		l->sq = 0;
	else if (q == '\"' && !l->sq && !l->dq)
		l->dq = 1;
	else if (q == '\"' && !l->sq && l->dq
		&& (l->input[l->pos] == '\"'))
		l->dq = 0;
}

// if (q == '\'' && !l->sq && !l->dq && l->input[l->pos - 1] != '\\')
// 		l->sq = 1;
// 	else if (q == '\'' && l->sq && !l->dq && l->input[l->pos - 1] != '\\')
// 		l->sq = 0;
// 	else if (q == '\"' && !l->sq && !l->dq && l->input[l->pos - 1] != '\\')
// 		l->dq = 1;
// 	else if (q == '\"' && !l->sq && l->dq && l->input[l->pos - 1] != '\\')
// 		l->dq = 0;
// 	l->pos++;

// void	quote_token_value(t_lex *l, char q)
// {
// 	if (q == '\'' && !l->sq && !l->dq && l->input[l->pos - 1] != '\\')
// 		l->sq = 1;
// 	else if (q == '\'' && l->sq && !l->dq && l->input[l->pos - 1] != '\\')
// 		l->sq = 0;
// 	else if (q == '\"' && !l->sq && !l->dq && l->input[l->pos - 1] != '\\')
// 	{
// 		l->dq = 1;
// 	}
// 	else if (q == '\"' && !l->sq && l->dq && l->input[l->pos - 1] != '\\')
// 		l->dq = 0;
// 	l->pos++;
// }

/**
 * @brief Creates an unclosed quote token.
 * 
 * Creates a token with the type ERR and the value "Unclosed quote".
 * 
 * @return A pointer to the created token, or NULL if malloc fails.
 * 
 * Create a token and set the type to ERR and the value to "Unclosed quote".
 * set next to NULL
 * return the created token.
 */

t_token	*unclosed_quote_token(void)
{
	t_token	*token;

	token = (t_token *)malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->type = ERR;
	printf("ERROR: Unclosed quote----------\n");
	token->value = ft_strdup("Unclosed quote");
	token->next = NULL;
	return (token);
}

// void	*unclosed_quote_token(t_lex *l)
// {
// 	if (l->sq)
// 		printf("ERROR: Unclosed single quote\n");
// 	else if (l->dq)
// 		printf("ERROR: Unclosed double quote\n");
// 	return ;
// }
