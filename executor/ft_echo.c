/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trosinsk <trosinsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 12:22:14 by trosinsk          #+#    #+#             */
/*   Updated: 2024/05/28 23:48:49 by trosinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_echo(char **str, int n_flag, int i, t_ms *ms)
{
	ms->exit_code = 1;
	if (str[1])
	{
		while (str[i])
		{
			printf("%s", str[i]);
			if (str[i + 1])
				printf(" ");
			i++;
		}
	}
	if (!n_flag)
		printf("\n");
	ms->exit_code = 0;
}

void	ft_echo_prep(char **cmd, t_env **env_s, t_ms *ms)
{
	int		n_flag;
	int		i;
	int		j;
	char	*str;

	(void)env_s;
	n_flag = 0;
	i = 1;
	j = 0;
	str = ft_strdup(cmd[1]);
	if (cmd[1] && !ft_strncmp(cmd[1], "-n", 2))
	{
		j = 1;
		while (str[j] == 'n')
		{
			i = 2;
			if (str[j] == '\0')
				break ;
			j++;
		}
		n_flag = 1;
	}
	free(str);
	ft_echo(cmd, n_flag, i, ms);
}
