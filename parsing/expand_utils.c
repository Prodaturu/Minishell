/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trosinsk <trosinsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 23:53:55 by sprodatu          #+#    #+#             */
/*   Updated: 2024/05/27 00:05:54 by trosinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

int	handle_pid_exitcode_ex(char *str, int *i, char **ex_str, t_ms *ms)
{
	char	*expansion;

	if (str[*i] == '$')
	{
		(*i)++;
		expansion = ft_itoa((int)getpid());
		if (!expansion)
			return (0);
		*ex_str = ft_strnjoin(*ex_str, expansion, ft_strlen(expansion));
		free(expansion);
	}
	else if (str[*i] == '?')
	{
		(*i)++;
		expansion = ft_itoa(ms->exit_code);
		if (!expansion)
			return (0);
		*ex_str = ft_strnjoin(*ex_str, expansion, ft_strlen(expansion));
		free(expansion);
	}
	return (1);
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
		return (0);
	*ex_str = ft_strnjoin(*ex_str, expansion, ft_strlen(expansion));
	ft_setenv(temp, expansion, 1, ms->env_s);
	free(temp);
	return (1);
}

int	handle_dquotes(char *str, int *i, char **ex_str, t_ms *ms)
{
	(*i)++;
	while (str[*i] && str[*i] != '\"')
	{
		if (str[*i] == '$' && str[(*i) + 1] != '\"' && str[(*i) + 1] != ' ')
			handle_expansion(str, i, ex_str, ms);
		else
			*ex_str = ft_strnjoin(*ex_str, &str[*i], 1);
		(*i)++;
	}
	(*i)++;
	return (1);
}

int	handle_squotes(char *str, int *i, char **ex_str)
{
	int	start;

	start = ++(*i);
	while (str[*i] && str[*i] != '\'')
		(*i)++;
	*ex_str = ft_strnjoin(*ex_str, &str[start], *i - start);
	(*i)++;
	return (1);
}
