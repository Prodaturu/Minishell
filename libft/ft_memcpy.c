/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sprodatu <sprodatu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 00:54:51 by sprodatu          #+#    #+#             */
/*   Updated: 2024/04/13 05:25:56 by sprodatu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t					index;
	unsigned char			*ptr;

	index = 0;
	ptr = (unsigned char *)dst;
	if (!dst && !src)
		return (0);
	while (index < n)
	{
		*(ptr + index) = *((const unsigned char *) src + index);
		index++;
	}
	return (dst);
}
