/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-gady <ael-gady@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 10:37:14 by ael-gady          #+#    #+#             */
/*   Updated: 2025/02/17 22:36:12 by ael-gady         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	handle_here_doc(char *limiter, int *pipe_fd, t_process *proc)
{
	char	*line;

	proc->here_fd = open("/tmp/.hg", O_RDWR | O_TRUNC | O_CREAT, 0644);
	if (proc->here_fd == -1)
		ft_error("open failed !");
	proc->fd_tmp = open("/tmp/.hg", O_RDWR | O_TRUNC | O_CREAT, 0644);
	if (proc->fd_tmp == -1)
		(close(proc->here_fd), ft_error("open failed !"));
	unlink("/tmp/.hg");
	while (1)
	{
		write(1, "heredoc>", 9);
		line = get_next_line(0);
		if (!line)
			break ;
		if (!ft_strncmp(line, limiter, ft_strlen(limiter)) \
			&& line[ft_strlen(limiter)] == '\n')
		{
			free(line);
			break ;
		}
		write(proc->here_fd, line, ft_strlen(line));
		free(line);
	}
	(close(proc->here_fd), close(pipe_fd[1]));
}

void	first_mission(t_process *proc, int *pipe_fd, int i)
{
	int	in_fd;

	close(pipe_fd[0]);
	if (proc->here_doc)
		in_fd = proc->fd_tmp;
	else
		in_fd = open(proc->av[1], O_RDONLY);
	if (in_fd == -1)
		(close(pipe_fd[1]), ft_error("open failed !"));
	if (dup2(in_fd, 0) == -1 || dup2(pipe_fd[1], 1) == -1)
	{
		(close(pipe_fd[1]), close(in_fd));
		ft_error("dup input failed !");
	}
	(close(in_fd), close(pipe_fd[1]));
	execute_cmd(proc->av[i], proc->envp, 1);
}

void	end_mission(t_process *p, int *pipe_fd, int i)
{
	int	out_fd;

	close(pipe_fd[1]);
	if (p->here_doc)
		out_fd = open(p->av[p->ac - 1], O_RDWR | O_CREAT | O_APPEND, 0644);
	else
		out_fd = open(p->av[p->ac - 1], O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (out_fd == -1)
		(close(pipe_fd[0]), ft_error("open failed"));
	if (dup2(out_fd, STDOUT_FILENO) == -1)
	{
		close(pipe_fd[0]);
		(close(out_fd), ft_error("dup2 output file failed"));
	}
	close(out_fd);
	close(pipe_fd[0]);
	execute_cmd(p->av[i], p->envp, 0);
}

void	middle_mission(t_process *proc, int *pipe_fd, int i)
{
	close(pipe_fd[0]);
	if (dup2(pipe_fd[1], STDOUT_FILENO) == -1)
		(close(pipe_fd[1]), ft_error("dup2 input file failed !"));
	close(pipe_fd[1]);
	execute_cmd(proc->av[i], proc->envp, 0);
}

void	create_pipes_and_execute(t_process *proc)
{
	int		i;
	int		pipe_fd[2];
	pid_t	pid;

	i = 1 + proc->here_doc;
	while (++i < proc->ac - 1)
	{
		if (pipe(pipe_fd) == -1)
			ft_error("failed pipe");
		pid = fork ();
		if (pid == -1)
			ft_error("failed fork !");
		if (pid == 0)
		{
			if (i == 2 + proc->here_doc)
				first_mission(proc, pipe_fd, i);
			else if (i == proc->ac - 2)
				end_mission(proc, pipe_fd, i);
			middle_mission(proc, pipe_fd, i);
		}
		if (dup2(pipe_fd[0], STDIN_FILENO) == -1)
			(close(pipe_fd[0]), close(pipe_fd[1]), ft_error("dup2 failed"));
		(close(pipe_fd[1]), close(pipe_fd[0]));
	}
}
