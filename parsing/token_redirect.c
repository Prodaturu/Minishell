/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_redirect.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sprodatu <sprodatu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 06:45:45 by sprodatu          #+#    #+#             */
/*   Updated: 2024/05/15 17:10:56 by sprodatu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * Handles the pipe token in the lexer.
 * 
 * @param lexer The lexer object.
 * @return A pointer to created token, or NULL if malloc fails.
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
		if (lex->input[lex->pos] == '\'' || lex->input[lex->pos] == '"')
			quote_token(lex);
		if (ft_isspace(lex->input[lex->pos]) && !(lex->dq || lex->sq))
			break ;
		if ((lex->input[lex->pos] == '|' || lex->input[lex->pos] == '<'
				|| lex->input[lex->pos] == '>') && !(lex->dq || lex->sq))
			break ;
		lex->pos++;
	}
	if (lex->dq || lex->sq)
		return (unclosed_quote_token(lex));
	return (word_token_value(start, lex));
}
