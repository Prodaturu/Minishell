/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sprodatu <sprodatu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 19:24:20 by trosinsk          #+#    #+#             */
/*   Updated: 2024/05/25 21:40:05 by sprodatu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * @brief Merges two arrays of strings
 * 
 * @param arr1
 * @param arr2
 * @param index
 * 
 * @return void
 * 
 * @details
 * Creates a new array that can hold both arr1 and arr2
 * Copies all elements from arr1 and arr2 into the new array
 * Frees the old arr1 and sets it to the new array
 */
void	merge_arrays(char ***arr1, char **arr2, int *index)
{
	int		len1;
	int		len2;
	char	**new_arr;
	int		i;
	int		j;

	len1 = 0;
	len2 = 0;
	j = 0;
	i = 0;
	while ((*arr1)[len1])
		len1++;
	while (arr2[len2])
		len2++;
	new_arr = (char **)malloc(sizeof(char *) * (len1 + len2 + 1));
	if (!new_arr)
		return ;
	while (i < *index)
	{
		new_arr[i] = (*arr1)[i];
		i++;
	}
	while (j < len2)
	{
		new_arr[i] = arr2[j];
		i++;
		j++;
	}
	while ((*arr1)[*index])
	{
		new_arr[i] = (*arr1)[(*index)++];
		i++;
	}
	new_arr[i] = NULL;
	free(*arr1);
	*arr1 = new_arr;
}

// try this if below doesnt work:
// void	free_replace_args(char ***args, int *i, int *splits)
// {
// 	char	*to_split;
// 	char	**split_args;
// 	char	**org_args;

// 	*splits = 0;
// 	to_split = (*args)[*i];
// 	split_args = ft_split(to_split, ' ');
// 	org_args = *args;
// 	merge_arrays(args, split_args, i);
// 	free(to_split);
// 	free(org_args);
// 	free(split_args);
// 	return ;
// }

/**
 * @details
 * 
 * @param args
 * @param n
 * @param splits
 * 
 * @return void
 * 
 * @details
 * split the string into an argument array of strings
 * merge the arrays
 * free the temp string and the split_args
 * return void
*/

void	free_replace_args(char ***args, int *n, int *splits)
{
	char	*temp;
	char	**split_args;

	*splits = 0;
	temp = (*args)[*n];
	split_args = ft_split(temp, ' ');
	merge_arrays(args, split_args, n);
	free(temp);
	free(split_args);
}

/**
 * @brief Remove the element at the index i from the args
 * 
 * @param arr_ptr
 * @param index
 * 
 * @return void
 * 
 * @details
 * Remove each element from the array
 * set the last element to NULL (only one left)
*/

void	remove_element(char ***arr_ptr, int index)
{
	char	**arr;
	int		len;
	int		i;

	len = 0;
	arr = *arr_ptr;
	i = index;
	while (arr[len])
		len++;
	free(arr[index]);
	arr[len - 1] = NULL;
	while (i < len - 1)
	{
		arr[i] = arr[i + 1];
		i++;
	}
}

/**
 * @brief checks and expands the string
 * 
 * @param s
 * @param ms
 * @param s_flag
 * 
 * @return int
 * 
 * @details
 * check if the string needs an expander
 * 		the handle_string_exp function will expand the string
 * 		the expanded_str denotes whether we expanded the string or not
 * If there is no expanded string, return 0
 * if there is one, return 1
*/

int	check_expander(char **s, t_ms *ms, int *s_flag)
{
	char	*expanded_str;
	char	*str;

	str = *s;
	expanded_str = NULL;
	handle_string_exp(str, &expanded_str, ms, s_flag);
	if (!expanded_str)
		return (0);
	free (str);
	*s = expanded_str;
	return (1);
}

/**
 * Exapand function:
 *
 * @brief Expand the variables in the command
 *
 * @param ms
 *
 * @return void
 *
 * @details
 * we store the command in a variable
 * We will loop through the commands and the arguments
 * We will check if the argument is a variable
 * If it is a variable we will expand it
 * If the argument is a variable we will remove and replace it
 * 		with the expanded variable
 * after we are done with the command we will move to the next command
 * we exit loop and set the command to the original command
 * return void;
 * 
 * @example
 * 1. if the cmd was `ls $HOME`
 * 2. if home was set as `$HOME = /home/user`
 * 3. It would be expanded to `ls /home/user`
 */

void	expand(t_ms	*ms)
{
	t_cmd	*cmd;
	int		i;
	int		splits;

	splits = 0;
	cmd = ms->cmd;
	while (ms->cmd)
	{
		i = 0;
		while (ms->cmd->args && ms->cmd->args[i])
		{
			if (!check_expander(&ms->cmd->args[i], ms, &splits))
				remove_element(&ms->cmd->args, i--);
			if (splits == 1)
				free_replace_args(&ms->cmd->args, &i, &splits);
			i++;
		}
		ms->cmd = ms->cmd->next;
	}
	ms->cmd = cmd;
	return ;
}
