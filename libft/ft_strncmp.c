/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sprodatu <sprodatu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 05:10:53 by sprodatu          #+#    #+#             */
/*   Updated: 2023/10/12 07:19:03 by sprodatu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	index;

	index = 0;
	while (index < n)
	{
		if ((*s1 != *s2) || (*s1 == '\0') || (*s2 == '\0'))
			return ((unsigned char)*s1 - (unsigned char)*s2);
		index++;
		s1++;
		s2++;
	}
	return (0);
}
