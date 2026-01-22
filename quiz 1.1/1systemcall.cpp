#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        perror("fork failed");
        exit(1);
    }
    else if (pid == 0) {  // Child process
        pid_t gpid = fork();

        if (gpid < 0) {
            perror("fork failed");
            exit(1);
        }
        else if (gpid == 0) {  // Grandchild
            printf("    Grandchild: PID=%d, Parent PID=%d\n",
                   getpid(), getppid());

            execlp("whoami", "whoami", NULL);

            perror("execlp failed");
            exit(1);
        }
        else {  // Child
            // WAIT for the specific grandchild
            waitpid(gpid, NULL, 0);

            printf("  Child: PID=%d, Parent PID=%d\n",
                   getpid(), getppid());

            exit(0);
        }
    }
    else {  // Parent
        // WAIT for the specific child
        waitpid(pid, NULL, 0);

        printf("Parent: PID=%d\n", getpid());
        exit(0);
    }
}

//child waits for its own grandchild
//parent waits for its own child
//Prevents race conditions

/*
Output order is guaranteed:
1.Grandchild
2.Child
3.Parent
*/

//whoami will simply show which user the grandchild is running under.
//wait() is a system call that makes the parent process pause execution until one of its child processes finishes.
//Without wait(), the parent might finish before the child, and the child process becomes a zombie 
//duplicating the current process. The new process is called the child, and the original process is the parent.
