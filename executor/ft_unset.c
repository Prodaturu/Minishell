/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trosinsk <trosinsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 19:39:42 by trosinsk          #+#    #+#             */
/*   Updated: 2024/05/26 02:48:02 by trosinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	unset_1st(t_env **env_s, t_ms *ms)
{
	t_env	*tmp;
	t_env	*prev;
	t_env	*node_to_free;

	if (!env_s || !*env_s)
		return ;
	tmp = *env_s;
	prev = NULL;
	free(tmp->env_value);
	free(tmp->env_name);
	if (tmp->next)
	{
		node_to_free = tmp->next;
		tmp->env_name = node_to_free->env_name;
		tmp->env_value = node_to_free->env_value;
		tmp->next = node_to_free->next;
		free(node_to_free);
	}
	else
	{
		free(tmp);
		*env_s = NULL;
	}
	ms->exit_code = 0;
}

void	unset_next(t_env *tmp, t_env *prev, t_ms *ms)
{
	t_env	*node_to_free;

	node_to_free = tmp;
	prev->next = tmp->next;
	free(node_to_free->env_value);
	free(node_to_free->env_name);
	free(node_to_free);
	ms->exit_code = 0;
}

void	ft_unsetenv(char *name, t_env **env_s, t_ms *ms)
{
	t_env	*tmp;
	t_env	*prev;

	if (!name || !env_s || !*env_s)
		return ;
	tmp = *env_s;
	prev = NULL;
	ms->exit_code = 1;
	if (ft_strncmp(tmp->env_name, name, ft_strlen(name) + 1) == 0)
	{
		unset_1st(env_s, ms);
		return ;
	}
	while (tmp)
	{
		if (ft_strncmp(tmp->env_name, name, ft_strlen(name) + 1) == 0)
		{
			unset_next(tmp, prev, ms);
			return ;
		}
		prev = tmp;
		tmp = tmp->next;
	}
	ms->env = env_to_char(*env_s);
	ms->exit_code = 0;
}

void	ft_unset_prep(char **cmd, t_env **env_s, t_ms *ms)
{
	int		i;
	int		j;

	if (!cmd[1])
	{
		ms->exit_code = 0;
		return ;
	}
	i = 1;
	while (cmd[i])
	{
		j = 1;
		if (!ft_alpha_check(cmd[0], cmd[i], ms))
			break ;
		while (cmd[i][j])
		{
			if (!ft_alnum_check(cmd[0], cmd[i], j, ms))
				break ;
			j++;
		}
		ft_unsetenv(cmd[i], env_s, ms);
		i++;
	}
}
