/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sprodatu <sprodatu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 01:18:36 by sprodatu          #+#    #+#             */
/*   Updated: 2024/05/17 05:41:00 by sprodatu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_tokens(t_token *token)
{
	t_token	*temp;

	while (token)
	{
		temp = token->next;
		free(token->value);
		free(token);
		token = temp;
	}
}

/**
 * Parses the input command line and performs necessary operations.
 * 
 * @param mini A pointer to the t_mini structure representing the mini shell.
 * @return Returns 1 if the parsing is successful, 0 otherwise.
 */

int	parse(t_ms *ms)
{
	if (!lexing(ms))
		return (free_tokens(ms->token), 0);
	if (syntax_error(ms))
		return (free_tokens(ms->token), 0);
	return (free_tokens(ms->token), 1);
}

	// if (syntax_error(ms))
	// 	return (free_tokens(ms->token), 0);
	// if (!commands(ms))
	// 	return (free_tokens(ms->token), 0);
	// if (!expander(ms))
	// 	return (free_tokens(ms->token), 0);
	// if (!redirections(ms))
	// 	return (free_tokens(ms->token), 0);

// parse function:
// 1. Call lexing function.
// 2. If lexing function returns 0, free tokens and return 0.
// 3. Call syntax_error function.
// 4. If syntax_error function returns 1, free tokens and return 0.
// 5. Call commands function.
// 6. If commands function returns 0, free tokens and return 0.
// 7. Call expander function.
// 8. If expander function returns 0, free tokens and return 0.
// 9. Call redirections function.
// 10. If redirections function returns 0, free tokens and return 0.
// 11. free tokens and return 1.
