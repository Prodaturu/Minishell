/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trosinsk <trosinsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 04:50:47 by sprodatu          #+#    #+#             */
/*   Updated: 2024/05/30 00:05:50 by trosinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_lex *lexer_init(t_ms *ms) {
  t_lex *lexer;

  lexer = (t_lex *)malloc(sizeof(t_lex));
  if (!lexer)
    return (NULL);
  lexer->input = ms->input;
  lexer->dq = 0;
  lexer->sq = 0;
  lexer->pos = 0;
  return (lexer);
}

t_token *get_token(t_lex *lexer) {
  int input_len;
  char current_char;

  input_len = ft_strlen(lexer->input);
  while (lexer->pos < input_len) {
    current_char = lexer->input[lexer->pos];
    if (ft_isspace(current_char))
      lexer->pos++;
    else if (current_char == '|')
      return (pipe_token(lexer));
    else if (current_char == '<')
      return (in_token(lexer));
    else if (current_char == '>')
      return (out_token(lexer));
    else if ((current_char == '\'' || current_char == '\"') &&
             lexer->input[lexer->pos + 1] == current_char)
      return (lexer->pos++, lexer->pos++, empty_quotes_token());
    else
      return (word_token(lexer));
  }
  return (eof_token());
}

int lexing(t_ms *ms) {
  t_lex *lexer;
  t_token *token;

  lexer = lexer_init(ms);
  if (!lexer || !lexer->input)
    return (0);
  ms->token = get_token(lexer);
  if (!ms->token)
    return (0);
  ms->token->prev = NULL;
  token = ms->token;
  while (token->type != END) {
    token->next = get_token(lexer);
    if (!token->next || token->type == ERR) {
      ms->exit_code = 258;
      ft_putstr_fd("Error! unclosed quotes\n", 2);
      return (free(lexer), 0);
    }
    token->next->prev = token;
    token = token->next;
  }
  return (free(lexer), 1);
}
