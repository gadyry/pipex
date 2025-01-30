/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-gady <ael-gady@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 18:45:53 by ael-gady          #+#    #+#             */
/*   Updated: 2025/01/30 04:26:04 by ael-gady         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_error(const char *msg)
{
	perror(msg);
	exit(1);
}

void	execute(char *cmd_, char **envp, t_pipex *p)
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
	execute(av[2], envp, p);
}

void	al_maari(char **av, char **envp, t_pipex *p)
{
	int	output_fd;

	output_fd = open_file(av[4], 0);
	if (dup2(p->pipe_fd[0], STDOUT_FILENO) == -1)
	{
		close(output_fd);
		close(p->pipe_fd[0]);
		close(p->pipe_fd[1]);
		ft_error("Error: Failed to redirect stdout");
	}
	if (dup2(output_fd, STDIN_FILENO) == -1)
	{
		close(output_fd);
		close(p->pipe_fd[0]);
		close(p->pipe_fd[1]);
		ft_error("Error: Failed to redirect stdin");
	}
	close(output_fd);
	close(p->pipe_fd[0]);
	close(p->pipe_fd[1]);
	execute(av[3], envp, p);
}

void	check_arg(int ac)
{
	if (ac != 5)
	{
		write(2, "Usage: ./pipex <infile> <cmd1> <cmd2> <outfile>\n", 48);
		exit(1);
	}
}

int	main(int ac, char **av, char **envp)
{
	pid_t	pid;
	t_pipex	pipex;
	int		status;

	check_arg(ac);
	if (pipe(pipex.pipe_fd) == -1)
		ft_error("pipe failed");
	pid = fork();
	if (pid == -1)
	{
		close(pipex.pipe_fd[0]);
		close(pipex.pipe_fd[1]);
		ft_error("fork failed");
	}
	if (!pid)
		the_dutiful_child(av, envp, &pipex);
	else
	{
		al_maari(av, envp, &pipex);
		wait(&status);
	}
	return (0);
}
