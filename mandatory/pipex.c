/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-gady <ael-gady@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 18:45:53 by ael-gady          #+#    #+#             */
/*   Updated: 2025/02/17 17:00:06 by ael-gady         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	execute(char *cmd_, char **envp)
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
		free(pathname);
		free_matrice(cmd_args);
		exit(1);
	}
}

void	the_dutiful_child(char **av, char **envp, t_pipex *p)
{
	int	input_fd;

	input_fd = open_file(av[1], 1);
	if (dup2(input_fd, STDIN_FILENO) == -1)
	{
		close(input_fd);
		close(p->pipe_fd[0]);
		close(p->pipe_fd[1]);
		ft_error("Error: Failed to redirect stdin");
	}
	if (dup2(p->pipe_fd[1], STDOUT_FILENO) == -1)
	{
		close(input_fd);
		close(p->pipe_fd[0]);
		close(p->pipe_fd[1]);
		ft_error("Error: Failed to redirect stdout");
	}
	close(input_fd);
	close(p->pipe_fd[0]);
	close(p->pipe_fd[1]);
	execute(av[2], envp);
}

void	second_child(char **av, char **envp, t_pipex *p)
{
	int	output_fd;

	output_fd = open_file(av[4], 0);
	if (dup2(output_fd, STDOUT_FILENO) == -1)
	{
		close(output_fd);
		close(p->pipe_fd[0]);
		close(p->pipe_fd[1]);
		ft_error("Error: Failed to redirect stdin");
	}
	if (dup2(p->pipe_fd[0], STDIN_FILENO) == -1)
	{
		close(output_fd);
		close(p->pipe_fd[0]);
		close(p->pipe_fd[1]);
		ft_error("Error: Failed to redirect stdout");
	}
	close(output_fd);
	close(p->pipe_fd[0]);
	close(p->pipe_fd[1]);
	execute(av[3], envp);
}

int	main(int ac, char **av, char **envp)
{
	pid_t	pid1;
	pid_t	pid2;
	t_pipex	p;

	if (ac != 5)
		ft_error("Usage: ./pipex <infile> <cmd1> <cmd2> <outfile>");
	if (pipe(p.pipe_fd) == -1)
		ft_error("pipe failed");
	pid1 = fork();
	if (pid1 == -1)
		(close(p.pipe_fd[0]), close(p.pipe_fd[1]), ft_error("fork failed"));
	if (!pid1)
		the_dutiful_child(av, envp, &p);
	pid2 = fork();
	if (pid2 == -1)
		(close(p.pipe_fd[0]), close(p.pipe_fd[1]), ft_error("fork failed"));
	if (!pid2)
		second_child(av, envp, &p);
	close(p.pipe_fd[0]);
	close(p.pipe_fd[1]);
	return (wait(NULL), wait(NULL), 0);
}
