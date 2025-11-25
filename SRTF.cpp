#include <iostream>
#include <vector>
#include <climits>
using namespace std;

struct Process {
    int pid, at, bt, rt, ct, tat, wt;
};

int main() {
    int n;
    cout << "Enter number of processes: ";
    cin >> n;

    vector<Process> p(n);

    cout << "Enter PID ArrivalTime BurstTime:\n";
    for(int i = 0; i < n; i++){
        cin >> p[i].pid >> p[i].at >> p[i].bt;
        p[i].rt = p[i].bt;   // remaining time initially burst time
    }

    int completed = 0, time = 0, shortest = -1, min_rt = INT_MAX;
    bool found = false;

    while(completed != n){
        shortest = -1;
        min_rt = INT_MAX;

        // find process with shortest remaining time at this clock time
        for(int i = 0; i < n; i++){
            if(p[i].at <= time && p[i].rt > 0 && p[i].rt < min_rt){
                min_rt = p[i].rt;
                shortest = i;
            }
        }

        if(shortest == -1){
            time++;        // no process ready, idle CPU
            continue;
        }

        // execute process for 1 unit time
        p[shortest].rt--;
        time++;

        // if process completed
        if(p[shortest].rt == 0){
            completed++;
            p[shortest].ct = time;
            p[shortest].tat = p[shortest].ct - p[shortest].at;
            p[shortest].wt = p[shortest].tat - p[shortest].bt;
        }
    }

    // output results
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
