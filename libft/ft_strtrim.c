/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sprodatu <sprodatu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 09:44:10 by sprodatu          #+#    #+#             */
/*   Updated: 2023/10/25 21:52:20 by sprodatu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(const char *s1, const char *set)
{
	char	*new_string;
	int		start;
	int		end;
	int		length;

	if (!s1 && !set)
		return ((char *)s1);
	start = 0;
	end = ft_strlen(s1) - 1;
	while ((s1[start]) && (ft_strrchr(set, s1[start])))
		start++;
	while ((end > start) && (ft_strrchr(set, s1[end])))
		end--;
	length = end - start + 1;
	new_string = (char *)malloc(length + 1);
	if (new_string == NULL)
		return (NULL);
	ft_memcpy(new_string, s1 + start, length);
	new_string[length] = '\0';
	return (new_string);
}

// #include "libft.h"

// int	ft_chrcmp(char c, char *set)
// {
// 	int	i;

// 	i = -1;
// 	while (set[++i])
// 		if (set[i] == c)
// 			return (1);
// 	return (0);
// }

// char	*ft_strtrim(char const *s1, char const *set)
// {
// 	size_t	i;
// 	size_t	n;
// 	char	*s1_cpy;
// 	size_t	j;

// 	j = 0;
// 	i = 0;
// 	n = ft_strlen(s1) - 1;
// 	while (ft_chrcmp(s1[i], (char *)set) && s1[i])
// 		i++;
// 	while (ft_chrcmp(s1[n], (char *)set) && n > i)
// 		n--;
// 	if (!s1)
// 		s1_cpy = malloc(sizeof(char));
// 	else
// 		s1_cpy = malloc(sizeof(char) * (n - i + 2));
// 	if (!s1_cpy)
// 		return (NULL);
// 	while (i < n + 1)
// 		s1_cpy[j++] = s1[i++];
// 	s1_cpy[j] = '\0';
// 	return (s1_cpy);
// }
