/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sprodatu <sprodatu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 13:49:55 by sprodatu          #+#    #+#             */
/*   Updated: 2023/10/22 14:00:14 by sprodatu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// funciton to count no of different strings

int	count_strings(char const *s, char delimiter)
{
	int	count;

	count = 0;
	while (*s)
	{
		while (*s == delimiter)
			s++;
		if (*s)
		{
			while (*s && *s != delimiter)
				s++;
			count++;
		}
	}
	return (count);
}

//  Function to free the memory when malloc fails
void	ft_free_split(char **s)
{
	int	i;

	if (s)
	{
		i = 0;
		while (s[i])
		{
			free(s[i]);
			i++;
		}
		free(s);
	}
}

// Allocating memory for count no of substrings and 
// 		returning the allocated memory address

char	**alloc_mem_for_substrs(int count)
{
	char	**result;

	result = (char **)malloc((count + 1) * sizeof(char *));
	if (!result)
		return (NULL);
	return (result);
}
// Fill the result array of arrays we created with substrings

char	**fill_substrs(char **result, const char *s, char c, int count)
{
	int		index;
	char	*start;
	char	*end;

	index = 0;
	while (index < count)
	{
		while (*s == c)
			s++;
		start = (char *)s;
		while ((*s) && (*s != c))
			s++;
		end = (char *)s;
		result[index] = (char *)malloc(end - start + 1);
		if (!result[index])
		{
			ft_free_split(result);
			return (NULL);
		}
		ft_memcpy(result[index], start, end - start);
		result[index][end - start] = '\0';
		index++;
	}
	result[index] = NULL;
	return (result);
}

char	**ft_split(char const *s, char c)
{
	int		count;
	char	**result;

	if (!s)
		return (NULL);
	count = count_strings(s, c);
	result = alloc_mem_for_substrs(count);
	if (!result)
	{
		ft_free_split(result);
		return (NULL);
	}
	return (fill_substrs(result, s, c, count));
}
