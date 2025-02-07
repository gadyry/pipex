/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-gady <ael-gady@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 10:45:52 by ael-gady          #+#    #+#             */
/*   Updated: 2025/02/07 03:45:48 by ael-gady         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define	PIPEX_H

#include <stdio.h>//for building

# include <unistd.h>//for write, execve, read,
# include <stdlib.h>//malloc
# include <sys/wait.h>//wait
# include <fcntl.h>//for system call open,
# include <sys/_types.h>//pid_t

typedef struct s_pipex
{
	char	*infile;
	char	*outfile;
}			t_pipex;


void	ft_error(const char *msg);
void	ft_error_dup2(const char *msg, int *pipe_fd, int prev_pipe_fd);
void	handle_here_doc(char *limiter, int *pipe_fd);
void	create_pipes_and_execute(int ac, char **av, char **envp, int here_doc);

#endif