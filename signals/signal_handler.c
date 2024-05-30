/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sprodatu <sprodatu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 05:08:46 by sprodatu          #+#    #+#             */
/*   Updated: 2024/05/31 00:07:20 by sprodatu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "signal_handler.h"

// sig_atomic_t g_signal; // Global flag to indicate signal reception

// Signal handler for SIGINT (Ctrl+C)
void	sigint_handler(int sig)
{
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	g_signal = sig;
}

// Signal handler for SIGQUIT (Ctrl+\)

void	sigquit_handler(int sig)
{
	if (g_signal == 0)
	{
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else
	{
		signal(sig, SIG_DFL);
		raise(sig);
	}
}

// Signal handler for EOF (Ctrl+D)
void	sig_eof_handler(int sig)
{
	if (g_signal == 0)
	{
		printf("exit\n");
		exit(0);
	}
	else
	{
		signal(sig, SIG_DFL);
		raise(sig);
	}
}

// Function to handle terminal settings
int	handle_termios(void)
{
	struct termios	term_settings;
	int				ret;

	ret = tcgetattr(STDIN_FILENO, &term_settings);
	if (ret == -1)
	{
		perror("tcgetattr");
		return (1);
	}
	term_settings.c_lflag &= ~(ECHOCTL);
	ret = tcsetattr(STDIN_FILENO, TCSANOW, &term_settings);
	if (ret == -1)
	{
		perror("tcsetattr");
		return (1);
	}
	return (0);
}

// Function to initialize signal handlers and terminal settings
void	signal_handler(void)
{
	if (handle_termios() != 0)
	{
		fprintf(stderr, "Error: Failed to set terminal settings\n");
		exit(1);
	}
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}

// //-> ctrl + c. : Signal interrupt.
// //-> ctrl + \. : Signal quit.
// //-> ctrl + z. : Signal stop.
