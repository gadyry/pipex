/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-gady <ael-gady@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 10:37:14 by ael-gady          #+#    #+#             */
/*   Updated: 2025/02/07 04:55:54 by ael-gady         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	handle_here_doc(char *limiter, int *pipe_fd)
{
	char	*line;

	close(pipe_fd[0]);
	while (1)
	{
		line = get_next_line(0);
		if (!line || !ft_strncmp(line, limiter, ft_strlen(limiter)))
			break;
		write(pipe_fd[1], line, ft_strlen(line));
		free(line);
	}
	free(line);
	close(pipe_fd[1]);
}

int	redirect_to_outfile(char *outfile, int here_doc)
{
	int	out_fd;

	if (here_doc)
		out_fd = open(outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		out_fd = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (out_fd == -1)
		ft_error("open failed");
	if (dup2(out_fd, 1) == -1)
		ft_error("dup2 output file failed");
	close(out_fd);
}

void	child_mission(int *pipe_fd, int prev_pipe_fd, int indice, int ac, char *av, int here_doc, char **envp)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		ft_error("fork failed");
	if (!pid)
	{
		if (dup2(prev_pipe_fd, 0) == -1)// void	ft_error_dup2(const char *msg, int *pipe_fd, int prev_pipe_fd)
			ft_error_dup2("dup2 input failed", pipe_fd, prev_pipe_fd);
		if (indice < ac - 2)
		{
			if (dup2(pipe_fd[1], 1) == -1)
				ft_error_dup2("dup2 input failed", pipe_fd, prev_pipe_fd);
		}
		else
			redirect_to_outfile(av[ac - 1], here_doc);
		close(pipe_fd[1]);
		execute_cmd(av[indice], envp);//todo
	}
}

void	create_pipes_and_execute(int ac, char **av, char **envp, int here_doc)
{
	int		i;
	int		pipe_fd[2];
	int		prev_pipe_fd;

	prev_pipe_fd = 0;
	if (here_doc)
		prev_pipe_fd = pipe_fd[0];
	i = 2 + here_doc;
	while (i < ac - 1)
	{
		if (pipe(pipe_fd) == -1)
			ft_error("failed pipe");
		child_mission(pipe_fd, prev_pipe_fd, i, ac, av, here_doc, envp);
		close(prev_pipe_fd);
		prev_pipe_fd = pipe_fd[0];
		i++;
	}
	while (wait(NULL) > 0);
}
