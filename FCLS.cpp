#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Process {
    int id;   // Process ID
    int at;   // Arrival Time
    int bt;   // Burst Time
    int wt;   // Waiting Time
    int tat;  // Turnaround Time
};

int main() {
    int n;
    cout << "Enter number of processes: ";
    cin >> n;

    vector<Process> p(n);

    cout << "Enter ProcessID ArrivalTime BurstTime:\n";
    for (int i = 0; i < n; i++) {
        cin >> p[i].id >> p[i].at >> p[i].bt;
    }

    // Sort by arrival time (ascending) -> FCFS ka base
    sort(p.begin(), p.end(), [](Process a, Process b) {
        return a.at < b.at;
    });

    // Reverse for FCLS (First Come Last Served)
    reverse(p.begin(), p.end());

    int currentTime = 0, totalWT = 0, totalTAT = 0;

    for (int i = 0; i < n; i++) {
        if (currentTime < p[i].at) {
            currentTime = p[i].at; 
        }
        p[i].wt = currentTime - p[i].at;
        p[i].tat = p[i].wt + p[i].bt;
        currentTime += p[i].bt;

        totalWT += p[i].wt;
        totalTAT += p[i].tat;
    }

    cout << "\nProcess\tAT\tBT\tWT\tTAT\n";
    for (int i = 0; i < n; i++) {
        cout << "P" << p[i].id << "\t" 
             << p[i].at << "\t" 
             << p[i].bt << "\t" 
             << p[i].wt << "\t" 
             << p[i].tat << endl;
    }

    cout << "\nAverage Waiting Time = " << (float)totalWT / n;
    cout << "\nAverage Turnaround Time = " << (float)totalTAT / n << endl;

    return 0;
}
