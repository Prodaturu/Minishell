/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sprodatu <sprodatu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 23:53:55 by sprodatu          #+#    #+#             */
/*   Updated: 2024/05/26 02:59:02 by sprodatu         ###   ########.fr       */
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

// Helper function implementations
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
	int		ep;
	char	*expansion;
	char	*temp;
	int		sp;

	sp = *i;
	while (str[*i] && ft_isalnum(str[*i]))
	{
		(*i)++;
		ep = *i;
	}
	temp = ft_substr(str, sp, ep - sp);
	expansion = get_env(temp, ms->env);
	free(temp);
	if (!expansion)
		return (0);
	*ex_str = ft_strnjoin(*ex_str, expansion, ft_strlen(expansion));
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

// void	merge_helper(char **new, char ***array1, char **array2, int *i)
// {
// 	int	j;
// 	int	k;
// 	int	l;

// 	j = 0;
// 	l = (*i);
// 	while (j < l)
// 	{
// 		new[j] = (*array1)[j];
// 		j++;
// 	}
// 	k = 0;
// 	while (array2[k])
// 	{
// 		new[j] = array2[k];
// 		j++;
// 		k++;
// 	}
// 	l++;
// 	while ((*array1)[l])
// 	{
// 		new[j] = (*array1)[l++];
// 		j++;
// 	}
// 	new[j] = NULL;
// }

// // Merges two arrays and updates the first array
// void	merge_arrays(char ***array1, char **array2, int *i)
// {
// 	char	**new_array;
// 	int		size1;
// 	int		size2;

// 	size1 = 0;
// 	size2 = 0;
// 	while ((*array1)[size1])
// 		size1++;
// 	while (array2[size2])
// 		size2++;
// 	new_array = malloc(sizeof(char *) * (size1 + size2 + 1));
// 	if (!new_array)
// 		return ;
// 	merge_helper(new_array, array1, array2, i);
// 	free(*array1);
// 	*array1 = new_array;
// }

// // Joins two strings with a specified length for the second string
// char	*ft_strnjoin(char *s1, char *s2, int n)
// {
// 	char	*str;
// 	int		i;
// 	int		j;

// 	i = 0;
// 	if (!s1 && !s2)
// 		return (NULL);
// 	str = (char *)malloc((strlen(s1) + n + 1) * sizeof(char));
// 	if (!str)
// 		return (NULL);
// 	while (s1 && s1[i] != '\0')
// 	{
// 		str[i] = s1[i];
// 		i++;
// 	}
// 	j = 0;
// 	while (s2 && s2[j] != '\0' && j < n)
// 	{
// 		str[i + j] = s2[j];
// 		j++;
// 	}
// 	str[i + j] = '\0';
// 	if (s1)
// 		free(s1);
// 	return (str);
// }

// // Retrieves the value of an environment variable
// char	*get_env(const char *name, char **env)
// {
// 	int	name_len;
// 	int	i;

// 	name_len = strlen(name);
// 	i = 0;
// 	while (env && env[i])
// 	{
// 		if (strncmp(env[i], name, name_len) == 0 && env[i][name_len] == '=')
// 		{
// 			return (&(env[i][name_len + 1]));
// 		}
// 		i++;
// 	}
// 	return (NULL);
// }

// // Prints the commands and their arguments
// void	print_cmds(t_ms *mini)
// {
// 	int		i;
// 	t_cmd	*temp;

// 	temp = mini->cmd;
// 	while (temp)
// 	{
// 		i = 0;
// 		printf("Command:\t FD_IN: %d  FD_OUT: %d\n", \
// 		temp->fd_in, temp->fd_out);
// 		while (temp->args && temp->args[i])
// 		{
// 			printf("\tArg%d: <%s>\n", i, temp->args[i]);
// 			i++;
// 		}
// 		temp = temp->next;
// 	}
// }
