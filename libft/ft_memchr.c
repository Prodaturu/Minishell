/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sprodatu <sprodatu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 07:25:31 by sprodatu          #+#    #+#             */
/*   Updated: 2023/10/31 14:14:23 by sprodatu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			index;
	unsigned char	*ptr;

	index = 0;
	ptr = (unsigned char *)s;
	while (index < n)
	{
		if (*(ptr + index) == (unsigned char)c)
			return ((void *)(ptr + index));
		index++;
	}
	return (NULL);
}

// void    *ft_memchr(const void *str, int c, size_t n)
// {
//     unsigned char   *cstr;
//     unsigned char   cc;
//     size_t          i;
//     i = 0;
//     cstr = (unsigned char *)str;
//     cc = (unsigned char)c;
//     while (i < n)
//     {
//         if (cstr[i] == c)
//             return (cstr + i);
//         i++;
//     }
//     return (NULL);
// }