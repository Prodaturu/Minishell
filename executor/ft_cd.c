/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trosinsk <trosinsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 17:33:36 by trosinsk          #+#    #+#             */
/*   Updated: 2024/05/30 20:56:04 by trosinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_getenv(char *name, t_env *env_s)
{
	t_env	*tmp;

	tmp = env_s;
	while (tmp)
	{
		if (ft_strncmp(tmp->env_name, name, ft_strlen(name)) == 0)
		{
			name = tmp->env_value;
			break ;
		}
		tmp = tmp->next;
	}
	return (name);
}

static char	*newpath_join(char *newpath, char *pwd, char *path)
{
	char	*temp;

	temp = ft_strjoin(pwd, "/");
	newpath = ft_strjoin(temp, path);
	free(temp);
	return (newpath);
}

char	*set_newpath(char *path, char *home, char *pwd, char *oldpwd)
{
	char	*newpath;

	newpath = NULL;
	if (path == NULL || ft_strncmp(path, "~", 1) == 0)
		newpath = ft_strdup(home);
	else if (ft_strncmp(path, "-", 1) == 0)
		newpath = ft_strdup(oldpwd);
	else if (ft_strncmp(path, "..", 2) == 0)
	{
		path = ft_strrchr(pwd, '/');
		if (path == pwd)
			newpath = ft_strdup("/");
		else
			newpath = ft_substr(pwd, 0, path - pwd);
	}
	else if (ft_strcmp(path, pwd) == 0 || ft_strncmp(path, ".", 1) == 0)
		newpath = ft_strdup(pwd);
	else if (path[0] == '/')
		newpath = ft_strdup(path);
	else
		newpath = newpath_join(newpath, pwd, path);
	return (newpath);
}

void	ft_cd(char *path, char *oldpwd, t_env **env_s, t_ms *ms)
{
	char	*pwd;
	char	*home;
	char	*newpath;

	home = ft_getenv("HOME", *env_s);
	pwd = ft_getenv("PWD", *env_s);
	newpath = NULL;
	newpath = set_newpath(path, home, pwd, oldpwd);
	if (access(newpath, F_OK) == 0)
	{
		chdir(newpath);
		ft_setenv("PWD", newpath, 1, *env_s);
	}
	else
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd(": ", 2);
		ft_putendl_fd(strerror(errno), 2);
		ms->exit_code = 1;
		return ;
	}
	free(newpath);
	ms->exit_code = 0;
}

void	ft_cd_prep(char **cmd, t_env **env_s, t_ms *ms)
{
	char	**new_cmd;
	char	*opwd;
	char	*pwd;
	char	*temp;
	int		i;

	opwd = ft_getenv("OLDPWD", *env_s);
	pwd = ft_strdup(ft_getenv("PWD", *env_s));
	if (cmd[1] == NULL)
		return (ft_cd(ft_getenv("HOME", *env_s), opwd, env_s, ms), (void) NULL);
	if (cmd[1][0] == '/')
		ft_cd(cmd[1], opwd, env_s, ms);
	new_cmd = ft_split(cmd[1], '/');
	i = -1;
	while (new_cmd[++i])
	{
		temp = ft_strjoin(new_cmd[i], "/");
		free(new_cmd[i]);
		new_cmd[i] = ft_strdup(temp);
		free(temp);
		ft_cd(new_cmd[i], opwd, env_s, ms);
	}
	ft_setenv("OLDPWD", pwd, 1, *env_s);
	free(pwd);
	free_array(new_cmd, 0);
}
