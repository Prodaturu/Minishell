/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_helper.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sprodatu <sprodatu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 19:35:32 by sprodatu          #+#    #+#             */
/*   Updated: 2024/05/17 04:45:00 by sprodatu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

void	quote_token_value(t_lex *l, char q)
{
	if (q == '\'' && !l->sq && !l->dq && l->input[l->pos - 1] != '\\')
		l->sq = 1;
	else if (q == '\'' && l->sq && !l->dq && l->input[l->pos - 1] != '\\')
		l->sq = 0;
	else if (q == '\"' && !l->sq && !l->dq && l->input[l->pos - 1] != '\\')
		l->dq = 1;
	else if (q == '\"' && !l->sq && l->dq && l->input[l->pos - 1] != '\\')
		l->dq = 0;
	l->pos++;
}

t_token	*unclosed_quote_token(void)
{
	t_token	*token;

	token = (t_token *)malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->type = ERR;
	token->value = ft_strdup("Unclosed quote");
	token->next = NULL;
	return (token);
}

// void	*unclosed_quote_token(t_lex *l)
// {
// 	if (l->sq)
// 		printf("ERROR: Unclosed single quote\n");
// 	else if (l->dq)
// 		printf("ERROR: Unclosed double quote\n");
// 	return ;
// }