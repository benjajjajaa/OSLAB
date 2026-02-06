#include<stdio.h>
#include<iostream>
#include<queue>

using namespace std;

#define MAX 1000
#define QUANTA 4

int flag[MAX], at[MAX], bt[MAX], pt[MAX], rt[MAX];
int ft[MAX], fe[MAX], fe_flag[MAX], pid[MAX];
int tms, qt[MAX];

queue<int> q;  // RR queue

void RR()
{
    if (!q.empty())
    {
        if (rt[q.front()] > 0 && qt[q.front()] < 4)
        {
            qt[q.front()]++;
            rt[q.front()]--;

            if (rt[q.front()] == 0)
            {
                ft[q.front()] = tms + 1;
                q.pop();
            }
            if (!q.empty() && rt[q.front()] != 0 && qt[q.front()] == 4)
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
    int i, n, smallest = 0, last_smallest = -1;
    int min, sum = 0, large = 0;

    // -------- ORGANIZED INPUT --------
    cout << "Enter number of processes: ";
    cin >> n;

    cout << "\nEnter process details:\n";
    cout << "PID  AT  BT  PT\n";

    for (i = 0; i < n; i++)
    {
        cin >> pid[i] >> at[i] >> bt[i] >> pt[i];

        rt[i] = bt[i];
        sum += bt[i];

        if (at[i] > large)
            large = at[i];

        flag[i] = qt[i] = fe_flag[i] = 0;
        fe[i] = ft[i] = 0;
    }

    min = MAX;

    // -------- SCHEDULING --------
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
            RR();
            continue;
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
            ((rt[smallest] == 0) || (bt[smallest] - rt[smallest]) == QUANTA))
        {
            if (rt[smallest] == 0)
            {
                ft[smallest] = tms + 1;
                flag[smallest] = 1;
            }
            else
            {
                q.push(smallest);
                flag[smallest] = 1;
            }
        }

        last_smallest = smallest;
    }

    // -------- TABLE OUTPUT --------
    cout << "\nPROCESS SCHEDULING TABLE\n";
    cout << "-------------------------------------------------------------\n";
    cout << "PID\tAT\tBT\tPT\tFE\tFT\tWT\n";
    cout << "-------------------------------------------------------------\n";

    for (i = 0; i < n; i++)
    {
        cout << pid[i] << "\t"
             << at[i] << "\t"
             << bt[i] << "\t"
             << pt[i] << "\t"
             << fe[i] << "\t"
             << ft[i] << "\t"
             << ft[i] - bt[i] - at[i] << endl;
    }

    cout << "-------------------------------------------------------------\n";

    return 0;
}