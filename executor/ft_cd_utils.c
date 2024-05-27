/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trosinsk <trosinsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 18:09:55 by trosinsk          #+#    #+#             */
/*   Updated: 2024/05/27 23:58:34 by trosinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static t_env	*find_last(t_env *env_s)
{
	if (NULL == env_s)
		return (NULL);
	while (env_s->next)
		env_s = env_s->next;
	return (env_s);
}

static void	free_struct(t_env **stack)
{
	t_env	*tmp;
	t_env	*current;

	if (!stack)
		return ;
	current = NULL;
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

void	ft_setenv(char *name, char *value, int overwrite, t_env *env_s)
{
	t_env	*tmp;

	tmp = env_s;
	while (tmp)
	{
		if (ft_strncmp(tmp->env_name, name, ft_strlen(name)) == 0)
		{
			if (overwrite == 1)
			{
				tmp->env_value = ft_strdup(value);
				free(value);
			}
			return ;
		}
		tmp = tmp->next;
	}
	append_node(&tmp, name, value);
	// free(name);
	// free(value);
	env_s = tmp;
}
