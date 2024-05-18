/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sprodatu <sprodatu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 01:38:12 by sprodatu          #+#    #+#             */
/*   Updated: 2024/05/18 07:33:08 by sprodatu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * @brief Create a new command node.
 * 
 * @param token The token to be added to the command node.
 * @return The new command node.
 */

t_cmd	*new_cmd(t_token *token)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (cmd == NULL)
		return (perror("ERROR! malloc fail"), NULL);
	cmd->token = token;
	cmd->next = NULL;
	return (cmd);
}

/**
 * @brief Add a command to the command list.
 * 
 * @param cmd The command list.
 * @param token The token to be added to the command list.
 */

void	add_cmd(t_cmd *head, t_cmd *new)
{
	if (head == NULL || new == NULL)
		return (0);
	while (head->next != NULL)
		head = head->next;
	head->next = new;
	return ;
}

/**
 * @brief Free the command list.
 * 
 * @param cmd The command list.
 */

int	get_args(t_token **token, t_cmd *cmd)
{
	if (token == NULL || *token == NULL || cmd == NULL)
		return (0);
	cmd->args = malloc(sizeof(char *) * 2);
	if (cmd->args == NULL)
		return (perror("ERROR! Malloc Fail"), 0);
	cmd->args[0] = (*token)->value;
	cmd->args[1] = NULL;
	*token = (*token)->next;
	return (1);
}

// gets commands from the tokens

int	commands(t_ms *ms)
{
	t_token	*token;
	t_cmd	*cmd;

	token = ms->token;
	cmd = NULL;
	while (token->type != END)
	{
		if (token->prev == NULL || token->prev->type == PIPE)
		{
			cmd = new_cmd(token);
			if (cmd == NULL)
				return (perror("ERROR! new_cmd fail"), 0);
			if (ms->cmd == NULL)
				ms->cmd = cmd;
			else
				add_cmd(ms->cmd, cmd);
		}
		if (token->type != PIPE)
			if (!get_args(&token, cmd))
				return (perror("ERROR! get_args"), free(cmd), 0);
		else if (token->type == PIPE)
			token = token->next;
	}
	return (1);
}
