/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-gady <ael-gady@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 23:40:28 by ael-gady          #+#    #+#             */
/*   Updated: 2025/02/17 16:27:28 by ael-gady         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_matrice(char **str)
{
	int	i;

	if (!str)
		return ;
	i = 0;
	while (str[i])
		free(str[i++]);
	free(str);
}

int	open_file(char *av, int key)
{
	int	fd;

	if (key)
	{
		fd = open(av, O_RDONLY, 0777);
		if (fd == -1)
		{
			perror("Error opening infile");
			exit(1);
		}
	}
	else
	{
		fd = open(av, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd == -1)
		{
			perror("Error opening outfile");
			exit(1);
		}
	}
	return (fd);
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
