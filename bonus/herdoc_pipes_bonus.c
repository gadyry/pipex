/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc_pipes_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-gady <ael-gady@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 10:33:40 by ael-gady          #+#    #+#             */
/*   Updated: 2025/02/18 09:53:28 by ael-gady         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	init_process(t_process *proc, int ac, char **av, char **envp)
{
	proc->ac = ac;
	proc->av = av;
	proc->envp = envp;
	proc->here_doc = (!ft_strncmp(av[1], "here_doc", 8));
	proc->here_fd = -1;
	proc->fd_tmp = -1;
}

void	handle_here_doc_and_pipes(int ac, char **av, char **envp)
{
	int			pipe_fd[2];
	t_process	proc;

	init_process(&proc, ac, av, envp);
	if (proc.here_doc)
		handle_here_doc(av[2], pipe_fd, &proc);
	create_pipes_and_execute(&proc);
	close(proc.fd_tmp);
}
