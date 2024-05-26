/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trosinsk <trosinsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 04:53:55 by sprodatu          #+#    #+#             */
/*   Updated: 2024/05/27 01:38:36 by trosinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signals/signal_handler.h"
#include "includes/minishell.h"

int	g_signal = 0;

void	free_commands(t_cmd *cmd)
{
	t_cmd	*tmp;
	int		i;

	tmp = NULL;
	while (cmd)
	{
		tmp = cmd->next;
		i = 0;
		while (cmd->args && cmd->args[i])
			free(cmd->args[i++]);
		free(cmd->args);
		free(cmd);
		cmd = tmp;
	}
}

int	wrong_input(char *input)
{
	if (!input)
		return (printf("ERROR! No input"), 0);
	if (ft_strlen(input) == 0 || input[0] == '\0')
		return (free(input), 1);
	if (ft_strncmp(input, "clear", 5) == 0)
		return (printf("\033[H\033[J"), free(input), 1);
	if (ft_strncmp(input, "exit", 4) == 0)
		return (free(input), exit(0), 1);
	return (0);
}

int	process(t_ms *ms)
{
	g_signal = 0;
	ms->input = readline("PROSI-shell$ :");
	if (ms->input)
		add_history(ms->input);
	else
		return (0);
	if (wrong_input(ms->input))
		return (0);
	if (!parse(ms))
		return (free(ms->input), 0);
	return (executor(ms), free_commands(ms->cmd), free(ms->input), 1);
}

int	main(int argc, char **argv, char **envp)
{
	t_ms	ms;
	t_env	*env_s;

	env_s = NULL;
	ms.env = envp;
	env_s = save_env(ms.env, env_s);
	ms.env_s = env_s;
	if (argc != 1)
		return (printf("ERROR! Use: ./mini_shell\n"), 1);
	signal_handler();
	using_history();
	rl_bind_key('\t', rl_complete);
	while (9)
		if (!process(&ms))
			continue ;
	return (clear_history(), (void)argv, (void)argc, 0);
}
