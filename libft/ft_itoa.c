/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sprodatu <sprodatu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 18:28:34 by sprodatu          #+#    #+#             */
/*   Updated: 2023/10/17 07:47:59 by sprodatu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_numlen(int n)
{
	int	temp;
	int	count;

	count = 0;
	temp = n;
	if (temp == 0)
		return (1);
	if (temp < 0)
	{
		temp = -temp;
		count++;
	}
	while (temp > 0)
	{
		temp = temp / 10;
		count++;
	}
	return (count);
}

int	ft_isneg(int n)
{
	if (n < 0)
		return (1);
	return (0);
}

int	ft_rem(int n)
{
	if (n < 0)
		return (-1 * (n % 10));
	return (n % 10);
}

char	*ft_itoa(int n)
{
	char	*str;
	size_t	length;
	int		is_neg;

	if (n == 0)
		return (ft_strdup("0"));
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	length = ft_numlen(n);
	str = (char *)malloc(length + 1);
	if (!str)
		return (0);
	is_neg = ft_isneg(n);
	str[length] = '\0';
	while (n != 0)
	{
		length--;
		str[length] = '0' + ft_rem(n);
		n /= 10;
	}
	if (is_neg)
		str[0] = '-';
	return (str);
}
