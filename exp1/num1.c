#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>  // Include this for the wait() function

int main(int argc, char *arg[])  
{
    int pid = fork();
    
    if (pid < 0)  // Check if fork failed
    {
        printf("fork failed\n");
        exit(1);
    }
    else if (pid == 0)  // Child process
    {
        execlp("whoami", "whoami", NULL); 
        //error message
        printf("execlp failed\n");
        exit(1);
    }
    else  // Parent process
    {
        printf("\nProcess ID is: %d\n", getpid());
        wait(NULL);  
        exit(0);
    }
}
