/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sprodatu <sprodatu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 05:39:19 by sprodatu          #+#    #+#             */
/*   Updated: 2024/05/20 08:09:05 by sprodatu         ###   ########.fr       */
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
 * If next token is not a WORD,
 * 		print err msg & return 1.
 * else return 0.
*/

int	redir_error_check(t_token *token)
{
	if (!token->next || token->next->type != WORD)
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
 * If next token is NULL or a pipe or end,
 * If token is the first token i.e prev is NULL or
 * If prev token is not a WORD
 * 		print err msg & return 1.
 * else return 0.
 * 
 * CHECKED & WORKING
*/

int	pipe_error_check(t_token *token)
{
	if (token->next == NULL || token->next->type == END
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
 * Loop through the tokens.
 * If token is a pipe and pipe error is found,
 * 		set exit code to 258 & return 1.
 * If token is a redirection and redirection error is found,
 * 		set exit code to 258 & return 1.
 * 	Both the above conditions print an custom error message.
 * Return 0.
 * 
 * CHECKED & WORKING
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
		else if ((token->type == IN || token->type == H_DOC
				|| token->type == OUT || token->type == APPEND)
			&& redir_error_check(token) && token->type != WORD)
		{
			ms->exit_code = 258;
			return (1);
		}
		token = token->next;
	}
	return (0);
}
