/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sprodatu <sprodatu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 09:07:00 by sprodatu          #+#    #+#             */
/*   Updated: 2023/10/17 10:24:50 by sprodatu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	unsigned int	length;
	unsigned int	index;

	index = 0;
	length = ft_strlen(s);
	if (!s || !f)
		return ;
	if (!s)
		return ;
	while (index < length)
	{
		f(index, &s[index]);
		index++;
	}
	return ;
}
