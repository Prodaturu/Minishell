/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sprodatu <sprodatu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 05:39:19 by sprodatu          #+#    #+#             */
/*   Updated: 2024/05/17 06:33:02 by sprodatu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
