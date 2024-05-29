/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trosinsk <trosinsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 01:18:36 by sprodatu          #+#    #+#             */
/*   Updated: 2024/05/30 00:05:18 by trosinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_commands(t_cmd *cmd)
{
	t_cmd	*current;
	int		i;

	i = 0;
	if (cmd == NULL)
	{
		printf("No commands to print.\n");
		return ;
	}
	current = cmd;
	while (current != NULL)
	{
		printf("Command Arguments: ");
		if (current->args != NULL)
		{
			while (current->args[i] != NULL)
			{
				printf("argument ->|--:%s:--|\n", current->args[i]);
				i++;
			}
		}
		printf("\ncommands done\n");
		current = current->next;
	}
}

void	free_tokens(t_token *token)
{
	t_token	*temp;
	t_token	*temp2;

	temp = token;
	while (temp != NULL)
	{
		temp2 = temp->next;
		if (temp->value != NULL)
			free(temp->value);
		free(temp);
		temp = temp2;
	}
}

void	print_tokens(t_token *token)
{
	t_token	*temp;

	temp = token;
	while (temp)
	{
		printf("\n--------\nToken Type: %d\n", temp->type);
		printf("Token Value: %s\n", temp->value);
		temp = temp->next;
	}
}

int	parse(t_ms *ms)
{
	if (!lexing(ms))
		return (free_tokens(ms->token), 0);
	if (syntax_error(ms))
		return (free_tokens(ms->token), 0);
	if (!commands(ms))
		return (free_tokens(ms->token), 0);
	expand(ms);
	handle_redirection(ms);
	free_tokens(ms->token);
	return (1);
}
