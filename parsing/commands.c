/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trosinsk <trosinsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 01:38:12 by sprodatu          #+#    #+#             */
/*   Updated: 2024/05/30 00:09:59 by trosinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int new_cmd(t_cmd **prev, t_token **token, t_cmd **cmd) {
  t_cmd *new;

  new = malloc(sizeof(t_cmd));
  if (!new)
    return (perror("ERROR! malloc fail"), 0);
  new->prev = *prev;
  new->args = NULL;
  new->next = NULL;
  new->fd_in = STDIN_FILENO;
  new->fd_out = STDOUT_FILENO;
  if (*prev)
    (*prev)->next = new;
  if (!*cmd)
    *cmd = new;
  *prev = new;
  if ((*token)->prev && (*token)->prev->type != PIPE)
    *token = (*token)->next;
  return (1);
}

int create_cmds(t_token *token, t_cmd **cmds) {
  t_cmd *cmd;

  cmd = NULL;
  while (token->type != END) {
    if ((token->prev == NULL || token->prev->type == PIPE) &&
        !new_cmd(&cmd, &token, cmds))
      return (0);
    else if (token->type != PIPE && !get_args(&token, cmd))
      return (0);
    else if (token->type == PIPE)
      token = token->next;
  }
  return (1);
}

int commands(t_ms *ms) {
  t_token *token;
  t_cmd *cmd;

  cmd = NULL;
  token = ms->token;
  if (!create_cmds(token, &cmd))
    return (0);
  if (cmd != NULL)
    ms->cmd = cmd;
  return (1);
}
