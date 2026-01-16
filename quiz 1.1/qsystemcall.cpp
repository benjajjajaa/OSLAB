//BEN JUSTIN Z. ESPIRITU and MARIANE EUSTAQUIO
//quiz1 prelims 10:00am
//
//
//
//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void)
{
    int pid1, pid2;  //Variables to store process IDs from fork()

    // First fork
    pid1 = fork();

    if (pid1 < 0)
    {
        printf("First fork failed\n");
        exit(1);
    }
    else if (pid1 == 0)
    {
        // First child
        printf("First Child Process\n");
        printf("PID: %d | Parent PID: %d\n", getpid(), getppid());
        exit(0);
    }
    else
    {
        // Second fork (only parent reaches here)
        pid2 = fork();

        if (pid2 < 0)
        {
            printf("Second fork failed\n");
            exit(1);
        }
        else if (pid2 == 0)
        {
            // Second child
            printf("Second Child Process\n");
            printf("PID: %d | Parent PID: %d\n", getpid(), getppid());
            exit(0);
        }
        else
        {
            // Parent process
            printf("Parent Process\n");
            printf("PID: %d\n", getpid());

            // Wait for both children
            wait(NULL);
            wait(NULL);
        }
    }

    return 0;
}
