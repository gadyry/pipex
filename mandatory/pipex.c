/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-gady <ael-gady@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 18:45:53 by ael-gady          #+#    #+#             */
/*   Updated: 2025/01/29 23:46:25 by ael-gady         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	execute(char *cmd_, char **envp, t_pipex *p)//todo had zeeb !!
{
	char	*pathname;
	char	**cmd_args;

	cmd_args = ft_split(cmd_, ' ');
	pathmane = get_cmd_path(cmd_args, envp);//todo
}

void	The_dutiful_child(char **av, char **envp, t_pipex *p)
{
	int	input_fd;

	input_fd = open_file(av[1], 0);//todo
	dup2(input_fd, 0);
	dup2(p->pipe_fd[1], 1);
	close(input_fd);
	close(p->pipe_fd[0]);
	close(p->pipe_fd[1]);
	//execute cm1 : get_cmd_path execev(cmd_path, cmd_argv, envp)
	execute(av[3], envp, p);//todo
}

void	al_maari(char **av, char **envp, t_pipex *p)
{
	int	output_fd;

	output_fd = open_file(av[4], 1);//todo
	dup2(output_fd, 0);
	dup2(p->pipe_fd[0], 1);
	close(output_fd);
	close(p->pipe_fd[0]);
	close(p->pipe_fd[1]);
	//execute cm2 : get_cmd_path execev(cmd_path, cmd_argv, envp)
	execute(av[4], envp, p);//todo
}

int main(int ac, char **av, char **envp)
{
	pid_t	pid;
	t_pipex	pipex;

	if (ac != 5)
	{
		write(2, "Usage: ./pipex <infile> <cmd1> <cmd2> <outfile>\n", 48);
		exit(1);
	}
	if (pipe(pipex.pipe_fd) == -1)
	{
		write(2, "Failed pipe !\n", 14);
		exit(1);
	}
	pid = fork();
	if (pid == -1)
	{
		write(2, "Failed fork !\n", 14);
		exit(1);
	}
	if (!pid)
		The_dutiful_child(av, envp, &pipex);
	al_maari(av, envp, &pipex);
	//wait(&pid);
}
