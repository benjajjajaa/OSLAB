#include <stdio.h>
#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
#include <iomanip>
using namespace std;

#define MAX 1000
#define QUANTA 4

int flag[MAX], at[MAX], bt[MAX], pt[MAX], rt[MAX],
    ft[MAX], fe[MAX], fe_flag[MAX], pid[MAX],
    tms, qt[MAX];

// Queues for MLFQ
queue<int> rrQueue;        // Top queue: RR
vector<int> sjfQueue;      // Middle queue: SJF
queue<int> fcfsQueue;      // Bottom queue: FCFS

/* Round Robin execution for 1 time unit */
void RR() {
    if (!rrQueue.empty()) {
        int idx = rrQueue.front(); rrQueue.pop();
        if (fe[idx] == -1) fe[idx] = tms; // first execution

        qt[idx]++;
        rt[idx]--; //Process executes 1 time unit in Round Robin
        
        if (rt[idx] == 0) {
            ft[idx] = tms + 1;
            flag[idx] = 1;
        } else if (qt[idx] == QUANTA) {
            qt[idx] = 0;
            sjfQueue.push_back(idx); // move to SJF
        } else {
            rrQueue.push(idx); // continue in RR
        }
    }
}

int main() {
    int i, n = 0, sum = 0, large = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    for (i = 0; i < n; i++) {
        printf("\nEnter PID for process %d: ", i + 1);
        scanf("%d", &pid[i]);
        printf("Enter AT for process %d: ", i + 1);
        scanf("%d", &at[i]);
        printf("Enter BT for process %d: ", i + 1);
        scanf("%d", &bt[i]);
        printf("Enter P for process %d: ", i + 1);
        scanf("%d", &pt[i]);

        rt[i] = bt[i];
        qt[i] = 0;
        ft[i] = 0;
        fe[i] = -1;
        fe_flag[i] = 0;
        flag[i] = 0;
        sum += bt[i];
        if (at[i] > large) large = at[i];
    }

    int last_exec = -1;

    // Main loop
    for (tms = 0; tms <= sum + large; tms++) {
        // Add new arrivals to RR queue
        for (i = 0; i < n; i++) {
            if (at[i] == tms && !flag[i] && qt[i] == 0 && rt[i] > 0) {
                rrQueue.push(i);
            }
        }

        // 1️⃣ Top queue: RR
        if (!rrQueue.empty()) { //Decides which queue (RR, SJF, FCFS) will run next
            RR();
        }
        // 2️⃣ Middle queue: SJF
        else if (!sjfQueue.empty()) {
            // pick shortest remaining time
            sort(sjfQueue.begin(), sjfQueue.end(), [&](int a, int b) {
                return rt[a] < rt[b];
            });
            int idx = sjfQueue.front();
            sjfQueue.erase(sjfQueue.begin());

            if (fe[idx] == -1) fe[idx] = tms;
            rt[idx]--; //Process executes 1 time unit in SJF queue
            tms++; // advance time for execution

            if (rt[idx] == 0) {
                ft[idx] = tms;
                flag[idx] = 1;
            } else {
                fcfsQueue.push(idx); // move to FCFS
            }
            tms--; // adjust because main loop will increment
        }
        // 3️⃣ Bottom queue: FCFS
        else if (!fcfsQueue.empty()) {
            int idx = fcfsQueue.front(); fcfsQueue.pop();
            if (fe[idx] == -1) fe[idx] = tms;
            rt[idx]--; //Process executes 1 time unit in FCFS queue
            tms++;

            if (rt[idx] == 0) {
                ft[idx] = tms;
                flag[idx] = 1;
            } else {
                fcfsQueue.push(idx);
            }
            tms--;
        }
        // CPU idle
        else {
            continue;
        }
    }

    // Calculate WT
    for (i = 0; i < n; i++) {
        int WT = ft[i] - at[i] - bt[i];
        // print FE, FT, WT
    }

    // Print table
    cout << "\nPROCESS SCHEDULING TABLE\n";
    cout << "-------------------------------------------------------------\n";
    cout << left
         << setw(8) << "PID"
         << setw(8) << "AT"
         << setw(8) << "BT"
         << setw(8) << "P"
         << setw(8) << "FE"
         << setw(8) << "FT"
         << setw(8) << "WT" << endl;

    for (i = 0; i < n; i++) {
        int WT = ft[i] - at[i] - bt[i];
        cout << left
             << setw(8) << pid[i]
             << setw(8) << at[i]
             << setw(8) << bt[i]
             << setw(8) << pt[i]
             << setw(8) << fe[i]
             << setw(8) << ft[i]
             << setw(8) << WT << endl;
    }

    return 0;
}

/*
3
1 2 5 2
2 0 3 1
3 2 1 4

1 1 9 2
2 0 3 0
3 5 8 5
*/