/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execve.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sprodatu <sprodatu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 19:36:47 by trosinsk          #+#    #+#             */
/*   Updated: 2024/05/28 01:42:13 by sprodatu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**env_to_char(t_env *env_s)
{
	int		i;
	char	**env;
	t_env	*tmp;

	i = 0;
	tmp = env_s;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	env = malloc(sizeof(char *) * (i + 1));
	if (env == NULL)
		return (NULL);
	i = 0;
	tmp = env_s;
	while (tmp)
	{
		env[i] = ft_strjoin(tmp->env_name, "=");
		env[i] = ft_strjoin(env[i], tmp->env_value);
		i++;
		tmp = tmp->next;
	}
	env[i] = NULL;
	return (env);
}

char	*my_getenv(char *name, char **env)
{
	int		i;
	int		j;
	char	*sub;

	i = 0;
	while (env[i])
	{
		j = 0;
		while (env[i][j] && env[i][j] != '=')
			j++;
		sub = ft_substr(env[i], 0, j);
		if (ft_strcmp(sub, name) == 0)
		{
			free(sub);
			return (env[i] + j + 1);
		}
		free(sub);
		i++;
	}
	return (NULL);
}

char	*get_path(char *cmd, char **env)
{
	int		i;
	char	*exec;
	char	**allpath;
	char	*path_part;

	i = -1;
	allpath = ft_split(my_getenv("PATH", env), ':');
	while (allpath[++i])
	{
		path_part = ft_strjoin(allpath[i], "/");
		exec = ft_strjoin(path_part, cmd);
		free(path_part);
		if (access(exec, F_OK | X_OK) == 0)
			return (exec);
		free(exec);
	}
	i = 0;
	while (allpath[i])
		free(allpath[i++]);
	free(allpath);
	return (cmd);
}

void	free_struct(t_env **stack)
{
	t_env	*tmp;
	t_env	*current;

	if (!stack)
		return ;
	current = NULL;
	while (current)
	{
		tmp = current->next;
		free(current);
		current = tmp;
	}
	*stack = NULL;
}

void	ft_execve(t_cmd *cmd, t_env **env_s, t_ms *mini)
{
	if (!cmd->args)
		exit(1);
	if (cmd->args[0] == NULL)
		exit(0);
	mini->env = env_to_char(*env_s);
	if (execve(get_path(cmd->args[0], mini->env),
			cmd->args, mini->env))
	{
		ft_putstr_fd("PROSI-shell: ", 2);
		ft_putstr_fd(cmd->args[0], 2);
		ft_putstr_fd(": ", 2);
		ft_putendl_fd("command not found", 2);
		free_struct(env_s);
		exit(127);
	}
}
// exit(127);
