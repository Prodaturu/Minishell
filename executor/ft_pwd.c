/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trosinsk <trosinsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 16:37:50 by trosinsk          #+#    #+#             */
/*   Updated: 2024/05/26 02:47:59 by trosinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_pwd(t_env **env_s, t_ms *ms)
{
	char	*pwd;

	ms->exit_code = 1;
	pwd = ft_getenv("PWD", *env_s);
	printf("%s\n", pwd);
	ms->exit_code = 0;
}

void	ft_pwd_prep(char **cmd, t_env **env_s, t_ms *ms)
{
	(void)cmd;
	ft_pwd(env_s, ms);
}
