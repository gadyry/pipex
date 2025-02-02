/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-gady <ael-gady@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 18:45:53 by ael-gady          #+#    #+#             */
/*   Updated: 2025/02/01 17:12:09 by ael-gady         ###   ########.fr       */
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

void	handle_stdin_input(t_pipex *p, char **av, char **envp)
{
	if (dup2(p->pipe_fd[1], STDOUT_FILENO) == -1)
	{
		close(p->pipe_fd[0]);
		close(p->pipe_fd[1]);
		ft_error("Error: Failed to redirect stdout");
	}
	close(p->pipe_fd[0]);
	close(p->pipe_fd[1]);
	execute(av[3], envp, p);
}

void	handle_file_input(t_pipex *p, char **av, char **envp)
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

void	the_dutiful_child(char **av, char **envp, t_pipex *p)
{
	// if (ft_strncmp(av[1], "/dev/stdin", 10) == 0)
	// 	handle_stdin_input(p, av, envp);
	// else
	handle_file_input(p, av, envp);
}

void	al_maari(char **av, char **envp, t_pipex *p)
{
	int	output_fd;

	output_fd = open_file(av[4], 0);
	if ( dup2(p->pipe_fd[0], STDIN_FILENO) == -1)
	{
		close(output_fd);
		close(p->pipe_fd[0]);
		close(p->pipe_fd[1]);
		ft_error("Error: Failed to redirect stdout");
	}
	if (dup2(output_fd, STDOUT_FILENO) == -1)
	{
		close(output_fd);
		close(p->pipe_fd[0]);
		close(p->pipe_fd[1]);
		ft_error("Error: Failed to redirect stdin");
	}
	close(output_fd);
	close(p->pipe_fd[0]);
	close(p->pipe_fd[1]);
	sleep(1000);
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

void	f()
{
	system("leaks  pipex");
}
#include "libc.h"

int	main(int ac, char **av, char **envp)
{
	pid_t	pid;
	t_pipex	pipex;
	int		status;

	atexit(f);
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
