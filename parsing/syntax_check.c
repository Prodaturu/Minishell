/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sprodatu <sprodatu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 05:39:19 by sprodatu          #+#    #+#             */
/*   Updated: 2024/05/20 04:28:44 by sprodatu         ###   ########.fr       */
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
	if (token->next->type != WORD)
	{
		ft_putstr_fd("ERROR! unexpected token `", 2);
		ft_putstr_fd(token->value, 2);
		ft_putstr_fd("'\n", 2);
		return (1);
	}
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
	if (token->next == NULL || (token->next && token->next->type == END)
		|| token->prev == NULL || token->prev->type != WORD)
		return (ft_putstr_fd("ERROR! unexpected token `|'\n", 2), 1);
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
	t_token	*token;

	token = ms->token;
	while (token)
	{
		if (token->type == PIPE && pipe_error_check(token))
		{
			ms->exit_code = 258;
			return (1);
		}
		else if (token->type == IN || token->type == H_DOC
			|| token->type == OUT || token->type == APPEND
			&& (redir_error_check(token)) && token->type != WORD)
		{
			ms->exit_code = 258;
			return (1);
		}
		token = token->next;
	}
	return (0);
}
