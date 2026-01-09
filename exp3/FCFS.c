#include <stdio.h>

int main(void)
{
    int bt[20], wt[20], tat[20]; //capable of storing 20 intgrs
    int i, n; //i → loop counter ; n → number of processes
    float wtavg = 0, tatavg = 0; // initialize to zero, bc auto 

    printf("Enter the number of processes (max 20): ");
    scanf("%d", &n); //Reads the number of processes and stores it in n

    if (n <= 0 || n > 20) {
        printf("Invalid number of processes.\n");
        return 1;
    }

    for (i = 0; i < n; i++) { // loops until the number or processes is not met
        printf("Enter Burst Time for Process %d: ", i);
        scanf("%d", &bt[i]); //stores in burst time array
    }

    wt[0] = 0; //first process never waits
    tat[0] = bt[0]; //turn around time is equal to burst time

    for (i = 1; i < n; i++) {
        wt[i] = wt[i - 1] + bt[i - 1];
        tat[i] = tat[i - 1] + bt[i];
        wtavg += wt[i];
        tatavg += tat[i];
    }

    printf("\nPROCESS\tBURST TIME\tWAITING TIME\tTURNAROUND TIME\n");
    for (i = 0; i < n; i++) {
        printf("P%d\t%d\t\t%d\t\t%d\n", i, bt[i], wt[i], tat[i]);
    } //stores the output

    printf("\nAverage Waiting Time = %.2f", wtavg / n); //formula for AWT
    printf("\nAverage Turnaround Time = %.2f\n", tatavg / n); //formula for ATT

    return 0;
}

//Easy to implement
//No starvation - A process is ready to run, but never gets a chance.

//Poor average waiting time - how long a process sits in the ready queue doing nothing before it gets the CPU.