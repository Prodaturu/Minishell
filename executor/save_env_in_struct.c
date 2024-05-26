/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_env_in_struct.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trosinsk <trosinsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 19:27:16 by trosinsk          #+#    #+#             */
/*   Updated: 2024/05/26 02:46:32 by trosinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

//changing way of saving env, from char to struct

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
	if (type)
		node->env_value = ft_strdup(type);
	if (NULL == *env_s)
		*env_s = node;
	else
	{
		last_node = find_last(*env_s);
		last_node->next = node;
	}
}

t_env	*save_env(char **env, t_env *env_struct)
{
	char	**env_split;
	int		i;

	i = 0;
	while (env[i])
	{
		env_split = ft_split(env[i], '=');
		if (env_split[0] && !env_split[1])
			env_split[1] = "";
		append_node(&env_struct, env_split[0], env_split[1]);
		i++;
	}
	return (env_struct);
}
			// env_split[1] = "(null)"; l76
//free instead of break
