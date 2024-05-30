/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils_helper.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sprodatu <sprodatu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 00:00:35 by sprodatu          #+#    #+#             */
/*   Updated: 2024/05/30 08:56:52 by sprodatu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_env(const char *name, char **env)
{
	int	name_len;
	int	i;

	name_len = ft_strlen(name);
	i = 0;
	while (env && env[i])
	{
		if (ft_strncmp(env[i], name, name_len) == 0 && env[i][name_len] == '=')
		{
			return (&(env[i][name_len + 1]));
		}
		i++;
	}
	return (NULL);
}

void	ft_strnjoin_helper(char *dest, const char *src, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n && src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
}

int	expand_and_join(char *str, int *i, char **ex_str, t_ms *ms)
{
	char	*expansion;
	char	*temp;
	int		sp;
	int		ep;

	sp = *i;
	while (str[*i] && ft_isalnum(str[*i]))
	{
		(*i)++;
		ep = *i;
	}
	temp = ft_substr(str, sp, ep - sp);
	expansion = get_env(temp, ms->env);
	if (!expansion)
		return (free(temp), 0);
	*ex_str = ft_strnjoin(*ex_str, expansion, ft_strlen(expansion));
	ft_setenv(temp, expansion, 1, ms->env_s);
	free(temp);
	return (1);
}

char	**new_args_maker(char **new_args, char **args, char **splt_args, int *n)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	k = 0;
	while (args[i])
	{
		if (i == *n)
		{
			j = 0;
			while (splt_args[j])
				new_args[k++] = splt_args[j++];
		}
		else
			new_args[k++] = args[i];
		i++;
	}
	new_args[k] = NULL;
	return (new_args);
}

void	process_args(t_cmd *cmd, t_ms *ms)
{
	int	i;
	int	s_flag;

	i = 0;
	s_flag = 0;
	while (cmd->args && cmd->args[i] != NULL)
	{
		if (check_and_expand(&cmd->args[i], ms, &s_flag))
		{
			if (s_flag)
			{
				replace_and_free_args(&cmd->args, &i, &s_flag);
				i++;
				continue ;
			}
			else
				i++;
		}
		else
			i++;
	}
}
