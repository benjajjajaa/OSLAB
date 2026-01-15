#include <stdio.h>

int main(void)
{
    int n, i, j;
    int at[20], bt[20], pr[20];       // arrival time, burst time, priority
    int wt[20] = {0}, tat[20] = {0};  // waiting time, turnaround time
    int completed[20] = {0};          // process completion flag
    float wtavg = 0, tatavg = 0;

    printf("Enter the number of processes (max 20): ");
    scanf("%d", &n);

    if (n <= 0 || n > 20) {
        printf("Invalid number of processes.\n");
        return 1;
    }

    // Input in order: Arrival Time -> Burst Time -> Priority
    for (i = 0; i < n; i++) {
        printf("Enter Arrival Time for Process P%d: ", i);
        scanf("%d", &at[i]);
        printf("Enter Burst Time for Process P%d: ", i);
        scanf("%d", &bt[i]);
        printf("Enter Priority for Process P%d: ", i);
        scanf("%d", &pr[i]);
    }

    int time = 0;
    int completed_count = 0;

    // Non-preemptive priority scheduling
    while (completed_count < n) {
        int idx = -1;
        int highest_priority = 9999;

        // Find the highest priority process that has arrived and not completed
        for (i = 0; i < n; i++) {
            if (!completed[i] && at[i] <= time) {
                if (pr[i] < highest_priority) {
                    highest_priority = pr[i];
                    idx = i;
                } else if (pr[i] == highest_priority) {
                    if (at[i] < at[idx]) idx = i; // tie-breaker: earlier arrival
                }
            }
        }

        if (idx != -1) {
            wt[idx] = time - at[idx];
            if (wt[idx] < 0) wt[idx] = 0;
            tat[idx] = wt[idx] + bt[idx];
            time += bt[idx];
            completed[idx] = 1;
            completed_count++;
        } else {
            time++; // if no process has arrived yet
        }
    }

    // Calculate averages
    for (i = 0; i < n; i++) {
        wtavg += wt[i];
        tatavg += tat[i];
    }

    // Chronological output table
    printf("\n%-10s %-12s %-12s %-12s %-15s %-18s\n",
           "Process", "Arrival Time", "Burst Time", "Priority",
           "Waiting Time", "Turnaround Time");
    printf("--------------------------------------------------------------------------------------\n");

    for (i = 0; i < n; i++) {
        printf("P%-9d %-12d %-12d %-12d %-15d %-18d\n",
               i, at[i], bt[i], pr[i], wt[i], tat[i]);
    }

    printf("\nAverage Waiting Time = %.2f", wtavg / n);
    printf("\nAverage Turnaround Time = %.2f\n", tatavg / n);

    return 0;
}
