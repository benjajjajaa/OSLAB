#include <stdio.h>

int main(void)
{
    int bt[20], rt[20], wt[20], tat[20];
    int i, n, tq;
    int time = 0, done;
    float wtavg = 0, tatavg = 0;

    printf("Enter the number of processes (max 20): ");
    scanf("%d", &n);

    if (n <= 0 || n > 20) {
        printf("Invalid number of processes.\n");
        return 1;
    }

    for (i = 0; i < n; i++) {
        printf("Enter Burst Time for Process %d: ", i);
        scanf("%d", &bt[i]);
        rt[i] = bt[i];
        wt[i] = 0;
    }

    printf("Enter Time Quantum: ");
    scanf("%d", &tq);

    // Round Robin Scheduling
    do {
        done = 1;
        for (i = 0; i < n; i++) {
            if (rt[i] > 0) {
                done = 0;

                if (rt[i] > tq) {
                    time += tq;
                    rt[i] -= tq;
                } else {
                    time += rt[i];
                    wt[i] = time - bt[i];
                    rt[i] = 0;
                }
            }
        }
    } while (!done);

    // Turnaround Time
    for (i = 0; i < n; i++) {
        tat[i] = bt[i] + wt[i];
        wtavg += wt[i];
        tatavg += tat[i];
    }

    // Clean, aligned table
    printf("\n%-10s %-12s %-15s %-18s\n",
           "Process", "Burst Time", "Waiting Time", "Turnaround Time");
    printf("------------------------------------------------------------\n");

    for (i = 0; i < n; i++) {
        printf("%-10d %-12d %-15d %-18d\n",
               i, bt[i], wt[i], tat[i]);
    }

    printf("\nAverage Waiting Time = %.2f", wtavg / n);
    printf("\nAverage Turnaround Time = %.2f\n", tatavg / n);

    return 0;
}
