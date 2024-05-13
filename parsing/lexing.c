/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sprodatu <sprodatu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 04:50:47 by sprodatu          #+#    #+#             */
/*   Updated: 2024/05/11 06:26:32 by sprodatu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	lexing(t_ms *ms)
{
	t_lex	*lexer;

	lexer_init(ms);
}

// lexer function:
// 1. Initialize the lexer with the input string.
// 2. Get the first token from the input.
// 3. Loop through input string & get next token until end of input.
// 4. Return the list of tokens.
