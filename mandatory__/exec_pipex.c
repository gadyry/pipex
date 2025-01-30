/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-gady <ael-gady@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 10:23:56 by ael-gady          #+#    #+#             */
/*   Updated: 2025/01/29 23:56:34 by ael-gady         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_t_pipex(t_pipex *p)
{
	int	i;

	free(p->infile);
	free(p->outfile);
	i = 0;
	while (p->cmd1[i])
		free(p->cmd1[i]);
	free(p->cmd1);
	i = 0;
	while (p->cmd2[i])
		free(p->cmd2[i]);
	free(p->cmd2);	
}

char	*get_path(char **envp)
{
	char	**paths;
	char	*path_value;
	int		i;

	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], "PATH=", 5))
		{
			path_value = envp[i] + 5;
			paths = ft_split(path_value, ':');
			return (paths);
		}
		i++;
	}
	return (NULL);
}

char	*find_cmd_path(char **cmd, char **envp)
{
	char	*cmd_path;
	int		i;

	i = 0;
	cmd_path = get_path(envp);
	while (cmd_path[i])
	{
		if (!access(cmd, X_OK))
			return (cmd_path[i]);
		i++;
	}
	return (NULL);
}

void	execute_pipex(t_pipex *pipex, char **av, char **envp)
{
	t_fd	*fd;
	pid_t	pid1;
	pid_t	pid2;
	char	*path;

	fd->input_fd = open(pipex->infile, O_RDONLY, 0644);
	if (fd->input_fd == -1)
	{
		perror("Problem in opening the file !!\n");
		free_t_pipex(pipex);
		exit(1);		
	}
	fd->output_fd = open(pipex->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd->output_fd == -1)
	{
		fclose(fd->input_fd);
		perror("Problem in opening the file !!\n");
		free_t_pipex(pipex);
		exit(1);
	}
	// create a pipe
	if (pipe(fd->pipe_fd) == -1)
	{
		perror("Pipe failed !!\n");
		free_t_pipex(pipex);
		exit(1);
	}
	// Fork the first child for cmd1
	pid1 = fork();
	if (pid1 == 0)
	{
		close(fd->pipe_fd[0]);
		dup2(fd->input_fd, 0);// Redirect stdin to infile
		dup2(fd->pipe_fd[1], 1);// Redirect stdout to pipe read-end
		close(fd->input_fd);
		close(fd->output_fd);
		close(fd->pipe_fd[1]);
		//execute cm1 : get_cmd_path execev(cmd_path, cmd_argv, envp)
		path = find_cmd_path(pipex->cmd1, envp);//todo
		if (!path)
		{
		perror("Commande not found !!\n");
		free_t_pipex(pipex);
		exit(1);
		}
		if (execve(path, pipex->cmd1, envp) == -1)
		{
			perror("Error executing cmd1 !!\n");
			free_t_pipex(pipex);
			exit(1);
		}
	}
	/* Fork the second child for cmd1 */
	pid2 = fork();
	if (!pid2)
	{
		dup2(fd->pipe_fd[0], 0);
		dup2(fd->output_fd, 1);
		close(fd->pipe_fd[1]);
        close(fd->pipe_fd[0]);
        close(fd->input_fd);
        close(fd->output_fd);
		//execute cm2 : get_cmd_path execev(cmd_path, cmd_argv, envp)
		path = find_cmd_path(pipex->cmd2, envp);//todo
		if (!path)
		{
		perror("Commande not found !!\n");
		free_t_pipex(pipex);
		exit(1);
		}
		if (execve(path, pipex->cmd1, envp) == -1)
		{
			perror("Error executing cmd1 !!\n");
			free_t_pipex(pipex);
			exit(1);
		}
	}
	close(fd->pipe_fd[0]);
	close(fd->pipe_fd[1]);
	close(fd->input_fd);
	close(fd->output_fd);
	
}

