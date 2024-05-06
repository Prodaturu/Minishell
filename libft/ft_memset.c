/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sprodatu <sprodatu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 02:17:39 by sprodatu          #+#    #+#             */
/*   Updated: 2023/10/09 23:02:03 by sprodatu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	size_t			length;
	unsigned char	*start;

	length = 0;
	start = (unsigned char *) b;
	while (length < len)
	{
		*start = (unsigned char) c;
		length++;
		start++;
	}
	return (b);
}
