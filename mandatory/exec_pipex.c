/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-gady <ael-gady@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 10:23:56 by ael-gady          #+#    #+#             */
/*   Updated: 2025/01/28 13:17:49 by ael-gady         ###   ########.fr       */
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

void	execute_pipex(t_pipex *pipex)
{
	int		pipe_fd[2];
	pid_t	pid1;
	pid_t	pid2;
	int		in_fd;
	int		out_fd;

	in_fd = open(pipex->infile, O_RDONLY, 0644);
	if (in_fd == -1)
	{
		perror("Problem in opening the file !!\n");
		free_t_pipex(pipex);
		exit(1);		
	}
	out_fd = open(pipex->outfile, O_WRONLY | O_CREAT | O_TRUNC);//O_TRUNC : If the file already exists, truncate its content to zero length (i.e., erase its content).
	if (out_fd == -1)
	{
		fclose(in_fd);
		perror("Problem in opening the file !!\n");
		free_t_pipex(pipex);
		exit(1);
	}
	// create a pipe
	if (pipe(pipe_fd) == -1)
	{
		perror("Pipe failed !!\n");
		free_t_pipex(pipex);
		exit(1);
	}
	// Fork the first child for cmd1
	pid1 = fork();
	if (pid1 == 0)
	{
		dup2(in_fd, 0);// Redirect stdin to infile
		dup2(pipe_fd[1], 1);// Redirect stdout to pipe write-end
		close(pipe_fd[0]);// Close unused write-end
		close(in_fd);
		close(out_fd);
		close(pipe_fd[1]);
		//execute cm1 :
	}
}
