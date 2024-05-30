/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sprodatu <sprodatu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 05:08:46 by sprodatu          #+#    #+#             */
/*   Updated: 2024/05/30 03:04:37 by sprodatu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "signal_handler.h"

sig_atomic_t g_signal; // Global flag to indicate signal reception

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
		return 1;
	}
	return 0;
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

// //: rl_on_new_line():
// // This function tells Readline that the cursor is on a new line,
// // allowing it to perform any necessary screen management.
// // This is typically used after outputting a newline character.

// // rl_replace_line("", 0):
// // Replaces the current line that Readline is aware of with given string,
// // in this case an empty string.
// // The second argument, if non-zero,
// //	 tells Readline to save the original line in the undo list.

// // rl_redisplay(): 
// // This function forces Readline to update the screen
// // to reflect the current state of the line.
// // This is typically used after making changes to the line,
// // 		such as with rl_replace_line().

// // Signal handler for SIGINT (Ctrl+C)
// void	sigint_handler(int sig)
// {
// 	printf("\n");
// 	rl_on_new_line();
// 	rl_replace_line("", 0);
// 	rl_redisplay();
// 	(void)sig;
// }

// // Function to ignore SIGQUIT (Ctrl+\)

// void	sigquit_handler(void)
// {
// 	struct sigaction	sa_quit;

// 	memset(&sa_quit, 0, sizeof(sa_quit));
// 	sigemptyset(&sa_quit.sa_mask);
// 	sa_quit.sa_handler = SIG_IGN;
// 	sigaction(SIGQUIT, &sa_quit, NULL);
// }

// // Function to handle terminal settings
// // ECHOCTL: If this bit is set, control characters other than TAB, NL, and CR
// // are echoed as ^X, where X is the character with 0x40 bits set.
// // This bit is set by default.

// int	handle_termios(void)
// {
// 	struct termios	term_settings;
// 	int				ret;

// 	ret = tcgetattr(STDIN_FILENO, &term_settings);
// 	if (ret == -1)
// 		return (ft_putstr_fd("tcgetattr failed\n", 2), 1);
// 	term_settings.c_lflag &= ~(ECHOCTL);
// 	ret = tcsetattr(STDIN_FILENO, TCSANOW, &term_settings);
// 	if (ret == -1)
// 		return (perror("tcsetattr"), 1);
// 	return (0);
// }

// // Function to initialize signals and terminal settings

// void	signal_handler(void)
// {
// 	if (handle_termios() != 0)
// 	{
// 		ft_putstr_fd("Error: Failed to set terminal settings\n", 2);
// 		exit(1);
// 	}
// 	sigquit_handler();
// 	signal(SIGINT, sigint_handler);
// }

// // signal_handler function:
// // 1. Call sigquits_handler function to ignore SIGQUIT signal.
// // 2. Call signal function to handle SIGINT signal.
// // 3. Call signal function to handle SIGQUIT signal.