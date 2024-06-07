/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sprodatu <sprodatu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 23:53:55 by sprodatu          #+#    #+#             */
/*   Updated: 2024/05/31 01:02:30 by sprodatu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int handle_pid_exitcode_ex(const char *str, int *i, char **ex_str, t_ms *ms) {
  char *expansion;

  if (str[*i] == '$') {
    (*i)++;
    expansion = ft_itoa((int)getpid());
    if (!expansion)
      return (0);
    *ex_str = ft_strnjoin(*ex_str, expansion, ft_strlen(expansion));
    free(expansion);
  } else if (str[*i] == '?') {
    (*i)++;
    expansion = ft_itoa(ms->exit_code);
    if (!expansion)
      return (0);
    *ex_str = ft_strnjoin(*ex_str, expansion, ft_strlen(expansion));
    free(expansion);
  }
  return (1);
}

char *ft_strnjoin(char *s1, const char *s2, size_t n) {
  char *str;
  size_t len1;

  if (!s1 && !s2)
    return (NULL);
  len1 = ft_strlen(s1);
  str = (char *)malloc((len1 + n + 1) * sizeof(char));
  if (!str)
    return (NULL);
  if (s1)
    ft_strlcpy(str, s1, len1 + 1);
  else
    *str = '\0';
  ft_strnjoin_helper(str + len1, s2, n);
  if (s1)
    free(s1);
  return (str);
}

int handle_dquotes(char *str, int *i, char **ex_str, t_ms *ms) {
  if (*i < (int)ft_strlen(str))
    (*i)++;
  while (str[(*i) + 1] && str[*i] != '\"') {
    if (str[*i] == '$' && str[(*i) + 1] != '\"' && str[(*i) + 1] != ' ') {
      handle_expansion(str, i, ex_str, ms);
      (*i)--;
    } else
      *ex_str = ft_strnjoin(*ex_str, &str[*i], 1);
    (*i)++;
  }
  if (*i < (int)ft_strlen(str))
    (*i)++;
  return (1);
}

int handle_squotes(char *str, int *i, char **ex_str) {
  int start;
  int end;

  start = ++(*i);
  end = ft_strlen(str);
  while (str[*i] && str[*i] != '\'')
    (*i)++;
  *ex_str = ft_strnjoin(*ex_str, &str[start], *i - start);
  if (*i < end)
    (*i)++;
  return (1);
}

int handle_expansion(char *str, int *i, char **ex_str, t_ms *ms) {
  if (*i < (int)ft_strlen(str))
    (*i)++;
  if (str[*i] == '$' || str[*i] == '?')
    return (handle_pid_exitcode_ex(str, i, ex_str, ms));
  expand_and_join(str, i, ex_str, ms);
  return (1);
}
