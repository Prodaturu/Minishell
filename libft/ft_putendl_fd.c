/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sprodatu <sprodatu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 14:35:53 by sprodatu          #+#    #+#             */
/*   Updated: 2023/10/17 17:37:37 by sprodatu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putendl_fd(char *s, int fd)
{
	size_t	length;

	length = 0;
	if (s == NULL)
		return ;
	while (s[length] != '\0')
		length++;
	write(fd, s, length);
	write(fd, "\n", 1);
}
