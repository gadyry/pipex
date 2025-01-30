/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-gady <ael-gady@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 08:56:57 by ael-gady          #+#    #+#             */
/*   Updated: 2025/01/29 10:53:38 by ael-gady         ###   ########.fr       */
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
	char	**cmd1;
	char	**cmd2;
}			t_pipex;

typedef struct s_fd
{
	int	input_fd;
	int	output_fd;
	int	pipe_fd[2];
}		t_fd;

void	parse_arg(char **av, int ac, t_pipex *pipex);
char	**ft_split(char const *s, char c);
char	*find_cmd_path(char **cmd, char **envp);
void	execute_pipex(t_pipex *pipex, char **av, char **envp);

#endif