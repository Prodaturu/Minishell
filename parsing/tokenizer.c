/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trosinsk <trosinsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 06:45:45 by sprodatu          #+#    #+#             */
/*   Updated: 2024/05/30 00:06:18 by trosinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_token *pipe_token(t_lex *lexer) {
  t_token *token;

  token = (t_token *)malloc(sizeof(t_token));
  if (!token)
    return (NULL);
  token->type = PIPE;
  token->value = ft_strdup("|");
  return (lexer->pos++, token);
}

t_token *in_token(t_lex *lexer) {
  t_token *token;

  token = (t_token *)malloc(sizeof(t_token));
  if (!token)
    return (NULL);
  if (lexer->input[lexer->pos + 1] == '<') {
    token->type = H_DOC;
    token->value = ft_strdup("<<");
    return (lexer->pos += 2, token);
  } else {
    token->type = IN;
    token->value = ft_strdup("<");
    return (lexer->pos++, token);
  }
}

t_token *out_token(t_lex *lexer) {
  t_token *token;

  token = (t_token *)malloc(sizeof(t_token));
  if (!token)
    return (NULL);
  if (lexer->input[lexer->pos + 1] == '>') {
    token->type = APPEND;
    token->value = ft_strdup(">>");
    return (lexer->pos += 2, token);
  } else {
    token->type = OUT;
    token->value = ft_strdup(">");
    return (lexer->pos++, token);
  }
}

t_token *empty_quotes_token(void) {
  t_token *token;

  token = (t_token *)malloc(sizeof(t_token));
  if (!token)
    return (NULL);
  token->type = WORD;
  token->value = ft_strdup("");
  return (token);
}

t_token *word_token(t_lex *lex) {
  int start;

  start = lex->pos;
  while (lex->input[lex->pos]) {
    if (lex->input[lex->pos] == '\'' || lex->input[lex->pos] == '\"')
      quote_token_value(lex, lex->input[lex->pos]);
    if ((ft_isspace(lex->input[lex->pos]) || lex->input[lex->pos] == '|' ||
         lex->input[lex->pos] == '<' || lex->input[lex->pos] == '>') &&
        !(lex->dq || lex->sq))
      break;
    lex->pos++;
  }
  if ((lex->dq || lex->sq))
    return (unclosed_quote_token());
  return (word_token_value(start, lex));
}
