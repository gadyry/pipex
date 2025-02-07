#include <libc.h>

// int main(int ac, char **av, char **env)
// {
// 	int pid;
// 	char *arg[2];
// 	int fds[2];// --> fd[0] : read &&  fd[1] : write

// 	pipe(fds);
// 	pid = fork();
// 	if (pid == 0)
// 	{
// 		arg[0] = strdup(av[1]);
// 		arg[1] = NULL;
// 		dup2(fds[1], 1);
// 		execve("/bin/ls", arg, env);
// 	}
// 	else
// 	{
// 		pid = fork();
// 		if (pid == 0)
// 		{
// 			arg[0] = strdup(av[2]);
// 			arg[1] = NULL;
// 			dup2(fds[0], 0);
// 			execve("/bin/cat", arg, env);
// 		}
// 	}
// 	wait(&pid);
// }

/*

	fork();
	execve();
	dup2
	dup
	pipe
	ls > file

*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
	int pipe_fd[2];
	int	fd[2];

	if (pipe(pipe_fd) == -1)
	{
		perror("pipe");
		return (EXIT_FAILURE);
	}
	if (pipe(fd) == -1)
	{
		perror("pipe");
		return (EXIT_FAILURE);
	}

	printf("pipe_fd[0] = %d (lecture)\n", pipe_fd[0]);
	printf("pipe_fd[1] = %d (écriture)\n", pipe_fd[1]);
	printf("-----------------------------------------\n");
	printf("fd[0] = %d (lecture)\n", fd[0]);
	printf("fd[1] = %d (écriture)\n", fd[1]);

	close(fd[1]);
	close(fd[0]);
	close(pipe_fd[1]);
	close(pipe_fd[0]);
	return 0;
}
