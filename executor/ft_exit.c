/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trosinsk <trosinsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 22:28:42 by trosinsk          #+#    #+#             */
/*   Updated: 2024/05/26 10:10:06 by trosinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_exit(char **cmd, t_ms *ms, int msg_flag, t_env **env_s)
{
	(void)env_s;
	ft_putendl_fd("exit", STDOUT_FILENO);
	if (msg_flag == 0)
		exit(ft_atoi(cmd[1]));
	else if (msg_flag == 1)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(cmd[1], STDERR_FILENO);
		ft_putendl_fd(": numeric argument required", STDERR_FILENO);
		exit(255);
	}
	else if (msg_flag == 2)
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", STDERR_FILENO);
		ms->exit_code = 1;
	}
}

	//1 - numeric argument required
	//2 - too many arguments
int	msg_calc(char **cmd, int i, int j)
{
	int	msg_flag;
	int	digit_flag;

	msg_flag = 0;
	digit_flag = 0;
	if (i > 1 && msg_flag == 0)
		msg_flag = 2;
	else if (ft_isdigit(cmd[i][j]))
		digit_flag = 1;
	else if (!ft_isdigit(cmd[i][j]) && cmd[i][j] != '-'
		&& cmd[i][j] != '+' && msg_flag != 2)
		msg_flag = 1;
	else if (ft_atoi(cmd[i]) == 0 && digit_flag == 0 && msg_flag != 2)
		msg_flag = 1;
	return (msg_flag);
}

void	ft_exit_prep(char **cmd, t_env **env_s, t_ms *ms)
{
	int	i;
	int	j;
	int	msg_flag;

	i = 1;
	j = 0;
	msg_flag = 0;
	while (cmd[i] && msg_flag != 2)
	{
		if (!cmd[1])
			break ;
		j = 0;
		while (cmd[i][j])
		{
			msg_flag = msg_calc(cmd, i, j);
			j++;
		}
		i++;
	}
	ft_exit(cmd, ms, msg_flag, env_s);
}
