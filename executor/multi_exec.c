/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trosinsk <trosinsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 20:55:36 by trosinsk          #+#    #+#             */
/*   Updated: 2024/05/26 10:08:56 by trosinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	close_fds(int **fds, int n_cmd)
{
	int	i;

	i = 0;
	while (i < n_cmd)
	{
		close(fds[i][0]);
		close(fds[i][1]);
		i++;
	}
}

void	child_process(t_cmd *cmd)
{
	if (STDIN_FILENO != cmd->fd_in)
	{
		dup2(cmd->fd_in, STDIN_FILENO);
		close(cmd->fd_in);
	}
	if (STDOUT_FILENO != cmd->fd_out)
	{
		dup2(cmd->fd_out, STDOUT_FILENO);
		close(cmd->fd_out);
	}
}

int	count_cmd(t_cmd *cmd)
{
	int	i;

	i = 0;
	while (cmd)
	{
		i++;
		cmd = cmd->next;
	}
	return (i);
}

void	pipes_process(int **fds, int i, t_ms *mini, int ncmd)
{
	if (!mini->cmd->args)
		exit(1);
	if (i == 0)
		dup2(fds[i][1], STDOUT_FILENO);
	else if (i == ncmd - 1)
		dup2(fds[i - 1][0], STDIN_FILENO);
	else
	{
		dup2(fds[i - 1][0], STDIN_FILENO);
		dup2(fds[i][1], STDOUT_FILENO);
	}
	close_fds(fds, ncmd);
	child_process(mini->cmd);
	if (is_builtin(mini->cmd))
	{
		exec_builtin(mini->cmd->args, &mini->env_s, mini);
		exit(EXIT_SUCCESS);
	}
	ft_execve(mini->cmd, &mini->env_s, mini);
}

void	performer(t_ms *mini, int **fds, int ncmd)
{
	int		i;

	i = 0;
	while (mini->cmd)
	{
		g_signal = 1;
		mini->pids[i] = fork();
		if (mini->pids[i] == -1)
		{
			ft_putendl_fd("Fork Error", 2);
			exit(EXIT_FAILURE);
		}
		if (mini->pids[i] == 0)
			pipes_process(fds, i, mini, ncmd);
		mini->cmd = mini->cmd->next;
		i++;
	}
}
