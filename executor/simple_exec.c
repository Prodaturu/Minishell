/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_exec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trosinsk <trosinsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 21:22:21 by trosinsk          #+#    #+#             */
/*   Updated: 2024/05/27 20:25:40 by trosinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_cmd *find_last_node(t_cmd *cmd) {
  t_cmd *tmp;

  tmp = cmd;
  while (tmp->next)
    tmp = tmp->next;
  return (tmp);
}

int *set_fds(t_ms *mini) {
  int *fd;

  fd = malloc(sizeof(int) * 4);
  if (fd == NULL)
    return (NULL);
  fd[0] = dup(STDIN_FILENO);
  fd[1] = dup(STDOUT_FILENO);
  fd[2] = mini->cmd->fd_in;
  fd[3] = mini->cmd->fd_out;
  return (fd);
}

void set_builtin(char **args, t_env *env_s, int *fd, t_ms *mini) {
  exec_builtin(args, &env_s, mini);
  dup2(fd[0], STDIN_FILENO);
  dup2(fd[1], STDOUT_FILENO);
}

void set_pipes(t_cmd *cmd, int *fd) {
  if (STDIN_FILENO != cmd->fd_in) {
    dup2(fd[2], STDIN_FILENO);
    close(cmd->fd_in);
  }
  if (STDOUT_FILENO != cmd->fd_out) {
    dup2(fd[3], STDOUT_FILENO);
    close(cmd->fd_out);
  }
}

void simple_exec(t_ms *mini) {
  int pid;
  int status;
  int *fd;

  if (!mini->cmd->args || (ft_strchr(mini->cmd->args[0], '/') &&
                           check_if_file_exits(mini, mini->cmd->args[0])))
    return;
  fd = set_fds(mini);
  set_pipes(mini->cmd, fd);
  if (is_builtin(mini->cmd))
    return (set_builtin(mini->cmd->args, mini->env_s, fd, mini), free(fd));
  g_signal = 1;
  pid = fork();
  if (pid == -1)
    exit(EXIT_FAILURE);
  if (pid == 0)
    ft_execve(mini->cmd, &mini->env_s, mini);
  dup2(fd[0], STDIN_FILENO);
  dup2(fd[1], STDOUT_FILENO);
  free(fd);
  waitpid(pid, &status, 0);
  mini->exit_code = WEXITSTATUS(status);
  g_signal = 0;
}
