/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_helper.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sprodatu <sprodatu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 19:02:46 by sprodatu          #+#    #+#             */
/*   Updated: 2024/05/19 19:02:57 by sprodatu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


char	*redirect_to_str(t_token *token)
{
	char	*str;

	str = (char *)ft_calloc(3, sizeof(char));
	if (!str)
		return (perror("ERROR! malloc fail"), NULL);
	if (token->type == IN)
		ft_strlcpy(str, "<", 2);
	else if (token->type == OUT)
		ft_strlcpy(str, ">", 2);
	else if (token->type == APPEND)
		ft_strlcpy(str, ">>", 3);
	else if (token->type == H_DOC)
		ft_strlcpy(str, "<<", 3);
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
		return (perror("ERROR! No arguments"), 0);
	cmd->args = malloc(sizeof(char *) * (i + 1));
	if (!cmd->args)
		return (perror("ERROR! malloc fail"), 0);
	cmd->args[i] = NULL;
	if (!fill_arg_array(i, &cmd, token))
		return (0);
	return (1);
}
