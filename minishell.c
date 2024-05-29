/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trosinsk <trosinsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 04:53:55 by sprodatu          #+#    #+#             */
/*   Updated: 2024/05/30 00:37:46 by trosinsk         ###   ########.fr       */
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
	executor(ms);
	return (free_commands(ms->cmd), free(ms->input), 1);
}

static void	clear_ms(t_ms *ms)
{
	if (ms->input)
		free(ms->input);
	if (ms->cmd)
		free_commands(ms->cmd);
	if (ms->pids)
		free(ms->pids);
	if (ms->env_s)
		free_env(ms->env_s);
	if (ms->token)
		free_tokens(ms->token);
	if (ms->exit_code)
		free(ms->exit_code);
	if (ms->env)
		free_array(ms->env, 0);
	if (ms)
		free(ms);
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
	clear_ms(&ms);
	return (clear_history(), (void)argv, (void)argc, 0);
}
