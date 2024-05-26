/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sprodatu <sprodatu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 23:45:19 by sprodatu          #+#    #+#             */
/*   Updated: 2024/05/26 05:02:51 by sprodatu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// static void	replace_and_free_args(char ***args, int *n, int *s_flag)
// {
// 	char	*temp;
// 	char	**new_args;
// 	char	**split_args;
// 	int		i, j, k;

// 	*s_flag = 0;
// 	temp = (*args)[*n];
// 	split_args = ft_split(temp, ' ');
// 	free(temp);
// 	for (i = 0; (*args)[i]; i++);
// 	for (j = 0; split_args[j]; j++);
// 	new_args = malloc(sizeof(char *) * (i + j));
// 	for (i = 0, k = 0; (*args)[i]; i++, k++)
// 		if (i == *n)
// 			for (j = 0; split_args[j]; j++, k++)
// 				new_args[k] = split_args[j];
// 		else
// 			new_args[k] = (*args)[i];
// 	new_args[k] = NULL;
// 	free(*args);
// 	free(split_args);
// 	*args = new_args;
// }

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
	free(temp);
	if (!split_args)
		return ;
	new_args = allocate_new_args(*args, temp, split_args, n);
	if (!new_args)
	{
		free(split_args);
		return ;
	}
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
	expanded_str = malloc(1);
	while (str[i])
	{
		if (str[i] == '\'')
			handle_squotes(str, &i, &expanded_str);
		else if (str[i] == '\"')
			handle_dquotes(str, &i, &expanded_str, ms);
		else if (str[i] == '$')
			handle_expansion(str, &i, &expanded_str, ms);
		else
			expanded_str = ft_strnjoin(expanded_str, &str[i], 1);
		i++;
	}
	if (expanded_str)
	{
		free(*s);
		*s = expanded_str;
		*s_flag = 1;
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
		printf("cmd->args: %s\n", ms->cmd->args[i]);
		while (ms->cmd->args && ms->cmd->args[i])
		{
			if (check_and_expand(&ms->cmd->args[i], ms, &s_flag))
			{
				if (s_flag)
				{
					replace_and_free_args(&ms->cmd->args, &i, &s_flag); // Update arguments if expansion occurred
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

/**
 * Expands the arguments in the given command structure.
 * 
 * @param ms The main shell structure.
 * 
 * @return 1 on success, 0 on failure.
 * 
 * @details This function expands the arguments in the given command structure.
 * It iterates through the command structure and expands the arguments in each
 * command. It uses the check_and_expand function to check and expand the
 * arguments. If an argument is successfully expanded, the function sets the
 * s_flag to 1. If the s_flag is set to 1, the function replaces the argument
 * with the expanded argument and frees the old argument. The function then
 * returns 1 on success.
 */

// int	expander(t_ms *ms)
// {
// 	t_cmd	*temp;
// 	int		i;
// 	int		s_flag;

// 	s_flag = 0;
// 	temp = ms->cmd;
// 	while (ms->cmd)
// 	{
// 		i = 0;
// 		while (ms->cmd->args && ms->cmd->args[i])
// 		{
// 			if (!check_and_expand(&ms->cmd->args[i], ms, &s_flag))
// 			{
// 				remove_element(&ms->cmd->args, i);
// 				i--;
// 			}
// 			if (s_flag == 1)
// 				replace_and_free_args(&ms->cmd->args, &i, &s_flag);
// 			i++;
// 		}
// 		ms->cmd = ms->cmd->next;
// 	}
// }

// // Helper function for handle_quotes and handle_dquotes
// int	handle_quotes(char *str, int *i, char **ex_str)
// {
// 	int	sp;
// 	int	ep;

// 	(*i)++;
// 	sp = *i;
// 	if (str[*i] == '\'')
// 	{
// 		(*i)++;
// 		return (1);
// 	}
// 	while (str[*i] && str[*i] != '\'')
// 	{
// 		(*i)++;
// 		ep = *i;
// 	}
// 	(*i)++;
// 	*ex_str = ft_strnjoin(*ex_str, &str[sp], ep - sp);
// 	if (!(*ex_str))
// 		return (0);
// 	return (1);
// }

// // Helper function for check_and_ex_helper
// void	check_and_ex_helper(char *str, char **es, t_ms *ms, int *sf)
// {
// 	int	i;

// 	i = 0;
// 	while (str[i])
// 	{
// 		if (str[i] == '\'')
// 			handle_quotes(str, &i, es);
// 		else if (str[i] == '\"')
// 			handle_dquotes(str, &i, es, ms);
// 		else if (str[i] == '$' && str[i + 1])
// 		{
// 			if (handle_expansion(str, &i, es, ms))
// 				*sf = 1;
// 		}
// 		else
// 			*es = ft_strnjoin(*es, &str[i++], 1);
// 	}
// }

// // Helper function for replace_and_free_args
// void	replace_and_free_args(char ***args, int *n, int *s_flag)
// {
// 	char	*temp;
// 	char	**temp1;
// 	char	**temp2;

// 	*s_flag = 0;
// 	temp = (*args)[*n];
// 	temp1 = ft_split((*args)[*n], ' ');
// 	temp2 = *args;
// 	merge_arrays(args, temp1, n);
// 	free(temp);
// 	free(temp1);
// 	free(temp2);
// }

// // Main function for checking and expanding strings
// int	check_and_expand(char **s, t_ms *ms, int *s_flag)
// {
// 	char	*expanded_str;
// 	char	*str;

// 	expanded_str = NULL;
// 	str = *s;
// 	check_and_ex_helper(str, &expanded_str, ms, s_flag);
// 	if (!expanded_str)
// 		return (0);
// 	else
// 	{
// 		free(str);
// 		*s = expanded_str;
// 	}
// 	return (1);
// }

// // Main expander function
// int	expand(t_ms *ms)
// {
// 	t_cmd	*temp;
// 	int		i;
// 	int		s_flag;

// 	s_flag = 0;
// 	temp = ms->cmd;
// 	while (ms->cmd)
// 	{
// 		i = 0;
// 		while (ms->cmd->args && ms->cmd->args[i])
// 		{
// 			if (!check_and_expand(&ms->cmd->args[i], ms, &s_flag))
// 			{
// 				remove_element(&ms->cmd->args, i);
// 				i--;
// 			}
// 			if (s_flag == 1)
// 				replace_and_free_args(&ms->cmd->args, &i, &s_flag);
// 			i++;
// 		}
// 		ms->cmd = ms->cmd->next;
// 	}
// 	ms->cmd = temp;
// 	return (1);
// }
