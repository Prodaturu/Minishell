/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sprodatu <sprodatu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 04:53:55 by sprodatu          #+#    #+#             */
/*   Updated: 2024/05/26 07:59:51 by sprodatu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signals/signal_handler.h"
#include "includes/minishell.h"

int	g_signal = 0;

void	free_commands(t_ms *ms)
{
	(void) (*ms);
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

// wrong_input function:
// 1. Check if input is NULL.
// 2. If input is NULL, return 1.
// 3. Check if length of input is 0.
// 4. If length of input is 0, free input, return 1.
// 5. Check if the input is "clear".
// 6. If input is "clear", clear the screen, free input, return 1.
// 7. Check if the input is "exit".
// 8. If input is "exit", free input, exit the program, return 1.
// 9. else Return 0.

// main function (CHECKED AND WORKING)

//! Add executor function after parser

int	process(t_ms *ms)
{
	t_env	*env_s;

	env_s = NULL;
	env_s = save_env(ms->env, env_s);
	ms->env_s = env_s;
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
	return (executor(ms), free_commands(ms), free(ms->input), 1);
}

int	main(int argc, char **argv, char **envp)
{
	t_ms	ms;

	ms.env = envp;
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
