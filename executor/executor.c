/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trosinsk <trosinsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 13:58:51 by trosinsk          #+#    #+#             */
/*   Updated: 2024/05/29 22:45:59 by trosinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	pids_init(pid_t **pids, int n_cmd)
{
	*pids = malloc(sizeof(pid_t) * n_cmd);
	if (!(*pids))
		return (0);
	return (1);
}

int	fds_init(int ***fds, int n_cmd)
{
	int	i;

	i = 0;
	*fds = malloc(sizeof(int *) * n_cmd);
	if (!(*fds))
		return (0);
	while (i < n_cmd)
	{
		(*fds)[i] = malloc(sizeof(int) * 2);
		if (!(*fds)[i])
			return (0);
		pipe((*fds)[i]);
		i++;
	}
	return (1);
}

void	exec_free(t_ms *mini, int n_cmd, int **fds)
{
	int	i;

	i = 0;
	free(mini->pids);
	while (i < n_cmd)
	{
		free(fds[i]);
		i++;
	}
	free(fds);
}

void	wait_pids(t_ms *mini, int n_cmd)
{
	int	i;
	int	status;

	i = 0;
	while (i < n_cmd)
	{
		if (waitpid(mini->pids[i], &status, 0) == -1)
		{
			ft_putendl_fd("Waitpid Error", 2);
			exit(EXIT_FAILURE);
		}
		mini->exit_code = WEXITSTATUS(status);
		i++;
	}
	g_signal = 0;
}

void	executor(t_ms *mini)
{
	int		ncmd;
	int		**fds;

	ncmd = count_cmd(mini->cmd);
	if (ft_strcmp(mini->cmd->args[0], "./minishell") == 0)
		ft_change_shellvl(mini, 1);
	if (ncmd == 1)
	{
		simple_exec(mini);
		return ;
	}
	if (!fds_init(&fds, ncmd))
		return ;
	else
	{
		if (!pids_init(&mini->pids, ncmd))
			return (free(fds));
		performer(mini, fds, ncmd);
		close_fds(fds, ncmd);
		wait_pids(mini, ncmd);
	}
	exec_free(mini, ncmd, fds);
}
