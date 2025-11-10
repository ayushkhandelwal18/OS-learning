#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

struct Process {
    int pid, arrival, burst, remaining, completion, turnaround, waiting;
};

int main() {
    int n, tq;
    cout << "Enter number of processes: ";
    cin >> n;

    vector<Process> p(n);

    for (int i = 0; i < n; i++) {
        cout << "\nProcess " << i + 1 << " Arrival Time: ";
        cin >> p[i].arrival;
        cout << "Burst Time: ";
        cin >> p[i].burst;
        p[i].pid = i + 1;
        p[i].remaining = p[i].burst;
    }

    cout << "\nEnter Time Quantum: ";
    cin >> tq;

    // Sort by arrival time
    sort(p.begin(), p.end(), [](const Process &a, const Process &b) {
        return a.arrival < b.arrival;
    });

    queue<int> q;
    int time = p[0].arrival;
    int completed = 0;
    vector<bool> inQueue(n, false);

    // Initial enqueue: processes that have already arrived at start time
    for (int i = 0; i < n; i++) {
        if (p[i].arrival <= time && p[i].remaining > 0) {
            q.push(i);
            inQueue[i] = true;
        }
    }

    while (completed < n) {
        if (q.empty()) {
            // No ready process, advance time to next available process
            int nextArrival = INT32_MAX;
            for (int i = 0; i < n; i++) {
                if (p[i].remaining > 0 && p[i].arrival < nextArrival) {
                    nextArrival = p[i].arrival;
                }
            }
            time = max(time, nextArrival);

            for (int i = 0; i < n; i++) {
                if (p[i].arrival <= time && p[i].remaining > 0 && !inQueue[i]) {
                    q.push(i);
                    inQueue[i] = true;
                }
            }
            continue;
        }

        int idx = q.front();
        q.pop();
        inQueue[idx] = false;

        int exec = min(tq, p[idx].remaining);
        int startTime = time;
        time = max(time, p[idx].arrival) + exec;
        p[idx].remaining -= exec;

        // Enqueue new arrivals during execution slice
        for (int i = 0; i < n; i++) {
            if (p[i].arrival > startTime && p[i].arrival <= time &&
                p[i].remaining > 0 && !inQueue[i]) {
                q.push(i);
                inQueue[i] = true;
            }
        }

        if (p[idx].remaining > 0) {
            q.push(idx);
            inQueue[idx] = true;
        } else {
            p[idx].completion = time;
            completed++;
        }
    }

    cout << "\nPID\tAT\tBT\tCT\tTAT\tWT\n";
    float totalTAT = 0, totalWT = 0;

    for (auto &x : p) {
        x.turnaround = x.completion - x.arrival;
        x.waiting = x.turnaround - x.burst;
        totalTAT += x.turnaround;
        totalWT += x.waiting;
        cout << x.pid << "\t" << x.arrival << "\t" << x.burst << "\t"
             << x.completion << "\t" << x.turnaround << "\t" << x.waiting << "\n";
    }

    cout << "\nAverage Turnaround Time: " << totalTAT / n;
    cout << "\nAverage Waiting Time: " << totalWT / n << "\n";

    return 0;
}
