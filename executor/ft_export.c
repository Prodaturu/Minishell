/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trosinsk <trosinsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 19:40:05 by trosinsk          #+#    #+#             */
/*   Updated: 2024/05/29 22:16:16 by trosinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	export_helper(char **new_env, t_env **env_s, t_ms *ms)
{
	free(new_env);
	ms->env = env_to_char(*env_s);
	ms->exit_code = 0;
}

char	*env_strdup(t_env *tmp, char **newenv)
{
	char	*str;

	free(tmp->env_value);
	str = ft_strdup(newenv[1]);
	free(newenv[0]);
	free(newenv[1]);
	return (str);
}

char	*env_strjoin(t_env *tmp, char **newenv)
{
	char	*str;

	str = ft_strjoin(tmp->env_value, newenv[1]);
	free(newenv[0]);
	free(tmp->env_value);
	free(newenv[1]);
	return (str);
}

void	ft_export(char *name, t_env **env_s, t_ms *ms)
{
	t_env	*tmp;
	char	*append_env;
	char	**newenv;

	newenv = ft_split(name, '=');
	if (ft_strnstr(newenv[0], "+", ft_strlen(newenv[0])))
	{
		append_env = ft_strdup(newenv[0]);
		free(newenv[0]);
		newenv[0] = ft_substr(append_env, 0, ft_strlen(append_env) - 1);
	}
	if (newenv[1])
	{
		tmp = *env_s;
		while (tmp)
		{
			if (ft_strncmp(tmp->env_name, newenv[0], ft_strlen(newenv[0])) == 0)
				return (new_env_exp(append_env, tmp, newenv), (void) NULL);
			tmp = tmp->next;
		}
		append_node(env_s, newenv[0], newenv[1]);
	}
	else
		free(newenv[0]);
	export_helper(newenv, env_s, ms);
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
