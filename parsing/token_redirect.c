/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sprodatu <sprodatu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 06:45:45 by sprodatu          #+#    #+#             */
/*   Updated: 2024/05/15 08:41:30 by sprodatu         ###   ########.fr       */
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
	
}
