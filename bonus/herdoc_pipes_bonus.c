/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc_pipes_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-gady <ael-gady@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 10:33:40 by ael-gady          #+#    #+#             */
/*   Updated: 2025/02/12 16:03:10 by ael-gady         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	init_process(t_process *proc, int ac, char **av, char **envp)
{
	proc->ac = ac;
	proc->av = av;
	proc->envp = envp;
	proc->here_doc = (!ft_strncmp(av[1], "her_doc", 8));
	proc->prev_pipe_fd = -1;
}

void	handle_here_doc_child(char *limiter, int *pipe_fd)
{
	close(pipe_fd[0]);
	handle_here_doc(limiter, pipe_fd);
	exit(0);
}

void	setup_here_doc(t_process *proc, int *pipe_fd, char **av)
{
	int	pid;

	if (pipe(pipe_fd) == -1)
		ft_error("failed pipe");
	pid = fork();
	if (pid == -1)
	{
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		ft_error("failed fork");
	}
	if (pid == 0)
		handle_here_doc_child(av[2], pipe_fd);
	close(pipe_fd[1]);
	proc->prev_pipe_fd = pipe_fd[0];
}

void open_infile(char *infile)
{
	int in_fd;

	in_fd = open(infile, O_RDONLY);
	if (in_fd == -1)
		ft_error("open failed");
	if (dup2(in_fd, 0) == -1)
		ft_error("dup2 input failed");
	close(in_fd);
}

void	handle_here_doc_and_pipes(int ac, char **av, char **envp)
{
	int			pipe_fd[2];
	t_process	proc;

	init_process(&proc, ac, av, envp);
	if (proc.here_doc)
		setup_here_doc(&proc, pipe_fd, av);
	else
		open_infile(av[1]);
	create_pipes_and_execute(&proc);
}
