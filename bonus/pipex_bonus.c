/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-gady <ael-gady@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 15:11:15 by ael-gady          #+#    #+#             */
/*   Updated: 2025/02/07 03:45:16 by ael-gady         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	ft_error(const char *msg)
{
	perror(msg);
	exit(1);
}

void	ft_error_dup2(const char *msg, int *pipe_fd, int prev_pipe_fd)
{
	close(prev_pipe_fd);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	perror(msg);
	exit(1);
}
int	main(int ac, char **av, char **envp)
{
	int	here_doc;
	int	pipe_fd[2];
	int	pid;

	if (ac < 5 || (ft_strncmp(av[1], "here_doc", 8) == 0 && ac < 6))
	{
		write(2, "Usage: ./pipex here_doc LIMITER cmd1 cmd2 ... cmdn outfile\n", 60);
		write(1, "or \n", 5);
		write(2, "Usage: ./pipex <infile> <cmd_1> ...  <cmd_n> <outfile>\n", 55);
		exit(1);
	}
	here_doc = (!ft_strncmp(av[1], "her_doc", 8));
	if (here_doc)
	{
		pipe(pipe_fd);
		pid = fork();
		if (pid == -1)
			ft_error("failed fork");
		if (pid == 0)
		{
			handle_here_doc(av[2], pipe_fd);//todo
			exit(0);
		}
		close(pipe_fd[1]);
	}
	create_pipes_and_execute(ac, av, envp, here_doc);//todo
	return (0);
}
