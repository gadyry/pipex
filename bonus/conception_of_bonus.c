/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conception_of_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-gady <ael-gady@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 15:11:15 by ael-gady          #+#    #+#             */
/*   Updated: 2025/01/30 15:13:12 by ael-gady         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*************  1. Start with Multiple Commands (Core Bonus)    *************/

int num_cmds = argc - 3 - here_doc; // Adjust based on here_doc
int **pipes = create_pipes(num_cmds - 1);

for (int i = 0; i < num_cmds; i++) {
    pid_t pid = fork();
    if (pid == 0) {
        // Child: Redirect input/output and exec
        if (i == 0) 
            redirect_input(infile_fd);
        else 
            dup2(pipes[i-1][0], STDIN_FILENO);

        if (i == num_cmds - 1) 
            redirect_output(outfile_fd, append_mode);
        else 
            dup2(pipes[i][1], STDOUT_FILENO);

        close_all_pipes(pipes, num_cmds - 1);
        exec_command(cmd[i]);
    }
}
// Parent closes pipes and waits

/******************************************************************************/