#include <iostream> // Include input/output stream library
#include <iomanip> // Include library for output formatting
#include <queue> // Include queue data structure library
using namespace std; // Use standard namespace

int main() { // Main function entry point
    int n = 5; // Number of processes
    double burstTime[] = {50.54, 10.11, 33.34, 2.5, 101.1}; // Array of burst times for each process
    double timeQuantum = 20; // Time slice for round robin scheduling
    
    double waitingTime[5] = {0}; // Array to store waiting time for each process
    double turnaroundTime[5] = {0}; // Array to store turnaround time for each process
    queue<int> q; // Queue to hold process indices
    double currentTime = 0; // Track current CPU time
    
    // Initialize queue with process indices
    for (int i = 0; i < n; i++) { // Loop through each process
        q.push(i); // Add process index to queue
    }
    
    double remainingBurst[5]; // Array to track remaining burst time for each process
    for (int i = 0; i < n; i++) { // Loop through each process
        remainingBurst[i] = burstTime[i]; // Initialize remaining burst time with original burst time
    }
    
    // Round Robin Scheduling 
    while (!q.empty()) { // Continue while queue is not empty
        int process = q.front(); // Get front process from queue
        q.pop(); // Remove front process from queue
        
        if (remainingBurst[process] > timeQuantum) { // If remaining time exceeds time quantum
            currentTime += timeQuantum; // Add time quantum to current time
            remainingBurst[process] -= timeQuantum; // Reduce remaining burst time by time quantum
            q.push(process); // Re-add process to back of queue
        } else { // If remaining time is within time quantum
            currentTime += remainingBurst[process]; // Add remaining burst time to current time
            turnaroundTime[process] = currentTime; // Record turnaround time as current time
            waitingTime[process] = turnaroundTime[process] - burstTime[process]; // Calculate waiting time
            remainingBurst[process] = 0; // Mark process as complete
        }
    }
    
    // Display Results
    cout << "\n===== ROUND ROBIN SCHEDULING =====" << endl; // Print header
    cout << "Time Quantum: " << timeQuantum << endl << endl; // Print time quantum value
    
    cout << left << setw(12) << "Process" // Print "Process" column header, left-aligned, width 12
         << left << setw(15) << "Burst Time" // Print "Burst Time" column header, left-aligned, width 15
         << left << setw(18) << "Turnaround Time" // Print "Turnaround Time" column header, left-aligned, width 18
         << left << setw(15) << "Waiting Time" << endl; // Print "Waiting Time" column header, left-aligned, width 15
    cout << "================================================" << endl; // Print separator line
    
    double totalWaiting = 0, totalTurnaround = 0; // Initialize totals for averages
    for (int i = 0; i < n; i++) { // Loop through each process
        cout << left << setw(12) << "P" + to_string(i + 1) // Print process name (P1, P2, etc.)
             << left << setw(15) << fixed << setprecision(2) << burstTime[i] // Print burst time with 2 decimals
             << left << setw(18) << fixed << setprecision(2) << turnaroundTime[i] // Print turnaround time with 2 decimals
             << left << setw(15) << fixed << setprecision(2) << waitingTime[i] << endl; // Print waiting time with 2 decimals
        
        totalWaiting += waitingTime[i]; // Add to total waiting time
        totalTurnaround += turnaroundTime[i]; // Add to total turnaround time
    }
    
    cout << "================================================" << endl; // Print separator line
    cout << "\nAverage Waiting Time: " << fixed << setprecision(2) << totalWaiting / n << endl; // Print average waiting time
    cout << "Average Turnaround Time: " << fixed << setprecision(2) << totalTurnaround / n << endl; // Print average turnaround time
    
    return 0; // Exit program
}

