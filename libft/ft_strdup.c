/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sprodatu <sprodatu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 05:48:02 by sprodatu          #+#    #+#             */
/*   Updated: 2023/11/09 00:20:46 by sprodatu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*new_string;
	size_t	length;

	length = ft_strlen(s1);
	new_string = (char *)malloc(length + 1);
	if (new_string == NULL)
		return (NULL);
	ft_memcpy(new_string, s1, length);
	new_string[length] = '\0';
	return (new_string);
}
// char	*ft_strdup(const char *s1)
// {
// 	char	*new_string;
// 	size_t	length;

// 	length = ft_strlen(s1);
// 	new_string = (char *)malloc(length + 1);
// 	if (new_string == NULL)
// 		return (NULL);

// 	return (ft_memcpy(new_string, s1, length),new_string);
// }