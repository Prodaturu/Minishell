/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trosinsk <trosinsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 19:40:05 by trosinsk          #+#    #+#             */
/*   Updated: 2024/05/26 02:47:58 by trosinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

//go back to head of linked list
static t_env	*find_last(t_env *env_s)
{
	t_env	*tmp;

	tmp = env_s;
	if (NULL == tmp)
		return (NULL);
	while (tmp->next)
		tmp = tmp->next;
	return (tmp);
}

static void	free_struct(t_env **stack)
{
	t_env	*tmp;
	t_env	*current;

	current = NULL;
	if (!stack)
		return ;
	while (current)
	{
		tmp = current->next;
		free(current);
		current = tmp;
	}
	*stack = NULL;
}

static void	append_node(t_env **env_s, char *token, char *type)
{
	t_env	*node;
	t_env	*last_node;

	if (NULL == env_s)
		return ;
	node = malloc(sizeof(t_env));
	if (NULL == node)
		return (free_struct(env_s), (void) NULL);
	node->next = NULL;
	node->env_name = ft_strdup(token);
	node->env_value = ft_strdup(type);
	if (NULL == *env_s)
		*env_s = node;
	else
	{
		last_node = find_last(*env_s);
		last_node->next = node;
	}
}

void	ft_export(char *name, t_env **env_s, t_ms *ms)
{
	t_env	*tmp;
	char	**newenv;

	ms->exit_code = 1;
	newenv = ft_split(name, '=');
	if (newenv[1])
	{
		tmp = *env_s;
		while (tmp)
		{
			if (ft_strncmp(tmp->env_name, newenv[0], ft_strlen(newenv[0])) == 0)
			{
				free(tmp->env_value);
				tmp->env_value = ft_strdup(newenv[1]);
				free(newenv[0]);
				free(newenv[1]);
				return ;
			}
			tmp = tmp->next;
		}
		append_node(env_s, newenv[0], newenv[1]);
		free(newenv[0]);
		free(newenv[1]);
	}
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
