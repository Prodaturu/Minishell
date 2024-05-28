/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trosinsk <trosinsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 20:32:47 by trosinsk          #+#    #+#             */
/*   Updated: 2024/05/29 01:09:46 by trosinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	identifier_error(char *name, char *cmd, t_ms *ms)
{
	ft_putstr_fd("PROSI-shell: ", 2);
	ft_putstr_fd(name, 2);
	ft_putstr_fd(": '", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
	ms->exit_code = 1;
}

int	input_checker(char *name, char *cmd, t_ms *ms, t_env **env_s)
{
	int		i;
	char	**tmp;

	i = 1;
	(void)env_s;
	if (ft_strcmp(cmd, "=") == 0)
		return (identifier_error(name, cmd, ms), 0);
	tmp = ft_split(cmd, '=');
	if (!tmp[0])
		return (free(tmp), 0);
	if (!ft_isalpha(tmp[0][0]) && tmp[0][0] != '_')
		return (identifier_error(name, cmd, ms), free_array(tmp, 0), 0);
	while (tmp[0][i])
	{
		if (!ft_isalnum(tmp[0][i]) && tmp[0][i] != '_')
			return (identifier_error(name, cmd, ms), free_array(tmp, 0), 0);
		i++;
	}
	return (free_array(tmp, 0), 1);
}
