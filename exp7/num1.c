#include <stdio.h>

int main()
{
    int alloc[10][10], max[10][10];
    int avail[10], work[10], total[10];
    int i, j, k, n, need[10][10];
    int m;
    int count = 0, c;
    char finish[10];

    printf("Enter the no. of processes and resources: ");
    scanf("%d%d", &n, &m);

    for(i = 0; i < n; i++)
        finish[i] = 'n';

    printf("Enter the claim matrix:\n");
    for(i = 0; i < n; i++)
        for(j = 0; j < m; j++)
            scanf("%d", &max[i][j]);

    printf("Enter the allocation matrix:\n");
    for(i = 0; i < n; i++)
        for(j = 0; j < m; j++)
            scanf("%d", &alloc[i][j]);

    printf("Enter the resource vector:\n");
    for(i = 0; i < m; i++)
        scanf("%d", &total[i]);

    // Calculate available resources
    for(i = 0; i < m; i++)
        avail[i] = 0;

    for(i = 0; i < n; i++)
        for(j = 0; j < m; j++)
            avail[j] += alloc[i][j];

    for(i = 0; i < m; i++)
        work[i] = total[i] - avail[i];

    // Calculate need matrix
    for(i = 0; i < n; i++)
        for(j = 0; j < m; j++)
            need[i][j] = max[i][j] - alloc[i][j];

    // Banker's Algorithm
    while(count < n)
    {
        int found = 0;

        for(i = 0; i < n; i++)
        {
            if(finish[i] == 'n')
            {
                c = 0;
                for(j = 0; j < m; j++)
                {
                    if(need[i][j] <= work[j])
                        c++;
                }

                if(c == m)
                {
                    printf("Process %d can execute\n", i + 1);

                    for(k = 0; k < m; k++)
                        work[k] += alloc[i][k];

                    finish[i] = 'y';
                    count++;
                    found = 1;
                }
            }
        }

        if(!found)
        {
            printf("\nSystem is NOT in safe state\n");
            return 0;
        }
    }

    printf("\nSystem is in SAFE state\n");
    return 0;
}