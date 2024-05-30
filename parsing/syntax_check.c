/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trosinsk <trosinsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 05:39:19 by sprodatu          #+#    #+#             */
/*   Updated: 2024/05/30 00:07:41 by trosinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

int	pipe_error_check(t_token *token)
{
	if (token->next == NULL || token->next->type == END
		|| token->prev == NULL || token->prev->type != WORD)
		return (ft_putstr_fd("ERROR! unexpected token `|'\n", 2), 1);
	return (0);
}

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
