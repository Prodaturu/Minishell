/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trosinsk <trosinsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 19:37:53 by trosinsk          #+#    #+#             */
/*   Updated: 2024/05/26 03:02:07 by trosinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_change_shellvl(t_ms *mini)
{
	char	*shell_lvl;
	char	*new_lvl;
	char	*tmp;

	shell_lvl = ft_getenv("SHLVL", mini->env_s);
	if (!shell_lvl)
		return ;
	new_lvl = ft_itoa(ft_atoi(shell_lvl) + 1);
	tmp = ft_strjoin("SHLVL=", new_lvl);
	ft_export(tmp, &mini->env_s, mini);
	free(new_lvl);
	free(tmp);
}

int	ft_alnum_check(char *name, char *arg, int j, t_ms *ms)

{
	if (!ft_isalnum(arg[j]) && arg[j] != '_')
	{
		identifier_error(name, arg, ms);
		return (0);
	}
	return (1);
}

int	ft_alpha_check(char *name, char *cmd, t_ms *ms)
{
	if (!ft_isalpha(cmd[0]) && cmd[0] != '_')
	{
		identifier_error(name, cmd, ms);
		return (0);
	}
	return (1);
}
