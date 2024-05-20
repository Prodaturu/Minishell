/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_helper.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sprodatu <sprodatu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 19:02:46 by sprodatu          #+#    #+#             */
/*   Updated: 2024/05/20 05:42:11 by sprodatu         ###   ########.fr       */
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
				return (perror("ERROR! strdup fail"), 0);
		}
		else
		{
			(*cmd)->args[index] = redirect_to_str(*token);
			if (!(*cmd)->args[index])
				return (0);
		}
		*token = (*token)->next;
		index++;
	}
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
		return (0);
	return (1);
}
