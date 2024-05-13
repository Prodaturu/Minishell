/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sprodatu <sprodatu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 05:08:46 by sprodatu          #+#    #+#             */
/*   Updated: 2024/05/12 21:45:46 by sprodatu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "signal_handler.h"

//-> ctrl + c. : Signal interrupt.
//-> ctrl + \. : Signal quit.
//-> ctrl + z. : Signal stop.

//: rl_on_new_line():
// This function tells Readline that the cursor is on a new line,
// allowing it to perform any necessary screen management.
// This is typically used after outputting a newline character.

// rl_replace_line("", 0):
// Replaces the current line that Readline is aware of with given string,
// in this case an empty string.
// The second argument, if non-zero,
//	 tells Readline to save the original line in the undo list.

// rl_redisplay(): 
// This function forces Readline to update the screen
// to reflect the current state of the line.
// This is typically used after making changes to the line,
// 		such as with rl_replace_line().

void	sigint_handler(int signum)
{
	(void)signum;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	sigquit_handler(int signum)
{
	(void) signum;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	sigquits_handler(void)
{
	struct sigaction	act;

	ft_memset(&act, 0, sizeof(struct sigaction));
	sigemptyset(&(act.sa_mask));
	act.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &act, NULL);
}

// ! Add handle_termios(true); to signal_handler function

void	signal_handler(void)
{
	sigquits_handler();
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, sigquit_handler);
}

// signal_handler function:
// 1. Call sigquits_handler function to ignore SIGQUIT signal.
// 2. Call signal function to handle SIGINT signal.
// 3. Call signal function to handle SIGQUIT signal.