/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sprodatu <sprodatu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 05:39:19 by sprodatu          #+#    #+#             */
/*   Updated: 2024/05/17 17:04:55 by sprodatu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * Checks for syntax errors in command line input.
 * 
 * @param ms Pointer to t_ms structure.
 * 
 * @return 1 if syntax error is found, 0 otherwise.
 *
 * Checks in a loop while token is not NULL.
 * 		If token type is PIPE, check for pipe error.
 * 		If token type is IN, H_DOC, OUT, or APPEND, check for redir error.
 * 		return the result of the error check.
 * else return 0.
 */

int	syntax_error(t_ms *ms)
{
	while (ms->token)
	{
		if (ms->token->type == PIPE)
			return (pipe_error_check(ms->token));
		if (ms->token->type == IN || ms->token->type == H_DOC
			|| ms->token->type == OUT || ms->token->type == APPEND)
			return (redir_error_check(ms->token));
		ms->token = ms->token->next;
	}
	return (0);
}

/**
 * Checks for redirection errors in command line input.
 * 
 * @param token Pointer to t_token structure.
 * 
 * @return 1 if redirection error is found, 0 otherwise.
 * 
 * If token is NULL or a pipe, print err msg & return 1.
 * If token is the first token, print err msg & return 1.
 * If token is not a WORD, print err msg & return 1.
*/

int	pipe_error_check(t_token *token)
{
	if (token->next == NULL || token->next->type == PIPE)
		return (printf("syntax error near unexpected token `|'\n"), 1);
	else if (token->prev == NULL)
		return (printf("syntax error near unexpected token `|'\n"), 1);
	else if (token->prev->type == PIPE)
		return (printf("syntax error near unexpected token `|'\n"), 1);
	else if (token->prev->type != WORD)
		return (printf("syntax error near unexpected token `|'\n"), 1);
	return (0);
}
