#include <stdio.h>
#include <iostream>
#include <queue>
#include <iomanip>

using namespace std;

#define MAX 1000
#define QUANTA 4

int flag[MAX], at[MAX], bt[MAX], pt[MAX], rt[MAX],
    ft[MAX], fe[MAX], fe_flag[MAX], pid[MAX],
    tms, qt[MAX];

queue<int> q;   // Round Robin queue

/* Round Robin execution for 1 time unit */
void RR()
{
    if (!q.empty())
    {
        if (rt[q.front()] > 0 && qt[q.front()] < QUANTA)
        {
            qt[q.front()]++;
            rt[q.front()]--;

            if (rt[q.front()] == 0)
            {
                ft[q.front()] = tms + 1;
                q.pop();
            }
            else if (qt[q.front()] == QUANTA)
            {
                qt[q.front()] = 0;
                q.push(q.front());
                q.pop();
            }
        }
    }
}

int main()
{
    int i, n = 0, smallest = 0, last_smallest = -1;
    int min, sum = 0, large = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    for (i = 0; i < n; i++)
    {
        printf("\nEnter PID for process %d: ", i + 1);
        scanf("%d", &pid[i]);

        printf("Enter AT for process %d: ", i + 1);
        scanf("%d", &at[i]);

        printf("Enter BT for process %d: ", i + 1);
        scanf("%d", &bt[i]);

        printf("Enter P for process %d: ", i + 1);
        scanf("%d", &pt[i]);

        rt[i] = bt[i];
        sum += bt[i];

        if (at[i] > large)
            large = at[i];
    }

    /* Main scheduler loop */
    for (tms = 0; !q.empty() || tms <= sum + large; tms++)
    {
        min = MAX;
        smallest = -1;

        for (i = 0; i < n; i++)
        {
            if (at[i] <= tms && pt[i] < min && rt[i] > 0 && !flag[i])
            {
                min = pt[i];
                smallest = i;
            }
        }

        if (smallest == -1 && !q.empty())
        {
            if (last_smallest != -1 && rt[last_smallest] == 0)
            {
                ft[last_smallest] = tms;
                flag[last_smallest] = 1;
            }
            last_smallest = -1;
            RR();
            continue;
        }
        else if (smallest != -1 && !q.empty() && last_smallest == -1)
        {
            if (qt[q.front()] > 0 && qt[q.front()] <= QUANTA)
            {
                q.push(q.front());
                q.pop();
            }
        }

        if (smallest != -1 && !fe_flag[smallest])
        {
            fe[smallest] = tms - at[smallest];
            fe_flag[smallest] = 1;
        }

        if (smallest != last_smallest && last_smallest != -1 && !flag[last_smallest])
        {
            q.push(last_smallest);
            flag[last_smallest] = 1;
        }

        if (smallest != -1)
            rt[smallest]--;

        if (smallest != -1 &&
            (rt[smallest] == 0 || (bt[smallest] - rt[smallest]) == QUANTA))
        {
            if ((bt[smallest] - rt[smallest]) == QUANTA && rt[smallest] != 0)
            {
                flag[smallest] = 1;
                q.push(smallest);
            }
            else
            {
                ft[smallest] = tms + 1;
                flag[smallest] = 1;
            }
        }

        last_smallest = smallest;
    }

    /* Output table */
    cout << "\nPROCESS SCHEDULING TABLE\n";
    cout << "-------------------------------------------------------------------\n";
    cout << left
         << setw(8) << "PID"
         << setw(8) << "AT"
         << setw(8) << "BT"
         << setw(8) << "PT"
         << setw(8) << "FE"
         << setw(8) << "FT"
         << setw(8) << "TAT"
         << setw(8) << "WT" << endl;

    for (i = 0; i < n; i++)
    {
        int TAT = ft[i] - at[i]; // Turnaround Time
        int WT = TAT - bt[i];    // Waiting Time

        cout << left
             << setw(8) << pid[i]
             << setw(8) << at[i]
             << setw(8) << bt[i]
             << setw(8) << pt[i]
             << setw(8) << fe[i]
             << setw(8) << ft[i]
             << setw(8) << TAT
             << setw(8) << WT
             << endl;
    }

    return 0;
}
