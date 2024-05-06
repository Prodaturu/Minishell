/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sprodatu <sprodatu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 08:01:39 by sprodatu          #+#    #+#             */
/*   Updated: 2023/10/17 10:12:47 by sprodatu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	length;
	char			*new_str;
	unsigned int	index;

	index = 0;
	length = ft_strlen(s);
	if (!s || !f)
		return (NULL);
	new_str = (char *)malloc(length + 1);
	if (!new_str)
		return (NULL);
	while (index < length)
	{
		new_str[index] = f(index, s[index]);
		index++;
	}
	new_str[length] = '\0';
	return (new_str);
}
