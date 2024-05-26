/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trosinsk <trosinsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 23:45:19 by sprodatu          #+#    #+#             */
/*   Updated: 2024/05/26 10:07:21 by trosinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**allocate_new_args(char **args, char *temp, char **split_args, int *n)
{
	int		i;
	int		j;
	int		k;
	char	**new_args;

	i = 0;
	while (args[i])
		i++;
	j = 0;
	while (split_args[j])
		j++;
	new_args = malloc(sizeof(char *) * (i + j));
	if (!new_args)
		return (NULL);
	i = 0;
	k = 0;
	while (args[i])
	{
		if (i == *n)
		{
			j = 0;
			while (split_args[j])
				new_args[k++] = split_args[j++];
		}
		else
			new_args[k++] = args[i];
		i++;
	}
	new_args[k] = NULL;
	return ((void) temp, new_args);
}

void	replace_and_free_args(char ***args, int *n, int *s_flag)
{
	char	*temp;
	char	**split_args;
	char	**new_args;

	*s_flag = 0;
	temp = (*args)[*n];
	split_args = ft_split(temp, ' ');
	if (!split_args)
		return ;
	new_args = allocate_new_args(*args, temp, split_args, n);
	if (!new_args)
	{
		free(split_args);
		return ;
	}
	free(temp);
	free(*args);
	free(split_args);
	*args = new_args;
}

int	handle_expansion(char *str, int *i, char **ex_str, t_ms *ms)
{
	(*i)++;
	if (str[*i] == '$' || str[*i] == '?')
		return (handle_pid_exitcode_ex(str, i, ex_str, ms));
	return (expand_and_join(str, i, ex_str, ms));
}

int	check_and_expand(char **s, t_ms *ms, int *s_flag)
{
	char	*expanded_str;
	char	*str;
	int		i;

	str = *s;
	i = 0;
	expanded_str = NULL;
	while (str[i])
	{
		if (str[i] == '\'')
			handle_squotes(str, &i, &expanded_str);
		else if (str[i] == '\"')
			handle_dquotes(str, &i, &expanded_str, ms);
		else if (str[i] == '$')
		{
			*s_flag = 1; //just to check flow
			handle_expansion(str, &i, &expanded_str, ms);
		}
		else
			expanded_str = ft_strnjoin(expanded_str, &str[i], 1);
		i++;
	}
	if (expanded_str)
	{
		free(*s);
		*s = expanded_str;
		return (1);
	}
	return (0);
}

void	expand(t_ms *ms)
{
	t_cmd	*temp;
	int		i;
	int		s_flag;

	temp = ms->cmd;
	while (ms->cmd)
	{
		i = 0;
		s_flag = 0;
		while (ms->cmd->args && ms->cmd->args[i])
		{
			if (check_and_expand(&ms->cmd->args[i], ms, &s_flag))
			{
				if (s_flag)
				{
					replace_and_free_args(&ms->cmd->args, &i, &s_flag);
					i++;
					break ;
				}
				else
					i++;
			}
			else
				i++;
		}
		ms->cmd = ms->cmd->next;
	}
	ms->cmd = temp;
}
