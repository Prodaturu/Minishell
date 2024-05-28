/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trosinsk <trosinsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 19:40:05 by trosinsk          #+#    #+#             */
/*   Updated: 2024/05/29 00:02:28 by trosinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*env_strdup(t_env *tmp, char **newenv)
{
	char	*str;

	free(tmp->env_value);
	str = ft_strdup(newenv[1]);
	free(newenv[0]);
	free(newenv[1]);
	return (str);
}

void	ft_export(char *name, t_env **env_s, t_ms *ms)
{
	t_env	*tmp;
	char	**newenv;

	newenv = ft_split(name, '=');
	if (newenv[1])
	{
		tmp = *env_s;
		while (tmp)
		{
			if (ft_strncmp(tmp->env_name, newenv[0], ft_strlen(newenv[0])) == 0)
			{
				tmp->env_value = env_strdup(tmp, newenv);
				return ;
			}
			tmp = tmp->next;
		}
		append_node(env_s, newenv[0], newenv[1]);
	}
	else
		free(newenv[0]);
	free(newenv);
	ms->env = env_to_char(*env_s);
	ms->exit_code = 0;
}

void	ft_export_prep(char **cmd, t_env **env_s, t_ms *ms)
{
	int		i;
	t_env	*tmp;

	tmp = *env_s;
	if (cmd[1] == NULL)
	{
		while (tmp)
		{
			printf("declare -x %s=\"%s\"\n", tmp->env_name, tmp->env_value);
			tmp = tmp->next;
		}
		ms->exit_code = 0;
	}
	i = 1;
	while (cmd[i])
	{
		if (input_checker(cmd[0], cmd[i], ms, env_s))
		{
			ft_export(cmd[i], env_s, ms);
		}
		i++;
	}
}
