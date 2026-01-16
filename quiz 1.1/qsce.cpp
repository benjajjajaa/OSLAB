// BEN JUSTIN Z. ESPIRITU and MARIANE EUSTAQUIO
// quiz1 prelims 10:00am

#include <stdio.h>      // Provides printf()
#include <stdlib.h>     // Provides exit()
#include <unistd.h>     // Provides fork(), getpid(), getppid()
#include <sys/wait.h>   // Provides wait()

int main(void)
{
    int pid1, pid2;     // Variables to store process IDs from fork()

    // Create the first child process
    pid1 = fork();

    // Check if the first fork failed
    if (pid1 < 0)
    {
        printf("First fork failed\n"); // Print error message
        exit(1);                       // Exit program with error code
    }
    // This block runs in the first child process
    else if (pid1 == 0)
    {
        printf("First Child Process\n");              // Identify first child
        printf("PID: %d | Parent PID: %d\n",          // Print child PID and parent PID
               getpid(), getppid());
        exit(0);                                      // End first child process
    }
    // This block runs only in the parent process
    else
    {
        // Create the second child process
        pid2 = fork();

        // Check if the second fork failed
        if (pid2 < 0)
        {
            printf("Second fork failed\n"); // Print error message
            exit(1);                        // Exit program with error code
        }
        // This block runs in the second child process
        else if (pid2 == 0)
        {
            printf("Second Child Process\n");         // Identify second child
            printf("PID: %d | Parent PID: %d\n",      // Print child PID and parent PID
                   getpid(), getppid());
            exit(0);                                 // End second child process
        }
        // This block runs in the parent process only
        else
        {
            printf("Parent Process\n");               // Identify parent
            printf("PID: %d\n", getpid());            // Print parent PID

            // Parent waits for both child processes to finish
            wait(NULL);                               // Wait for first child
            wait(NULL);                               // Wait for second child
        }
    }

    return 0; // End of program
}
