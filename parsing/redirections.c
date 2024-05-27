/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trosinsk <trosinsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 01:50:16 by sprodatu          #+#    #+#             */
/*   Updated: 2024/05/27 22:47:55 by trosinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	handle_redirection_out(t_ms *mini, t_cmd *cmd, int *i)
{
	if (!cmd->args[*i + 1])
		return (1);
	if (!set_fd(cmd->args[*i], cmd->args[(*i) + 1], cmd, mini))
	{
		mini->exit_code = 1;
		return (0);
	}
	remove_element(&cmd->args, *i);
	remove_element(&cmd->args, *i);
	(*i)--;
	return (1);
}

int	handle_redirection_in(t_ms *mini, t_cmd *cmd, int *i)
{
	if (!cmd->args[*i + 1])
		return (1);
	if ((!ft_strcmp(cmd->args[*i], "<") || (!ft_strcmp(cmd->args[*i], "<<")))
		&& !check_file(cmd->args[(*i) + 1]))
	{
		mini->exit_code = 1;
		return (0);
	}
	if (!set_fd(cmd->args[*i], cmd->args[(*i) + 1], cmd, mini))
	{
		mini->exit_code = 1;
		return (0);
	}
	remove_element(&cmd->args, *i);
	remove_element(&cmd->args, *i);
	(*i)--;
	return (1);
}

void	remove_args(t_cmd *cmd)
{
	int	i;

	i = 0;
	while (cmd->args[i])
	{
		free(cmd->args[i]);
		i++;
	}
	free(cmd->args);
	cmd->args = NULL;
}

int	handle_redirection_helper(t_ms *mini, t_cmd *cmd, int *i)
{
	if (cmd->args[*i][0] == '<')
	{
		if (!handle_redirection_in(mini, cmd, i))
			return (remove_args(cmd), 0);
	}
	else if (cmd->args[*i][0] == '>')
	{
		if (!handle_redirection_out(mini, cmd, i))
			return (remove_args(cmd), 0);
	}
	return (1);
}

void	handle_redirection(t_ms *mini)
{
	t_cmd	*temp;
	int		i;

	temp = mini->cmd;
	while (mini->cmd)
	{
		i = 0;
		while (mini->cmd->args[i])
		{
			if (!handle_redirection_helper(mini, mini->cmd, &i))
			{
				if (!mini->cmd->next)
					return ;
				break ;
			}
			i++;
		}
		mini->cmd = mini->cmd->next;
	}
	mini->cmd = temp;
}
