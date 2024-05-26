/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils_helper.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trosinsk <trosinsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 00:00:35 by sprodatu          #+#    #+#             */
/*   Updated: 2024/05/26 06:57:42 by trosinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_env(const char *name, char **env)
{
	int	name_len;
	int	i;

	name_len = ft_strlen(name);
	i = 0;
	while (env && env[i])
	{
		if (ft_strncmp(env[i], name, name_len) == 0 && env[i][name_len] == '=')
		{
			return (&(env[i][name_len + 1]));
		}
		i++;
	}
	return (NULL);
}

char	*ft_strnjoin(char *s1, const char *s2, size_t n)
{
	char	*str;
	size_t	len1;
	size_t	len2;

	if (!s1 && !s2)
		return (NULL);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	str = (char *)malloc((len1 + n + 1) * sizeof(char));
	if (!str)
		return (NULL);
	if (s1)
		ft_strlcpy(str, s1, len1 + 1);
	else
		*str = '\0';
	ft_strnjoin_helper(str + len1, s2, n);
	if (s1)
		free(s1);
	return (str);
}
