/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sprodatu <sprodatu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 06:17:11 by sprodatu          #+#    #+#             */
/*   Updated: 2024/05/25 21:31:00 by sprodatu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*extract_var_name(char *s, int *i)
{
	char	*var_name;
	int		start;
	int		len;

	len = 0;
	start = *i + 1;
	while (isalnum(s[start + len]) || s[start + len] == '_')
		len++;
	var_name = malloc(len + 1);
	if (!var_name)
		return (NULL);
	strncpy(var_name, &s[start], len);
	var_name[len] = '\0';
	*i = start + len - 1;
	return (var_name);
}

/**
 * @brief Joins a string and a character
 *
 * @param s
 * @param c
 * @param len
 *
 * @return char*
 */

char	*ft_strjoin_char(char *s, char c, int len)
{
	char	*new_str;
	int		s_len;

	s_len = ft_strlen(s);
	new_str = malloc(s_len + len + 1);
	if (!new_str)
		return NULL;
	ft_strlcpy(new_str, s, s_len + 1); // Copies the string s to new_str
	new_str[s_len] = c; // Appends the character c to new_str
	new_str[s_len + 1] = '\0'; // Null-terminates the new string
	return (new_str);
}

/**
 * @brief Expands the values after the dollar to its actual value
 *
 * @param s
 * @param i
 * @param exp_s
 * @param ms
 *
 * @return void
 */

void	handle_dollar(char *s, int *i, char **exp_s, t_ms *ms)
{
	char	*var_name;
	char	*var_value;

	var_name = extract_var_name(s, i); // You need to implement this function
	var_value = getenv(var_name);
	if (var_value)
	{
		char *temp = *exp_s;
		*exp_s = ft_strjoin(*exp_s, var_value);
		free(temp);
	}
	free(var_name);
}

void	handle_dquotes(char *s, int *i, t_ms *ms, char **exp_s)
{
	while (s[++(*i)] && s[*i] != '\"')
	{
		if (s[*i] == '$' && s[*i + 1] != '\"' )
			handle_dollar(s, i, exp_s, ms);
		else
			*exp_s = ft_strjoin_char(*exp_s, &s[*i], 1);
	}
}

/**
 * @brief Handles single quotes and its exceptions
 *
 * @param s
 * @param i
 * @param exp_s
 * 
 * @return void
 * 
 * @details if we encounter a single quote, we skip the single quote
 * and store the string between the single quotes in exp_s
 * if we encounter a single quote again, we skip the single quote
 * and store the string between the single quotes in exp_s
 * else, we simply store the string in exp_s skipping code earlier
 */

void	handle_squotes(char *s, int *i, char **exp_s)
{
	int	start;
	int	end;

	start = ++(*i);
	if (s[*i] == '\'')
		return ((*i)++, (void)(start));
	while (s[*i] && s[*i] != '\'')
		(*i)++;
	end = *i;
	(*i)++;
	*exp_s = ft_strjoin_char(*exp_s, &s[start], end - start);
}

/**
 * @brief Handles quotes and dollar sign in the string
 * and stores the expanded string in exp_s
 *
 * @param s
 * @param exp_s
 * @param ms
 * @param sf
 *
 * @return void
 *
 * @details
 * Loop through the string values
 * if the value is a single quote, call handle_squotes
 * 		handles single quotes and its exceptions
 * if the value is a double quote, call handle_dquotes
 * 		handles double quotes and its exceptions
 * if the value is a dollar sign, call handle_dollar
 * 		expands the values after the dollar to its actual value
 * else, join the value to the expanded string
 *
 * All the above functions other than ft_strjoin_char;
 * create a new string and replace old string with the new string
 */

void	handle_string_exp(char **s, char **exp_s, t_ms *ms, int *sf)
{
	int		i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '\'')
			handle_squotes(s, &i, exp_s);
		else if (s[i] == '\"')
			handle_dquotes(s, &i, ms, exp_s);
		else if (s[i] == '$' && s[i + 1])
			sf = handle_dollar(s, &i, exp_s, ms);
		else
			*exp_s = ft_strjoin_char(*exp_s, &s[i++], 1);
	}
}
