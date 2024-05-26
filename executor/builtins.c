/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trosinsk <trosinsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 19:46:47 by trosinsk          #+#    #+#             */
/*   Updated: 2024/05/26 22:48:20 by trosinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_builtin(t_cmd *cmd)
{
	char	*builtins[7];
	int		i;

	i = 0;
	if (cmd->args[0] == NULL)
		return (0);
	builtins[0] = "echo";
	builtins[1] = "env";
	builtins[2] = "pwd";
	builtins[3] = "cd";
	builtins[4] = "export";
	builtins[5] = "unset";
	builtins[6] = "exit";
	while (i < 7)
	{
		if (ft_strnstr(cmd->args[0], builtins[i], ft_strlen(builtins[i])) != 0)
			return (1);
		i++;
	}
	return (0);
}

void	init_builtins(t_builtin *bt)
{
	t_ft	*inbuilt;

	inbuilt = bt->inbuilt;
	inbuilt[0].name = "echo";
	inbuilt[0].ft = &ft_echo_prep;
	inbuilt[1].name = "env";
	inbuilt[1].ft = &ft_env_prep;
	inbuilt[2].name = "pwd";
	inbuilt[2].ft = &ft_pwd_prep;
	inbuilt[3].name = "cd";
	inbuilt[3].ft = &ft_cd_prep;
	inbuilt[4].name = "export";
	inbuilt[4].ft = &ft_export_prep;
	inbuilt[5].name = "unset";
	inbuilt[5].ft = &ft_unset_prep;
	inbuilt[6].name = "exit";
	inbuilt[6].ft = &ft_exit_prep;
}

	// inbuilt[7].name = NULL;
	// inbuilt[7].ft = NULL;
t_builtin	*get_bt(void)
{
	t_builtin	*bt;

	bt = malloc(sizeof(t_builtin));
	if (bt == NULL)
	{
		return (NULL);
	}
	init_builtins(bt);
	return (bt);
}

void	exec_builtin(char **argv, t_env **env, t_ms *mini)
{
	t_builtin	*bt;
	char		*temp;
	int			i;

	i = 0;
	temp = ft_strdup(argv[0]);
	bt = get_bt();
	i = 0;
	while (i < 7)
	{
		if (ft_strcmp(temp, bt->inbuilt[i].name) == 0)
		{
			bt->inbuilt[i].ft(argv, env, mini);
			free(temp);
			return ;
		}
		i++;
	}
	free(temp);
}
