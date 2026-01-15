#include <stdio.h>

int main()
{
    int n, i, completed = 0, time = 0;
    int pid[20], at[20], bt[20], wt[20], tat[20], done[20];
    float avgWT = 0, avgTAT = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    for (i = 0; i < n; i++)
    {
        pid[i] = i + 1;   // P1, P2, P3...
        done[i] = 0;

        printf("Enter Arrival Time of P%d: ", pid[i]);
        scanf("%d", &at[i]);

        printf("Enter Burst Time of P%d: ", pid[i]);
        scanf("%d", &bt[i]);
    }

    /* -------- SJF Scheduling (Chronological Execution) -------- */
    while (completed < n)
    {
        int idx = -1;
        int minBT = 9999;

        for (i = 0; i < n; i++)
        {
            if (at[i] <= time && done[i] == 0 && bt[i] < minBT)
            {
                minBT = bt[i];
                idx = i;
            }
        }

        if (idx == -1)
        {
            time++; // CPU idle
        }
        else
        {
            tat[idx] = (time + bt[idx]) - at[idx];  // TAT first
            wt[idx]  = tat[idx] - bt[idx];          // WT after

            time += bt[idx];
            done[idx] = 1;
            completed++;

            avgWT += wt[idx];
            avgTAT += tat[idx];
        }
    }

    /* -------- Output arranged as P1, P2, P3... -------- */
    printf("\nPROCESS\tAT\tBT\tTAT\tWT\n");
    for (i = 0; i < n; i++)
    {
        printf("P%d\t%d\t%d\t%d\t%d\n",
               pid[i], at[i], bt[i], tat[i], wt[i]);
    }

    printf("\nAverage Turnaround Time = %.2f", avgTAT / n);
    printf("\nAverage Waiting Time = %.2f", avgWT / n);
    printf("\n");

    return 0;
}
