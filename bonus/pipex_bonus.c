/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-gady <ael-gady@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 15:11:15 by ael-gady          #+#    #+#             */
/*   Updated: 2025/02/17 22:44:40 by ael-gady         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	ft_error(const char *msg)
{
	perror(msg);
	exit(1);
}

int	main(int ac, char **av, char **envp)
{
	int	stdin_fd;

	stdin_fd = dup(0);
	if (ac < 5 || (ft_strncmp(av[1], "here_doc", 8) == 0 && ac < 6))
	{
		write(2, " ./pipex here_doc LIMITER cmd1 cmd2 ... cmdn outfile\n", 54);
		write(1, "or \n", 5);
		write(2, " ./pipex <infile> <cmd_1> ...  <cmd_n> <outfile>\n", 50);
		exit(1);
	}
	handle_here_doc_and_pipes(ac, av, envp);
	while (wait(NULL) != -1)
		;
	dup2(stdin_fd, 0);
	close(stdin_fd);
	return (0);
}
