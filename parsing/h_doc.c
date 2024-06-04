/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   h_doc.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trosinsk <trosinsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 01:53:31 by sprodatu          #+#    #+#             */
/*   Updated: 2024/05/30 22:46:09 by trosinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int ft_strcmp(const char *s1, const char *s2) {
  if ((*s1 != *s2) || (*s1 == '\0') || (*s2 == '\0'))
    return ((unsigned char)*s1 - (unsigned char)*s2);
  while (*s1 && (*s1 == *s2)) {
    s1++;
    s2++;
  }
  return (*(unsigned char *)s1 - *(unsigned char *)s2);
}

void heredoc(int fd, char *del, t_ms *mini) {
  char *line;

  while (1) {
    line = readline(">");
    if (!ft_strcmp(line, del)) {
      free(line);
      break;
    }
    if (ft_strchr(line, '$')) {
      check_and_expand(&line, mini, 0);
    }
    ft_putendl_fd(line, fd);
    free(line);
  }
}

void remove_element(char ***array_ptr, int index) {
  char **array;
  int size;
  int i;

  i = index;
  array = *array_ptr;
  size = 0;
  while (array[size] != NULL)
    size++;
  free(array[index]);
  while (i < size - 1) {
    array[i] = array[i + 1];
    i++;
  }
  array[size - 1] = NULL;
}

void remove_cmd_node(t_ms *mini, t_cmd *node_to_remove) {
  int i;

  if (mini == NULL || node_to_remove == NULL)
    return;
  if (node_to_remove == mini->cmd)
    mini->cmd = node_to_remove->next;
  if (node_to_remove->prev != NULL)
    node_to_remove->prev->next = node_to_remove->next;
  if (node_to_remove->next != NULL)
    node_to_remove->next->prev = node_to_remove->prev;
  if (node_to_remove->fd_in != STDIN_FILENO)
    close(node_to_remove->fd_in);
  if (node_to_remove->fd_out != STDOUT_FILENO)
    close(node_to_remove->fd_out);
  if (node_to_remove->args != NULL) {
    i = 0;
    while (node_to_remove->args[i]) {
      free(node_to_remove->args[i]);
      i++;
    }
    free(node_to_remove->args);
  }
  free(node_to_remove);
}
