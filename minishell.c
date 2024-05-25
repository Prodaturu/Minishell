/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sprodatu <sprodatu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 04:53:55 by sprodatu          #+#    #+#             */
/*   Updated: 2024/05/21 02:01:03 by sprodatu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signals/signal_handler.h"
#include "includes/minishell.h"

int	g_signal = 0;

void	free_commands(t_ms *ms)
{
	(void) (*ms);
}

void	executor(t_ms *ms)
{
	(void)ms;
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

/**
 * @brief The main function of the minishell program.
 *
 * @param argc The number of command line arguments.
 * @param argv An array of strings representing the command line arguments.
 * @param envp An array of strings representing the environment variables.
 * @return 0 on successful execution.
 * 
 * Entry point of the minishell program.
 * It initializes the `ms` structure with the env variables
 * registers a signal handlers,
 * enable command history
 * binding the tab key for auto-completion
 * loop and process user commands / user input
 * continue to next iteration if input is wrong
 * clear history and exit the program
 * returns 0.
 */

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

// main logic:
// 1. Initialize the minishell structure.
// 2. Check the number of arguments passed to the program.
// 3. Call signal_handler function to handle signals.
// 4. Bind the tab key to rl_complete function.
// 5. Call the using_history function to enable history.
// 6. Start an infinite loop to read the input from user.
// 7. Read the input from the user.
// 8. Add the input to the history.
// 9. Check if the input is wrong.
// 10. If input is wrong, continue to next iteration.
// 11. If input is correct, parse the input.
// 12. If parsing is successful, execute the command.
// 13. Free input.
// 14. Continue to next iteration.
// 15. When done clear the history and return 0.
// 16. End of main function.
