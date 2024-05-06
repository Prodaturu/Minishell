/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sprodatu <sprodatu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 02:28:27 by sprodatu          #+#    #+#             */
/*   Updated: 2023/10/14 06:09:04 by sprodatu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	src_length;
	char	*dst_ptr;
	char	*src_ptr;

	dst_ptr = (char *)dst;
	src_ptr = (char *)src;
	src_length = ft_strlen(src);
	if (dstsize == 0)
		return (ft_strlen(src));
	while (*src_ptr != '\0' && dstsize > 1)
	{
		*dst_ptr = *src_ptr;
		dst_ptr++;
		src_ptr++;
		dstsize--;
	}
	if (dstsize != 0)
		*dst_ptr = '\0';
	return (src_length);
}
