/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sprodatu <sprodatu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 01:18:36 by sprodatu          #+#    #+#             */
/*   Updated: 2024/05/25 18:10:30 by sprodatu         ###   ########.fr       */
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
		printf("\n----------------\n");
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

/**
 * Parses the input command line and performs necessary operations.
 * 
 * @param mini A pointer to the t_mini structure representing the mini shell.
 * @return Returns 1 if the parsing is successful, 0 otherwise.
 */

int	parse(t_ms *ms)
{
	if (!lexing(ms))
		return (free_tokens(ms->token), 0);
	if (syntax_error(ms))
		return (free_tokens(ms->token), 0);
	if (!commands(ms))
		return (free_tokens(ms->token), 0);
	expand(ms);
	print_commands(ms->cmd);
	return (1);
}

	// expand(ms);
	// if (!redirections(ms))
	// 	return (free_tokens(ms->token), 0);
	// free_tokens(ms->token);

// parse function:
// 1. Call lexing function.
// 2. If lexing function returns 0, free tokens and return 0.
// 3. Call syntax_error function.
// 4. If syntax_error function returns 1, free tokens and return 0.
// 5. Call commands function.
// 6. If commands function returns 0, free tokens and return 0.
// 7. Call expander function.
// 8. If expander function returns 0, free tokens and return 0.
// 9. Call redirections function.
// 10. If redirections function returns 0, free tokens and return 0.
// 11. free tokens and return 1.
