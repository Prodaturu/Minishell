/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trosinsk <trosinsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 08:54:44 by sprodatu          #+#    #+#             */
/*   Updated: 2024/05/29 20:25:42 by trosinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char *ft_strnstr(const char *haystack, const char *needle, size_t len) {
  size_t i;
  size_t j;
  size_t ndl_len;

  ndl_len = ft_strlen(needle);
  i = 0;
  if (*needle == '\0')
    return ((char *)haystack);
  while (haystack[i] && (i + ndl_len <= len)) {
    j = 0;
    while (haystack[i + j] == needle[j] && (i + j) < len) {
      if (needle[j + 1] == '\0')
        return ((char *)(haystack + i));
      j++;
    }
    i++;
  }
  return (NULL);
}
