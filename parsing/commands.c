/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sprodatu <sprodatu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 01:38:12 by sprodatu          #+#    #+#             */
/*   Updated: 2024/05/23 03:03:36 by sprodatu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	new_cmd(t_cmd **prev, t_token **token, t_cmd **cmd)
{
	t_cmd	*new;

	new = malloc(sizeof(t_cmd));
	if (!new)
		return (perror("ERROR! malloc fail"), 0);
	new->prev = *prev;
	new->args = NULL;
	new->next = NULL;
	new->fd_in = STDIN_FILENO;
	new->fd_out = STDOUT_FILENO;
	if (*prev)
		(*prev)->next = new;
	if (!*cmd)
		*cmd = new;
	*prev = new;
	if ((*token)->prev && (*token)->prev->type != PIPE)
		*token = (*token)->next;
	return (1);
}

int	create_cmds(t_token *token, t_cmd **cmds)
{
	t_cmd	*cmd;

	cmd = NULL;
	while (token->type != END)
	{
		if ((token->prev == NULL || token->prev->type == PIPE)
			&& !new_cmd(&cmd, &token, cmds))
			return (0);
		else if (token->type != PIPE && !get_args(&token, cmd))
			return (0);
		else if (token->type == PIPE)
			token = token->next;
	}
	return (1);
}

/**
 * commands function:
 * 
 * @brief Gets the commands from the tokens
 * 
 * @param ms
 * 
 * @return int
 * 
 * Takes the token address from the ms struct
 * and creates a linked list of commands 
 * 		using create_cmds function
 * 		which takes token & address of the command list as arguments
 * If the create_cmds function returns 0, return 0
 * If the command list is not empty,
 * 		set the command list in the ms struct to the new command list
 * 		which is created by the create_cmds function
 * return 1
 * 
 * @note: 
*/

int	commands(t_ms *ms)
{
	t_token	*token;
	t_cmd	*cmd;

	cmd = NULL;
	token = ms->token;
	if (!create_cmds(token, &cmd))
		return (0);
	if (cmd != NULL)
		ms->cmd = cmd;
	return (1);
}

/**
 * @brief Create a new command node.
 * 
 * @param token The token to be added to the command node.
 * @return The new command node.
 */

// t_cmd	*new_cmd(t_token *token)
// {
// 	t_cmd	*cmd;

// 	cmd = malloc(sizeof(t_cmd));
// 	if (cmd == NULL)
// 		return (perror("ERROR! malloc fail"), NULL);
// 	cmd->token = token;
// 	cmd->next = NULL;
// 	return (cmd);
// }

/**
 * @brief Add a command to the command list.
 * 
 * @param cmd The command list.
 * @param token The token to be added to the command list.
 */

// void	add_cmd(t_cmd *head, t_cmd *new)
// {
// 	if (head == NULL || new == NULL)
// 		return ;
// 	while (head->next != NULL)
// 		head = head->next;
// 	head->next = new;
// 	return ;
// }

/**
 * @brief Free the command list.
 * 
 * @param cmd The command list.
 */

// int	get_args(t_token **token, t_cmd *cmd)
// {
// 	if (token == NULL || *token == NULL || cmd == NULL)
// 		return (0);
// 	cmd->args = malloc(sizeof(char *) * 2);
// 	if (cmd->args == NULL)
// 		return (perror("ERROR! Malloc Fail"), 0);
// 	cmd->args[0] = (*token)->value;
// 	cmd->args[1] = NULL;
// 	*token = (*token)->next;
// 	return (1);
// }

// gets commands from the tokens

// int	commands(t_ms *ms)
// {
// 	t_token	*token;
// 	t_cmd	*cmd;

// 	token = ms->token;
// 	cmd = NULL;
// 	while (token->type != END)
// 	{
// 		if (token->prev == NULL || token->prev->type == PIPE)
// 		{
// 			cmd = new_cmd(token);
// 			if (cmd == NULL)
// 				return (perror("ERROR! new_cmd fail"), 0);
// 			if (ms->cmd == NULL)
// 				ms->cmd = cmd;
// 			else
// 				add_cmd(ms->cmd, cmd);
// 		}
// 		if (token->type != PIPE && !get_args(&token, cmd))
// 			return (perror("ERROR! get_args"), free(cmd), 0);
// 		else if (token->type == PIPE)
// 			token = token->next;
// 	}
// 	return (1);
// }
