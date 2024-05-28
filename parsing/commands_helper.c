/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_helper.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trosinsk <trosinsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 19:02:46 by sprodatu          #+#    #+#             */
/*   Updated: 2024/05/29 00:13:30 by trosinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*redirect_to_str(t_token *token)
{
	char	*str;

	str = ft_strdup(token->value);
	if (!str)
		return (perror("ERROR! strdup fail"), NULL);
	return (str);
}

void	free_array(char **array, int index)
{
	int	i;

	i = 0;
	if (index == 0)
	{
		while (array[i])
		{
			free(array[i]);
			i++;
		}
	}
	else
	{
		while (i < index)
		{
			free(array[i]);
			i++;
		}
	}
	free(array);
}

int	fill_arg_array(int i, t_cmd **cmd, t_token **token)
{
	int	index;

	index = 0;
	while (index < i)
	{
		if ((*token)->type == WORD)
		{
			(*cmd)->args[index] = ft_strdup((*token)->value);
			if ((*cmd)->args[index] == NULL)
				return (perror("strdup fail"), free_array((*cmd)->args, 0), 0);
		}
		else
		{
			(*cmd)->args[index] = redirect_to_str(*token);
			if (!(*cmd)->args[index])
				return (free_array((*cmd)->args, 0), 0);
		}
		*token = (*token)->next;
		index++;
	}
	(*cmd)->args[i] = NULL;
	return (1);
}

int	get_args(t_token **token, t_cmd *cmd)
{
	int		i;
	t_token	*temp;

	temp = *token;
	i = 0;
	while (temp->type != PIPE && temp->type != END)
	{
		i++;
		temp = temp->next;
	}
	if (i == 0)
		return (1);
	cmd->args = malloc(sizeof(char *) * (i + 1));
	if (!cmd->args)
		return (ft_putstr_fd("ERROR! malloc fail\n", 2), 0);
	cmd->args[i] = NULL;
	if (!fill_arg_array(i, &cmd, token))
	{
		while (--i > 0)
			free(cmd->args[i]);
		free(cmd->args);
		return (0);
	}
	return (1);
}
