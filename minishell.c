/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sprodatu <sprodatu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 04:53:55 by sprodatu          #+#    #+#             */
/*   Updated: 2024/05/30 22:20:44 by sprodatu         ###   ########.fr       */
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

int	has_something(char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (input[i] != ' ' && input[i] != '\t')
			return (1);
		i++;
	}
	return (0);
}

int	wrong_input(char *input)
{
	if (!input)
		return (printf("ERROR! No input"), 0);
	if (ft_strlen(input) == 0 || input[0] == '\0' || !has_something(input))
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
		return (printf("exit\n"), 0);
	if (wrong_input(ms->input))
		return (1);
	if (!parse(ms))
		return (free(ms->input), 1);
	executor(ms);
	return (free_commands(ms->cmd), free(ms->input), 1);
}

// static void	clear_ms(t_ms *ms)
// {
// 	if (ms->input)
// 		free(ms->input);
// 	if (ms->cmd)
// 		free_commands(ms->cmd);
// 	if (ms->pids)
// 		free(ms->pids);
// 	if (ms->env_s)
// 		free_struct(&ms->env_s);
// 	if (ms->token)
// 		free_tokens(ms->token);
// 	if (ms->env)
// 		free_array(ms->env, 0);
// 	if (ms)
// 		free(ms);
// }

int	main(int argc, char **argv, char **envp)
{
	t_ms	ms;
	t_env	*env_s;

	signal_handler();
	env_s = NULL;
	ms.env = envp;
	env_s = save_env(ms.env, env_s);
	ms.env_s = env_s;
	if (argc != 1)
		return (printf("ERROR! Use: ./mini_shell\n"), 1);
	using_history();
	rl_bind_key('\t', rl_complete);
	while (9)
		if (!process(&ms))
			break ;
	// clear_ms(&ms);
	return (clear_history(), (void)argv, (void)argc, 0);
}
