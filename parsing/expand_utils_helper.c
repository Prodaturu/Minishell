/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils_helper.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sprodatu <sprodatu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 00:00:35 by sprodatu          #+#    #+#             */
/*   Updated: 2024/05/26 03:57:16 by sprodatu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// void	remove_element(char ***array_ptr, int index)
// {
// 	char	**array;
// 	int		size;
// 	int		i;

// 	i = index;
// 	array = *array_ptr;
// 	size = 0;
// 	while (array[size] != NULL)
// 		size++;
// 	free(array[index]);
// 	while (i < size - 1)
// 	{
// 		array[i] = array[i + 1];
// 		i++;
// 	}
// 	array[size - 1] = NULL;
// }

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

char	*ft_strnjoin(char *s1, const char *s2, size_t n)
{
	char	*str;
	size_t	len1;
	size_t	len2;

	if (!s1 && !s2)
		return (NULL);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	str = (char *)malloc((len1 + n + 1) * sizeof(char));
	if (!str)
		return (NULL);
	if (s1)
		ft_strlcpy(str, s1, len1 + 1);
	else
		*str = '\0';
	ft_strnjoin_helper(str + len1, s2, n);
	if (s1)
		free(s1);
	return (str);
}



// int	handle_pid_exitcode_ex(char *str, int *i, char **ex_str, t_ms *m)
// {
// 	char	*expansion;

// 	if (str[*i] && str[*i] == '$')
// 	{
// 		(*i)++;
// 		expansion = ft_itoa((int)getpid());
// 		if (!expansion)
// 			return (0);
// 		*ex_str = ft_strnjoin(*ex_str, expansion, ft_strlen(expansion));
// 		if (!(*ex_str))
// 			return (0);
// 		free(expansion);
// 	}
// 	else if (str[*i] && str[*i] == '?')
// 	{
// 		(*i)++;
// 		expansion = ft_itoa(m->exit_code);
// 		if (!expansion)
// 			return (0);
// 		*ex_str = ft_strnjoin(*ex_str, expansion, ft_strlen(expansion));
// 		if (!ex_str)
// 			return (0);
// 		free(expansion);
// 	}
// 	return (1);
// }

// int	expand_and_join(char *str, int *i, char **ex_str, t_ms *mini)
// {
// 	int		ep;
// 	char	*expansion;
// 	char	*temp;
// 	int		sp;

// 	sp = (*i);
// 	while (str[*i] && ft_isalnum(str[*i]))
// 	{
// 		(*i)++;
// 		ep = *i;
// 	}
// 	temp = ft_substr(str, sp, ep - sp);
// 	expansion = get_env(temp, mini->env);
// 	if (!expansion || !expansion[0])
// 	{
// 		free(temp);
// 		return (0);
// 	}
// 	*ex_str = ft_strnjoin(*ex_str, expansion, ft_strlen(expansion));
// 	free(temp);
// 	return (1);
// }

// int	handle_dquotes(char *str, int *i, char **ex_str, t_ms *mini)
// {
// 	(*i)++;
// 	while (str[*i] && str[*i] != '\"')
// 	{
// 		if (str[*i] == '$' && str[(*i) + 1] != '\"' && str[(*i) + 1] != ' ')
// 			handle_expansion(str, i, ex_str, mini);
// 		else
// 		{
// 			*ex_str = ft_strnjoin(*ex_str, &str[*i], 1);
// 			(*i)++;
// 		}
// 	}
// 	(*i)++;
// 	return (1);
// }

// int	handle_expansion(char *str, int *i, char **ex_str, t_ms *mini)
// {
// 	(*i)++;
// 	if (str[*i] && (str[*i] == '$' || str[*i] == '?'))
// 	{
// 		if (!handle_pid_exitcode_ex(str, i, ex_str, mini))
// 			return (0);
// 	}
// 	else
// 	{
// 		if (!expand_and_join(str, i, ex_str, mini))
// 			return (0);
// 	}
// 	return (1);
// }
