/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sprodatu <sprodatu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 23:45:19 by sprodatu          #+#    #+#             */
/*   Updated: 2024/06/02 14:24:38 by sprodatu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**allocate_new_args(char **args, const char *temp, char **split_args, int *n)
{
	int		i;
	int		j;
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
	new_args = new_args_maker(new_args, args, split_args, n);
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

char	*str_expander(char *expanded_str, char *str, int *s_flag, t_ms *ms)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(str);
	while (i < len)
	{
		if (str[i] == '\'' || str[i] == '\"' || str[i] == '$')
		{
			if (str[i] == '\'')
				handle_squotes(str, &i, &expanded_str);
			else if (str[i] == '\"')
				handle_dquotes(str, &i, &expanded_str, ms);
			else if (str[i] == '$')
			{
				*s_flag = 1;
				handle_expansion(str, &i, &expanded_str, ms);
			}
			i--;
		}
		else
			expanded_str = ft_strnjoin(expanded_str, &str[i], 1);
		i++;
	}
	return (expanded_str);
}

int	check_and_expand(char **s, t_ms *ms, int *s_flag)
{
	char	*expanded_str;
	char	*str;

	str = *s;
	expanded_str = NULL;
	expanded_str = str_expander(expanded_str, str, s_flag, ms);
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

	temp = ms->cmd;
	while (ms->cmd)
	{
		process_args(ms->cmd, ms);
		ms->cmd = ms->cmd->next;
	}
	ms->cmd = temp;
}
