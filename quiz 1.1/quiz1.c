//BEN JUSTIN Z. ESPIRITU and MARIANE EUSTAQUIO
//quiz1 prelims till 10:00am
//program that implement system calls with function of fork and PID and using system call wait. it must show 3 PID in one run using the fork.
//first come first serve simulation where, it can display Average turn around time and average waiting time. that can process 10 process the burst time, the burst time are 3, 5, 4, 3, 2, 1, 0, 7, 8, 1
//implement a shortest job first that can hold 5 process. the burst time are 50.54, 10.11, 33.34, 2.5, 101.1 
//round robin with time quantum as 20.

#include <iostream>   // For input/output (cout, endl)
#include <iomanip>    // For controlling decimal places (setprecision)
using namespace std;

int main()
{
    int p[5], i, j;  // Array for process numbers (p[0] = P0, p[1] = P1, etc.)
                      // i and j are loop counters

    // Burst times for 5 processes (given in the problem)
    float bt[5] = {50.54, 10.11, 33.34, 2.50, 101.10}; 

    float wt[5], tat[5];      // Arrays for waiting time and turnaround time
    float wtavg = 0, tatavg = 0, temp;  // Variables for average calculation and swapping

    int n = 5;  // Number of processes

    // Initialize process numbers (P0, P1, P2, ...)
    for (i = 0; i < n; i++)
        p[i] = i;

    // SJF Sorting (Shortest Job First) based on burst time
    // This is a simple bubble sort
    for (i = 0; i < n - 1; i++)
    {
        for (j = i + 1; j < n; j++)
        {
            if (bt[i] > bt[j])  // If current burst time is larger than the next
            {
                // Swap burst times
                temp = bt[i];
                bt[i] = bt[j];
                bt[j] = temp;

                // Swap process numbers so processes stay matched with burst times
                temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
        }
    }

    // Calculate waiting time (time a process waits before execution)
    wt[0] = 0;           // First process starts immediately, so waiting time = 0
    tat[0] = bt[0];      // Turnaround time = burst time for first process

    for (i = 1; i < n; i++)
    {
        wt[i] = wt[i - 1] + bt[i - 1];  // Waiting time = previous process's waiting + burst
        tat[i] = wt[i] + bt[i];         // Turnaround time = waiting time + its own burst time
        wtavg += wt[i];                 // Add waiting time to total for average
        tatavg += tat[i];               // Add turnaround time to total for average
    }

    // Display table headers
    cout << "\nPROCESS\tBURST TIME\tWAITING TIME\tTURNAROUND TIME\n";
    cout << fixed << setprecision(2);  // Format numbers to 2 decimal places

    // Display each process’s burst time, waiting time, and turnaround time
    for (i = 0; i < n; i++)
        cout << "P" << p[i] << "\t"  // Process name
             << bt[i] << "\t\t"     // Burst time
             << wt[i] << "\t\t"     // Waiting time
             << tat[i] << endl;     // Turnaround time

    // Display average waiting time and turnaround time
    cout << "\nAverage Waiting Time = " << wtavg / n;
    cout << "\nAverage Turnaround Time = " << tatavg / n << endl;

    return 0;  // End of program
}
