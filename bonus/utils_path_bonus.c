/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_path_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-gady <ael-gady@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 14:51:37 by ael-gady          #+#    #+#             */
/*   Updated: 2025/02/17 18:39:58 by ael-gady         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	free_matrice(char **free_me)
{
	int	i;

	if (!free_me)
		return ;
	i = 0;
	while (free_me[i])
	{
		free(free_me[i]);
		i++;
	}
	free(free_me);
}

char	*get_env(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], "PATH=", 5))
			return (ft_strdup(envp[i] + 5));
		i++;
	}
	return (NULL);
}

char	*get_full_path(char **paths, char *cmd)
{
	int		i;
	char	*temp;
	char	*full_path;

	if (!paths || !cmd)
		return (NULL);
	i = -1;
	while (paths[++i])
	{
		temp = ft_strjoin(paths[i], "/");
		if (!temp)
			return (NULL);
		full_path = ft_strjoin(temp, cmd);
		free(temp);
		if (!full_path)
			return (NULL);
		if (access(full_path, X_OK) == 0)
			return (full_path);
		free(full_path);
	}
	return (NULL);
}

char	*get_cmd_path(char **cmd_args, char **envp)
{
	char	*path_env;
	char	**paths;
	char	*full_path;

	if (!cmd_args || !cmd_args[0])
		return (NULL);
	if (!ft_strncmp(cmd_args[0], "./", 2) || !ft_strncmp(cmd_args[0], "/", 1))
	{
		if (access(cmd_args[0], X_OK) == 0)
			return (cmd_args[0]);
		return (NULL);
	}
	path_env = get_env(envp);
	if (!path_env)
		return (NULL);
	paths = ft_split(path_env, ':');
	free(path_env);
	if (!paths)
		return (NULL);
	full_path = get_full_path(paths, cmd_args[0]);
	return (free_matrice(paths), full_path);
}

void	execute_cmd(char *cmd_, char **envp, int key)
{
	char	*pathname;
	char	**cmd_args;

	cmd_args = ft_split(cmd_, ' ');
	if (!cmd_args)
		ft_error("ft_split failed");
	pathname = get_cmd_path(cmd_args, envp);
	if (!pathname)
	{
		free_matrice(cmd_args);
		ft_error("Command not found");
	}
	if (execve(pathname, cmd_args, envp) == -1)
	{
		perror("execve");
		if (pathname != cmd_args[0])
			free(pathname);
		free_matrice(cmd_args);
		if (key == 1)
			unlink("/tmp/.hg");
		exit(1);
	}
}
