#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    // Create the first child process
    pid_t pid = fork();

    if (pid < 0) {
        // fork() failed; print an error and exit
        perror("fork failed");
        exit(1);
    }
    else if (pid == 0) {  // Child process
        // Inside Child process

        // Create a grandchild process
        pid_t gpid = fork();

        if (gpid < 0) {
            // fork() failed in Child; print error and exit
            perror("fork failed");
            exit(1);
        }
        else if (gpid == 0) {  // Grandchild process
            // Inside Grandchild process
            // Print Grandchild info (indented to show hierarchy)
            printf("    Grandchild: PID=%d, Parent PID=%d\n", getpid(), getppid());

            // Replace the grandchild process with "whoami" command
            execlp("whoami", "whoami", NULL);

            // If execlp fails, print an error
            perror("execlp failed");
            exit(1);
        }
        else {  
            // Still inside Child process
            // Wait for Grandchild to finish before printing Child info
            wait(NULL);

            // Print Child info (indented to show hierarchy)
            printf("  Child: PID=%d, Parent PID=%d\n", getpid(), getppid());

            // Child exits after printing
            exit(0);
        }
    }
    else {  // Parent process
        // Wait for Child (and by extension Grandchild) to finish
        wait(NULL);

        // Print Parent info
        printf("Parent: PID=%d\n", getpid());

        // Parent exits
        exit(0);
    }

    return 0; // Not strictly needed, but good practice
}
