#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Process {
    int pid, at, bt, ct, tat, wt;
};

int main() {
    int n;
    cout << "Enter number of processes: ";
    cin >> n;

    vector<Process> p(n), done(n, {0});

    cout << "Enter PID ArrivalTime BurstTime:\n";
    for(int i = 0; i < n; i++){
        cin >> p[i].pid >> p[i].at >> p[i].bt;
    }

    int completed = 0, time = 0;

    while(completed != n){
        int idx = -1;
        int max_bt = -1;

        // Find process with largest BT among available ones
        for(int i = 0; i < n; i++){
            if(p[i].at <= time && done[i].pid != 1 && p[i].bt > max_bt){
                max_bt = p[i].bt;
                idx = i;
            }
        }

        if(idx == -1){
            time++;   // idle CPU
            continue;
        }

        // Complete selected process
        time += p[idx].bt;
        p[idx].ct = time;
        p[idx].tat = p[idx].ct - p[idx].at;
        p[idx].wt = p[idx].tat - p[idx].bt;

        done[idx].pid = 1;
        completed++;
    }

    cout << "\nPID\tAT\tBT\tCT\tTAT\tWT\n";
    float totalWT = 0, totalTAT = 0;

    for(int i = 0; i < n; i++){
        cout << "P" << p[i].pid << "\t"
             << p[i].at << "\t"
             << p[i].bt << "\t"
             << p[i].ct << "\t"
             << p[i].tat << "\t"
             << p[i].wt << endl;

        totalWT += p[i].wt;
        totalTAT += p[i].tat;
    }

    cout << "\nAverage Waiting Time = " << totalWT / n;
    cout << "\nAverage Turnaround Time = " << totalTAT / n << endl;

    return 0;
}
