/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-gady <ael-gady@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 13:10:25 by ael-gady          #+#    #+#             */
/*   Updated: 2025/01/28 10:15:11 by ael-gady         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_error()
{
	write(1, "Usage: ./pipex <infile> <cmd1> <cmd2> <outfile>\n", 48);
	exit(1);
}

int main(int ac, char **av, char **env)/*		./pipex input.txt cmd1 cm2 output.txt		*/
{
	int		fd[2];
	pid_t	pid;
	t_pipex	pipex;

	parse_arg(av, ac, &pipex);
	
	printf("%s\n", pipex.infile);
	printf("%s\n", pipex.outfile);
	printf("\n-----------------\n");
	for(int i = 0; pipex.cmd1[i] != NULL; i++)
		printf("%s ", pipex.cmd1[i]);
	printf("\n-----------------\n");
	for(int i = 0; pipex.cmd2[i] != NULL; i++)
	{
		printf("|  %d |->", i);
		printf("%s ", pipex.cmd2[i]);		
	}
	printf("\n-----------------\n");
	
}