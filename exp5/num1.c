#include <stdio.h>

int main()
{
    int ms, mp[10], i, temp, n = 0;
    char ch = 'y';

    printf("Enter the total memory available (in Bytes) -- ");
    scanf("%d", &ms);
    temp = ms;

    for (i = 0; ch == 'y'; i++, n++)
    {
        printf("Enter memory required for process %d (in Bytes) -- ", i + 1);
        scanf("%d", &mp[i]);

        if (mp[i] <= temp)
        {
            printf("Memory is allocated for Process %d\n", i + 1);
            temp -= mp[i];
        }
        else
        {
            printf("Memory is Full\n");
            break;
        }

        printf("Do you want to continue (y/n) -- ");
        scanf(" %c", &ch);
    }

    printf("\nTotal Memory Available -- %d\n", ms);

    printf("\n\tPROCESS\t\tMEMORY ALLOCATED\n");
    for (i = 0; i < n; i++)
        printf("\t%d\t\t%d\n", i + 1, mp[i]);

    printf("\nTotal Memory Allocated is %d\n", ms - temp);
    printf("Total External Fragmentation is %d\n", temp);

    return 0;
}