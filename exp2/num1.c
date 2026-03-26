#include<stdio.h>

int main()
{
    int ms, bs, nob, ef, n;
    int mp[10], tif = 0;
    int i, p = 0;

    printf("Enter the total memory available (in Bytes) -- ");
    scanf("%d", &ms);

    printf("Enter the block size (in Bytes) -- ");
    scanf("%d", &bs);

    nob = ms / bs;
    ef = ms - nob * bs;

    printf("\nEnter the number of processes -- ");
    scanf("%d", &n);

    for(i = 0; i < n; i++)
    {
        printf("Enter memory required for process %d (in Bytes)-- ", i + 1);
        scanf("%d", &mp[i]);
    }

    printf("\nNo. of Blocks available in memory -- %d\n", nob);

    printf("\n%-10s %-20s %-12s %-20s",
           "PROCESS", "MEMORY REQUIRED", "ALLOCATED", "INTERNAL FRAG");

    for(i = 0; i < n && p < nob; i++)
    {
        printf("\n%-10d %-20d", i + 1, mp[i]);

        if(mp[i] > bs)
            printf("%-12s %-20s", "NO", "---");
        else
        {
            printf("%-12s %-20d", "YES", bs - mp[i]);
            tif = tif + bs - mp[i];
            p++;
        }
    }

    if(i < n)
        printf("\n\nMemory is Full, Remaining Processes cannot be accomodated");

    printf("\n\nTotal Internal Fragmentation is %d", tif);
    printf("\nTotal External Fragmentation is %d\n", ef);

    return 0;
}