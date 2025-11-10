// higher number = higher priority

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Process {
    int pid, arrival, burst, priority;
    int remaining, completion, turnaround, waiting;
};

int main() {
    int n;
    cout << "Enter number of processes: ";
    cin >> n;

    vector<Process> p(n);
    for (int i = 0; i < n; i++) {
        cout << "\nProcess " << i + 1 << " Arrival Time: ";
        cin >> p[i].arrival;
        cout << "Burst Time: ";
        cin >> p[i].burst;
        cout << "Priority (higher number = higher priority): ";
        cin >> p[i].priority;

        p[i].pid = i + 1;
        p[i].remaining = p[i].burst;
        p[i].completion = 0;
    }

    int completed = 0, time = 0;
    vector<int> isCompleted(n, 0);

    // Sort by arrival time initially
    sort(p.begin(), p.end(), [](const Process &a, const Process &b) {
        return a.arrival < b.arrival;
    });

    cout << "\n--- Executing Preemptive Priority Scheduling ---\n";

    while (completed < n) {
        int idx = -1;
        int maxPriority = -1e9; // lower limit since higher number = higher priority

        for (int i = 0; i < n; i++) {
            if (p[i].arrival <= time && p[i].remaining > 0) {
                if (p[i].priority > maxPriority) {  // changed from < to >
                    maxPriority = p[i].priority;
                    idx = i;
                } else if (p[i].priority == maxPriority) {
                    if (p[i].arrival < p[idx].arrival)
                        idx = i;
                }
            }
        }

        if (idx != -1) {
            p[idx].remaining--;
            time++;

            if (p[idx].remaining == 0) {
                p[idx].completion = time;
                p[idx].turnaround = p[idx].completion - p[idx].arrival;
                p[idx].waiting = p[idx].turnaround - p[idx].burst;
                isCompleted[idx] = 1;
                completed++;
            }
        } else {
            time++; // CPU idle
        }
    }

    cout << "\nPID\tAT\tBT\tPR\tCT\tTAT\tWT\n";
    float totalTAT = 0, totalWT = 0;

    for (auto &x : p) {
        totalTAT += x.turnaround;
        totalWT += x.waiting;
        cout << x.pid << "\t" << x.arrival << "\t" << x.burst << "\t"
             << x.priority << "\t" << x.completion << "\t"
             << x.turnaround << "\t" << x.waiting << "\n";
    }

    cout << "\nAverage Turnaround Time: " << totalTAT / n;
    cout << "\nAverage Waiting Time: " << totalWT / n << "\n";

    return 0;
}
