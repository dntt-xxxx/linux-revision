#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#define NUM_CHILDREN 3
#define MSG_SIZE 32

int main() {
    int pipe_fd[2];  // Array to hold the file descriptors for the pipe
    pid_t pid;
    char msg[MSG_SIZE];

    // Create the pipe
    if (pipe(pipe_fd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    // Create multiple child processes
    for (int i = 0; i < NUM_CHILDREN; i++) {
        pid = fork();

        if (pid < 0) {
            perror("fork");
            exit(EXIT_FAILURE);
        } else if (pid == 0) {
            // Child process
            printf("child process %d\n",i);
            close(pipe_fd[1]);  // Close unused write end of the pipe

            // Read message from the pipe
            ssize_t bytes_read = read(pipe_fd[0], msg, MSG_SIZE);
            if (bytes_read > 0) {
                msg[bytes_read] = '\0';  // Null-terminate the string
                printf("Child %d read: %s\n", i, msg);
            } else {
                perror("read");
            }

            close(pipe_fd[0]);  // Close the read end of the pipe
            exit(EXIT_SUCCESS);  // Child process exits
        }
        else {
            
        }
    }
    printf("parrent process\n");
    // Parent process
    close(pipe_fd[0]);  // Close unused read end of the pipe

    // Write a message to the pipe
    const char *parent_msg = "Hello from parent!";
    write(pipe_fd[1], parent_msg, MSG_SIZE);

    // Write a message to the pipe
    const char *parent_msg2 = "Hello from parent2!";
    write(pipe_fd[1], parent_msg2, MSG_SIZE);
        // Write a message to the pipe
    const char *parent_msg3 = "Hello from parent3!";
    write(pipe_fd[1], parent_msg3, MSG_SIZE);

    // close(pipe_fd[1]);  // Close the write end of the pipe

    // // Wait for all child processes to finish
    for (int i = 0; i < NUM_CHILDREN; i++) {
        wait(NULL);
    }

    // printf("Parent: All children have exited.\n");

    return 0;
}
