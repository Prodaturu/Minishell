/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execve.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trosinsk <trosinsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 19:36:47 by trosinsk          #+#    #+#             */
/*   Updated: 2024/05/30 00:10:42 by trosinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char **env_join(t_env *tmp, char **env) {
  int i;
  char *tmp1;

  i = 0;
  while (tmp) {
    tmp1 = ft_strjoin(tmp->env_name, "=");
    env[i] = ft_strjoin(tmp1, tmp->env_value);
    free(tmp1);
    i++;
    tmp = tmp->next;
  }
  env[i] = NULL;
  return (env);
}

char **env_to_char(t_env *env_s) {
  int i;
  char **env;
  t_env *tmp;

  i = 0;
  tmp = env_s;
  while (tmp) {
    i++;
    tmp = tmp->next;
  }
  env = malloc(sizeof(char *) * (i + 1));
  if (env == NULL)
    return (NULL);
  i = 0;
  tmp = env_s;
  env = env_join(tmp, env);
  return (env);
}

char *my_getenv(char *name, char **env) {
  int i;
  int j;
  char *sub;

  i = 0;
  while (env[i]) {
    j = 0;
    while (env[i][j] && env[i][j] != '=')
      j++;
    sub = ft_substr(env[i], 0, j);
    if (ft_strcmp(sub, name) == 0) {
      free(sub);
      return (env[i] + j + 1);
    }
    free(sub);
    i++;
  }
  return (NULL);
}

char *get_path(char *cmd, char **env) {
  int i;
  char *exec;
  char **allpath;
  char *path_part;

  i = -1;
  allpath = ft_split(my_getenv("PATH", env), ':');
  while (allpath[++i]) {
    path_part = ft_strjoin(allpath[i], "/");
    exec = ft_strjoin(path_part, cmd);
    free(path_part);
    if (access(exec, F_OK | X_OK) == 0)
      return (exec);
    free(exec);
  }
  i = 0;
  while (allpath[i])
    free(allpath[i++]);
  free(allpath);
  return (cmd);
}

void ft_execve(t_cmd *cmd, t_env **env_s, t_ms *mini) {
  if (!cmd->args)
    exit(1);
  if (cmd->args[0] == NULL)
    exit(0);
  mini->env = env_to_char(*env_s);
  if (mini->env == NULL) {
    free_struct(env_s);
    exit(1);
  }
  if (execve(get_path(cmd->args[0], mini->env), cmd->args, mini->env)) {
    free_array(mini->env, 0);
    free_struct(env_s);
    ft_putstr_fd("minishel: ", 2);
    ft_putstr_fd(cmd->args[0], 2);
    ft_putstr_fd(": ", 2);
    ft_putendl_fd("command not found", 2);
    exit(127);
  }
}
