/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-gady <ael-gady@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 13:10:25 by ael-gady          #+#    #+#             */
/*   Updated: 2025/01/29 18:44:36 by ael-gady         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_error()
{
	write(1, "Usage: ./pipex <infile> <cmd1> <cmd2> <outfile>\n", 48);
	exit(1);
}
void	parse_arg(char **av, int ac, t_pipex *pipex)
{
	if (ac != 5)
	{
		write(2, "Usage: ./pipex <infile> <cmd1> <cmd2> <outfile>\n", 48);
		exit(1);
	}
	pipex->infile = av[1];
	pipex->outfile = av[4];
	pipex->cmd1 = ft_split(av[2], ' ');//parse the cmd "tr ' ' '\n' !!!"
	pipex->cmd2 = ft_split(av[3], ' ');
}

int main(int ac, char **av, char **envp)/*		./pipex input.txt cmd1 cm2 output.txt		*/
{
	int		fd[2];
	pid_t	pid;
	t_pipex	pipex;

	if (ac != 5)
	{
		write(2, "Usage: ./pipex <infile> <cmd1> <cmd2> <outfile>\n", 48);
		exit(1);
	}
	parse_arg(av, ac, &pipex);
	execute_pipex(&pipex, av, envp);
}
