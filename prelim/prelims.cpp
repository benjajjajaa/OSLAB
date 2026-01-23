#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <iomanip>

using namespace std;

struct process {
    int pid;
    int at;
    int bt;
    int rt;
    int ct;
    int tt;
    int wt;
};

/* ---------- Time Quantum Calculation ---------- */

int calculateMedianQuantum(vector<process> p) {
    vector<int> bt;

    cout << "\n--------------------------------------------\n";
    cout << "TIME QUANTUM CALCULATION (MEDIAN METHOD)\n";
    cout << "--------------------------------------------\n";

    cout << "Burst Times: ";
    for (auto &x : p) {
        bt.push_back(x.bt);
        cout << x.bt << " ";
    }

    sort(bt.begin(), bt.end());

    cout << "\nSorted Burst Times: ";
    for (int x : bt)
        cout << x << " ";

    int n = bt.size();
    int quantum;

    if (n % 2 == 0) {
        quantum = (bt[n / 2 - 1] + bt[n / 2]) / 2;
        cout << "\nMedian = (" << bt[n / 2 - 1]
             << " + " << bt[n / 2] << ") / 2";
    } else {
        quantum = bt[n / 2];
        cout << "\nMedian = " << quantum;
    }

    cout << "\nCalculated Time Quantum = " << quantum << endl;
    cout << "--------------------------------------------\n";

    return quantum;
}

/* ---------- Table Printing ---------- */

void printTable(string title, vector<process> p) {
    double avgTT = 0, avgWT = 0;

    cout << "\n============================================================\n";
    cout << title << endl;
    cout << "------------------------------------------------------------\n";
    cout << left
         << setw(6) << "PID"
         << setw(6) << "AT"
         << setw(6) << "BT"
         << setw(12) << "CT"
         << setw(6) << "TT"
         << setw(6) << "WT" << endl;
    cout << "------------------------------------------------------------\n";

    for (auto &x : p) {
        cout << left
             << setw(6) << x.pid
             << setw(6) << x.at
             << setw(6) << x.bt
             << setw(12) << x.ct
             << setw(6) << x.tt
             << setw(6) << x.wt << endl;

        avgTT += x.tt;
        avgWT += x.wt;
    }

    cout << "------------------------------------------------------------\n";
    cout << "Average Turnaround Time = " << avgTT / p.size() << endl;
    cout << "Average Waiting Time    = " << avgWT / p.size() << endl;
    cout << "============================================================\n";
}

/* ---------- Round Robin ---------- */

void roundRobin(vector<process> p, int quantum) {
    queue<int> q;
    int time = 0, completed = 0, n = p.size();
    vector<bool> visited(n, false);

    while (completed < n) {
        for (int i = 0; i < n; i++) {
            if (p[i].at <= time && !visited[i] && p[i].rt > 0) {
                q.push(i);
                visited[i] = true;
            }
        }

        if (q.empty()) {
            time++;
            continue;
        }

        int idx = q.front();
        q.pop();

        int exec = min(quantum, p[idx].rt);
        p[idx].rt -= exec;
        time += exec;

        for (int i = 0; i < n; i++) {
            if (p[i].at <= time && !visited[i] && p[i].rt > 0) {
                q.push(i);
                visited[i] = true;
            }
        }

        if (p[idx].rt > 0)
            q.push(idx);
        else {
            p[idx].ct = time;
            p[idx].tt = p[idx].ct - p[idx].at;
            p[idx].wt = p[idx].tt - p[idx].bt;
            completed++;
        }
    }

    printTable("ROUND ROBIN SCHEDULING", p);
}

/* ---------- SJF ---------- */

void sjf(vector<process> p) {
    int time = 0, completed = 0, n = p.size();
    vector<bool> done(n, false);

    while (completed < n) {
        int idx = -1, minBT = 1e9;

        for (int i = 0; i < n; i++) {
            if (p[i].at <= time && !done[i] && p[i].bt < minBT) {
                minBT = p[i].bt;
                idx = i;
            }
        }

        if (idx == -1) {
            time++;
            continue;
        }

        time += p[idx].bt;
        p[idx].ct = time;
        p[idx].tt = p[idx].ct - p[idx].at;
        p[idx].wt = p[idx].tt - p[idx].bt;

        done[idx] = true;
        completed++;
    }

    printTable("SHORTEST JOB FIRST (SJF)", p);
}

/* ---------- SRTF ---------- */

void srtf(vector<process> p) {
    int time = 0, completed = 0, n = p.size();

    while (completed < n) {
        int idx = -1, minRT = 1e9;

        for (int i = 0; i < n; i++) {
            if (p[i].at <= time && p[i].rt > 0 && p[i].rt < minRT) {
                minRT = p[i].rt;
                idx = i;
            }
        }

        if (idx == -1) {
            time++;
            continue;
        }

        p[idx].rt--;
        time++;

        if (p[idx].rt == 0) {
            p[idx].ct = time;
            p[idx].tt = p[idx].ct - p[idx].at;
            p[idx].wt = p[idx].tt - p[idx].bt;
            completed++;
        }
    }

    printTable("SHORTEST REMAINING TIME FIRST (SRTF)", p);
}

/* ---------- MAIN ---------- */

int main() {
    int at[] = {4, 2, 3, 6, 1, 5, 8, 7};
    int bt[] = {53, 43, 18, 16, 44, 73, 99, 27};
    int n = 8;

    vector<process> p(n);

    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;
        p[i].at = at[i];
        p[i].bt = bt[i];
        p[i].rt = bt[i];
    }

    int quantum = calculateMedianQuantum(p);

    roundRobin(p, quantum);
    sjf(p);
    srtf(p);

    return 0;
}
