/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trosinsk <trosinsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 18:09:55 by trosinsk          #+#    #+#             */
/*   Updated: 2024/05/30 20:42:24 by trosinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void ft_setenv(char *name, char *value, int overwrite, t_env *env_s) {
  t_env *tmp;
  char *new_value;

  tmp = env_s;
  while (tmp) {
    if (ft_strncmp(tmp->env_name, name, ft_strlen(name)) == 0) {
      if (overwrite == 1) {
        new_value = ft_strdup(value);
        free(tmp->env_value);
        tmp->env_value = new_value;
      }
      return;
    }
    tmp = tmp->next;
  }
  append_node(&tmp, name, value);
  env_s = tmp;
}
