#include <stdio.h>

int main()
{
    int p[20], at[20], bt[20], wt[20], tat[20], done[20];
    int i, n, time = 0, completed = 0;
    float wtavg = 0, tatavg = 0;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    for (i = 0; i < n; i++)
    {
        p[i] = i + 1;     // P1, P2, P3...
        done[i] = 0;

        printf("Enter Arrival Time for Process P%d: ", p[i]);
        scanf("%d", &at[i]);

        printf("Enter Burst Time for Process P%d: ", p[i]);
        scanf("%d", &bt[i]);
    }

    /* -------- SJF Scheduling -------- */
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
            tat[idx] = (time + bt[idx]) - at[idx];  // Turnaround Time first
            wt[idx]  = tat[idx] - bt[idx];          // Waiting Time

            time += bt[idx];
            done[idx] = 1;
            completed++;

            tatavg += tat[idx];
            wtavg += wt[idx];
        }
    }

    /* -------- Output -------- */
    printf("\nPROCESS\tAT\tBT\tTAT\tWT\n");
    for (i = 0; i < n; i++)
    {
        printf("P%d\t%d\t%d\t%d\t%d\n",
               p[i], at[i], bt[i], tat[i], wt[i]);
    }

    printf("\nAverage Turnaround Time = %.2f", tatavg / n);
    printf("\nAverage Waiting Time = %.2f", wtavg / n);
    printf("\n");

    return 0;
}
