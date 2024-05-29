/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trosinsk <trosinsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 19:37:53 by trosinsk          #+#    #+#             */
/*   Updated: 2024/05/29 22:01:45 by trosinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_change_shellvl(t_ms *mini, int i)
{
	char	*shell_lvl;
	char	*new_lvl;

	shell_lvl = ft_getenv("SHLVL", mini->env_s);
	if (!shell_lvl)
		return ;
	if (i == 0)
		new_lvl = ft_itoa(ft_atoi(shell_lvl) - 1);
	else
		new_lvl = ft_itoa(ft_atoi(shell_lvl) + 1);
	ft_setenv("SHLVL", new_lvl, 1, mini->env_s);
	free(new_lvl);
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
