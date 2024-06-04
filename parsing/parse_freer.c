/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_freer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sprodatu <sprodatu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 02:06:58 by sprodatu          #+#    #+#             */
/*   Updated: 2024/05/30 13:08:37 by sprodatu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void free_tokens(t_token *token) {
  t_token *temp;

  while (token) {
    temp = token->next;
    free(token->value);
    free(token);
    token = temp;
  }
}
