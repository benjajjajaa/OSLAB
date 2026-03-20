#include <stdio.h>

int main() {
    int alloc[10][10], max[10][10], need[10][10];
    int total[10], avail[10], work[10];
    int n, m;
    int i, j, count = 0;
    char finish[10];
    int safeSeq[10]; // To store the safe sequence

    // Step 1: Get number of processes and resources
    printf("Enter the number of processes and resources: ");
    scanf("%d%d", &n, &m);

    // Initialize finish array
    for(i = 0; i < n; i++)
        finish[i] = 'n';

    // Step 2: Get maximum claim matrix
    printf("Enter the maximum claim matrix (max):\n");
    for(i = 0; i < n; i++)
        for(j = 0; j < m; j++)
            scanf("%d", &max[i][j]);

    // Step 3: Get allocation matrix
    printf("Enter the allocation matrix (alloc):\n");
    for(i = 0; i < n; i++)
        for(j = 0; j < m; j++)
            scanf("%d", &alloc[i][j]);

    // Step 4: Get total resources
    printf("Enter the total resources vector:\n");
    for(i = 0; i < m; i++)
        scanf("%d", &total[i]);

    // Step 5: Calculate available resources
    for(i = 0; i < m; i++) {
        avail[i] = 0;
        for(j = 0; j < n; j++)
            avail[i] += alloc[j][i];
        work[i] = total[i] - avail[i];
    }

    // Step 6: Calculate need matrix
    for(i = 0; i < n; i++)
        for(j = 0; j < m; j++)
            need[i][j] = max[i][j] - alloc[i][j];

    // Step 7: Banker's Algorithm to find safe state
    int progress;
    do {
        progress = 0;
        for(i = 0; i < n; i++) {
            if(finish[i] == 'n') {
                int canRun = 1;
                for(j = 0; j < m; j++) {
                    if(need[i][j] > work[j]) {
                        canRun = 0;
                        break;
                    }
                }

                if(canRun) {
                    printf("Process %d is executing...\n", i + 1);
                    // Add its allocated resources back to work
                    for(j = 0; j < m; j++)
                        work[j] += alloc[i][j];
                    
                    finish[i] = 'y';
                    safeSeq[count] = i + 1; // Store process number
                    count++;
                    progress = 1;

                    // Print available resources after execution
                    printf("Available resources after executing process %d: ", i + 1);
                    for(j = 0; j < m; j++)
                        printf("%d ", work[j]);
                    printf("\n\n");
                }
            }
        }
    } while(progress);

    // Step 8: Check if system is in safe state
    if(count == n) {
        printf("The system is in a safe state.\n");
        printf("Safe sequence: ");
        for(i = 0; i < n; i++)
            printf("P%d ", safeSeq[i]);
        printf("\n");
    } else {
        printf("The system is NOT in a safe state.\n");
    }

    return 0;
}