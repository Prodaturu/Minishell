/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sprodatu <sprodatu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 05:39:19 by sprodatu          #+#    #+#             */
/*   Updated: 2024/05/19 17:12:29 by sprodatu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * Checks for redirection errors in command line input.
 * 
 * @param token Pointer to t_token structure.
 * 
 * @return 1 if redirection error is found, 0 otherwise.
 * 
 * If token is NULL or a redirection, print err msg & return 1.
 * If token is the first token, print err msg & return 1.
 * If token is not a WORD, print err msg & return 1.
*/

int	redir_error_check(t_token *token)
{
	if (token->next == NULL || token->next->type == IN
		|| token->next->type == H_DOC || token->next->type == OUT
		|| token->next->type == APPEND)
		return (printf("ERROR! unexpected token `%s'\n", token->value), 1);
	else if (token->prev == NULL)
		return (printf("ERROR! unexpected token `%s'\n", token->value), 1);
	else if (token->prev->type != WORD)
		return (printf("ERROR! unexpected token `%s'\n", token->value), 1);
	return (0);
}

/**
 * Checks for pipe errors in command line input.
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
	int	exit_code;

	while (ms->token)
	{
		if (ms->token->type == PIPE)
		{
			exit_code = pipe_error_check(ms->token);
			if (exit_code != 0)
			{
				ms->exit_code = exit_code;
				return (exit_code);
			}
		}
		if (ms->token->type == IN || ms->token->type == H_DOC
			|| ms->token->type == OUT || ms->token->type == APPEND)
		{
			exit_code = redir_error_check(ms->token);
			if (exit_code != 0)
			{
				ms->exit_code = exit_code;
				return (exit_code);
			}
		}
		ms->token = ms->token->next;
	}
	return (0);
}
