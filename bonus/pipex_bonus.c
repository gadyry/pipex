/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-gady <ael-gady@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 15:11:15 by ael-gady          #+#    #+#             */
/*   Updated: 2025/02/02 11:06:07 by ael-gady         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	main(int ac, char **av, char **envp)
{
	int	here_doc;
	int	pipe_fd[2];

	if (ac >= 5)
	{
		here_doc = (!ft_strncmp(av[1], "her_doc"));
		if (here_doc)
		{
			pipe(pipe_fd);
			if (fork() == 0)
			{
				handle_here_doc(av[2], pipe_fd);//todo
				exit(0);
			}
			close(pipe_fd[1]);
		}
		create_pipes_and_execute(ac, av, envp, here_doc);//todo
	}
	else
	{
		write(2, "Usage: ./pipex <infile> <cmd_1> ...  <cmd_n> <outfile>\n", 55);
		exit(1);
	}
}