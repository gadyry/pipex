/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-gady <ael-gady@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 10:45:52 by ael-gady          #+#    #+#             */
/*   Updated: 2025/02/12 15:41:19 by ael-gady         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <unistd.h>//for write, execve, read,
# include <stdlib.h>//malloc
# include <sys/wait.h>//wait
# include <fcntl.h>//for system call open,
# include <sys/types.h>//pid_t

# include <libc.h>//for debugging !

#  define BUFFER_SIZE 69


typedef struct s_process
{
	int		ac;
	int		here_doc;
	char	**av;
	char	**envp;
	int		prev_pipe_fd;
}	t_process;


/*  get_next_line  && utils */
int		check_retline(char *line);
char	*ft_strjoin_get_next(char *s1, char *s2);
char	*get_next_line(int fd);
char	**ft_split(const char *s, char c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_strlen(const char *s);
char	*ft_strjoin(char const *s1, char const *s2);
/* pipex functions */
char	*ft_strdup(const char *s);
void	ft_error(const char *msg);
void	ft_error_dup2(const char *msg, int *pipe_fd, int prev_pipe_fd);
void	handle_here_doc(char *limiter, int *pipe_fd);
void	create_pipes_and_execute(t_process *proc);
void	execute_cmd(char *cmd_, char **envp);
void	handle_here_doc_and_pipes(int ac, char **av, char **envp);

#endif