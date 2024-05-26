/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_helper.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sprodatu <sprodatu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 01:52:27 by sprodatu          #+#    #+#             */
/*   Updated: 2024/05/27 01:18:14 by sprodatu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_file(char *path)
{
	struct stat	file_stat;

	if (stat(path, &file_stat) == 0)
	{
		if (S_ISDIR(file_stat.st_mode))
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(path, 2);
			ft_putstr_fd(": is a directory\n", 2);
			exit(126);
		}
	}
	return (1);
}

void	set_fd_helper(char *re, char *path, t_cmd *cmd)
{
	if ((!ft_strcmp(re, ">>") || !ft_strcmp(re, ">")) && \
	cmd->fd_out != STDOUT_FILENO)
		close(cmd->fd_out);
	if (!ft_strcmp(re, ">"))
		cmd->fd_out = open(path, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (!ft_strcmp(re, ">>"))
		cmd->fd_out = open(path, O_CREAT | O_RDWR | O_APPEND, 0644);
	if ((!ft_strcmp(re, "<<") || !ft_strcmp(re, "<")) && \
	cmd->fd_in != STDIN_FILENO)
		close(cmd->fd_in);
	if (!ft_strcmp(re, "<"))
		cmd->fd_in = open(path, O_RDONLY);
}

int	set_fd(char *re, char *path, t_cmd *cmd, t_ms *mini)
{
	set_fd_helper(re, path, cmd);
	if (!ft_strcmp(re, "<<"))
	{
		cmd->fd_in = open("lib/libft/.heredoc", \
		O_CREAT | O_RDWR | O_TRUNC, 0644);
		heredoc(cmd->fd_in, path, mini);
		close(cmd->fd_in);
		cmd->fd_in = open("lib/libft/.heredoc", O_RDONLY);
	}
	if (cmd->fd_in == -1 || cmd->fd_out == -1)
	{
		perror("minishell");
		return (0);
	}
	return (1);
}

void	handle_directory(char *path)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(path, 2);
	ft_putstr_fd(": is a directory\n", 2);
}

int	check_if_file_exits(t_ms *mini, char *path)
{
	struct stat	file_statistic;

	if (stat(path, &file_statistic) == 0)
	{
		if (!S_ISDIR(file_statistic.st_mode))
		{
			if (access(path, R_OK) == -1)
			{
				mini->exit_code = 126;
				ft_putstr_fd("minishell: ", 2);
				ft_putstr_fd(path, 2);
				ft_putstr_fd(": Permission denied \n", 2);
				return (1);
			}
		}
		else
		{
			mini->exit_code = 126;
			handle_directory(path);
			return (1);
		}
	}
	return (0);
}
