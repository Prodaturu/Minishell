/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mininshell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sprodatu <sprodatu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 04:53:55 by sprodatu          #+#    #+#             */
/*   Updated: 2024/05/06 13:33:39 by sprodatu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signals/signal_handler.h"

int	wrong_input(char *input)
{
	if (!input)
		return (1);
	if (ft_strlen(input) == 0)
		return (free(input), 1);
	if (ft_strncmp(input, "clear", 5) == 0)
		return (printf("\033[H\033[J"), free(input), 1);
	if (ft_strncmp(input, "exit", 4) == 0)
		return (free(input), exit(0), 1);
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	char	*input;

	signal_handler();
	while (9)
	{
		input = readline("RosPro-shell$ :");
		if (wrong_input(input))
			continue ;
	}
	return ((void)argv, (void)argc, 0);
}

	// if(check_syntax_error());
	// 	continue;
