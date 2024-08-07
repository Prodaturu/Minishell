/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trosinsk <trosinsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 12:25:12 by trosinsk          #+#    #+#             */
/*   Updated: 2024/05/30 00:10:48 by trosinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void ft_env(t_env **env_s, t_ms *ms) {
  t_env *tmp;

  ms->exit_code = 1;
  tmp = *env_s;
  while (tmp) {
    printf("%s=%s\n", tmp->env_name, tmp->env_value);
    tmp = tmp->next;
  }
  ms->exit_code = 0;
}

void ft_env_prep(char **cmd, t_env **env_s, t_ms *ms) {
  (void)cmd;
  ft_env(env_s, ms);
}
