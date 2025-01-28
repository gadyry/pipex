/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-gady <ael-gady@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 10:23:56 by ael-gady          #+#    #+#             */
/*   Updated: 2025/01/28 19:33:48 by ael-gady         ###   ########.fr       */
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
	t_fd	*fd;
	pid_t	pid1;
	pid_t	pid2;

	fd->input_fd = open(pipex->infile, O_RDONLY, 0644);
	if (fd->input_fd == -1)
	{
		perror("Problem in opening the file !!\n");
		free_t_pipex(pipex);
		exit(1);		
	}
	fd->output_fd = open(pipex->outfile, O_WRONLY | O_CREAT | O_TRUNC);//O_TRUNC : If the file already exists, truncate its content to zero length (i.e., erase its content).
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
		dup2(fd->input_fd, 0);// Redirect stdin to infile
		dup2(fd->pipe_fd[1], 1);// Redirect stdout to pipe write-end
		close(fd->pipe_fd[0]);// Close unused write-end
		close(fd->input_fd);
		close(fd->output_fd);
		close(fd->pipe_fd[1]);
		//execute cm1 : get_cmd_path execev(cmd_path, cmd_argv, envp)
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
		
	}
	close(fd->pipe_fd[0]);
	close(fd->pipe_fd[1]);
	close(fd->input_fd);
	close(fd->output_fd);
	
}

