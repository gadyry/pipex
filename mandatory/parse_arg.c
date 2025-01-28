/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-gady <ael-gady@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 09:16:12 by ael-gady          #+#    #+#             */
/*   Updated: 2025/01/28 10:09:08 by ael-gady         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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
