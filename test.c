// #include <fcntl.h>
// #include <unistd.h>
// #include <stdio.h>

// int main() {
// 	int fd = open("output.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
// 	if (fd == -1) {
// 		perror("open");
// 		return 1;
// 	}

// 	// Redirect standard output (stdout) to "output.txt"
// 	if (dup2(fd, STDOUT_FILENO) == -1) {
// 		perror("dup2");
// 		return 1;
// 	}

// 	// Now, printf will write to "output.txt" instead of stdout
// 	printf("This will be written to output.txt\n");

// 	close(fd);
// 	return 0;
// }


// #include <fcntl.h>
// #include <unistd.h>
// #include <stdio.h>
// #include <sys/wait.h>

// int main() {
//     int pipe_fd[2];  // Pipe file descriptors
//     pid_t pid;

//     // Step 1: Create the pipe
//     if (pipe(pipe_fd) == -1) {
//         perror("pipe");
//         return 1;
//     }

//     // Step 2: Fork the first child process (for the first command)
//     if ((pid = fork()) == -1) {
//         perror("fork");
//         return 1;
//     }

//     if (pid == 0) {  // Child 1 - "echo Hello"
//         // Close the read end of the pipe because we're writing to the pipe
//         close(pipe_fd[0]);

//         // Redirect stdout to the write-end of the pipe
//         if (dup2(pipe_fd[1], STDOUT_FILENO) == -1) {
//             perror("dup2");
//             return 1;
//         }

//         // Close the pipe's write-end since we no longer need it after redirecting
//         close(pipe_fd[1]);

//         // Run the first command (e.g., "echo Hello")
//         execlp("echo", "echo", "Hello \nlHelloooo", NULL);

//         // If exec fails
//         perror("execlp");
//         return 1;
//     }

//     // Step 3: Fork the second child process (for the second command)
//     if ((pid = fork()) == -1) {
//         perror("fork");
//         return 1;
//     }

//     if (pid == 0) {  // Child 2 - "grep Hello"
//         // Close the write end of the pipe because we're reading from the pipe
//         close(pipe_fd[1]);

//         // Redirect stdin to the read-end of the pipe
//         if (dup2(pipe_fd[0], STDIN_FILENO) == -1) {
//             perror("dup2");
//             return 1;
//         }

//         // Close the pipe's read-end since we no longer need it after redirecting
//         close(pipe_fd[0]);

//         // Run the second command (e.g., "grep Hello")
//         execlp("grep", "grep", "Hello", NULL);

//         // If exec fails
//         perror("execlp");
//         return 1;
//     }

//     // Step 4: Close both ends of the pipe in the parent process, since we're done
//     close(pipe_fd[0]);
//     close(pipe_fd[1]);

//     // Step 5: Wait for the child processes to finish
//     wait(NULL);
//     wait(NULL);

//     return 0;
// }


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    int pipe_fd[2];
    pid_t pid1, pid2;

    // Create a pipe
    if (pipe(pipe_fd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    // First child process (cat)
    if ((pid1 = fork()) == 0) {
        // Close the read-end of the pipe (not needed in "cat" process)
        close(pipe_fd[0]);

        // Redirect stdout to the write-end of the pipe
        if (dup2(pipe_fd[1], STDOUT_FILENO) == -1) {
            perror("dup2");
            exit(EXIT_FAILURE);
        }

        // Close the write-end after duplicating
        close(pipe_fd[1]);

        // Execute cat (waits for user input)
        execlp("cat", "cat", NULL);

        // If execlp fails
        perror("execlp");
        exit(EXIT_FAILURE);
    }

    // Second child process (ls)
    if ((pid2 = fork()) == 0) {
        // Close both ends of the pipe because ls does NOT read from stdin
        close(pipe_fd[0]);
        close(pipe_fd[1]);

        // Execute ls normally
        execlp("ls", "ls", NULL);

        // If execlp fails
        perror("execlp");
        exit(EXIT_FAILURE);
    }

    // Parent closes both ends of the pipe
    close(pipe_fd[0]);
    close(pipe_fd[1]);

    // Wait for both child processes to finish
    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);

    return 0;
}
