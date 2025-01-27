#include <libc.h>

int main(int ac, char **av, char **env)
{
	int pid;
	char *arg[2];
	int fds[2];// --> fd[0] : read &&  fd[1] : write 

	pipe(fds);
	pid = fork();
	if (pid == 0)
	{
		arg[0] = strdup(av[1]);
		arg[1] = NULL;
		dup2(fds[1], 1);
		execve("/bin/ls", arg, env);
	}
	else
	{
		pid = fork();
		if (pid == 0)
		{
			arg[0] = strdup(av[2]);
			arg[1] = NULL;
			dup2(fds[0], 0);
			execve("/bin/cat", arg, env);
		}
	}
	wait(&pid);
}

/*
	fork();
	execve();
	dup2
	dup
	pipe
	ls > file
*/