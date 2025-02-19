/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-gady <ael-gady@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 08:56:57 by ael-gady          #+#    #+#             */
/*   Updated: 2025/02/17 16:28:28 by ael-gady         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>//for perror
# include <unistd.h>//for write, execve, read,
# include <stdlib.h>//malloc
# include <sys/wait.h>//wait
# include <fcntl.h>//for system call open,
# include <sys/types.h>//pid_t

typedef struct s_pipex
{
	char	*infile;
	char	*outfile;
	char	**cmd1;
	char	**cmd2;
	int		pipe_fd[2];
}			t_pipex;

/*    libft utils :  */
void	ft_error(const char *msg);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strdup(const char *s);
size_t	ft_strlen(const char *s);
char	**ft_split(char const *s, char c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
//int		is_ls(char *cmd);
/* conception functions */
void	ft_error(const char *msg);
void	execute(char *cmd, char **envp);
char	*get_cmd_path(char **cmd_args, char **envp);
int		open_file(char *av, int key);
void	free_matrice(char **str);
#endif