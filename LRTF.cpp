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
        p[i].rt = p[i].bt;   
    }

    int completed = 0, time = 0, longest = -1, max_rt = -1;

    while(completed != n){
        longest = -1;
        max_rt = -1;

        // find process with longest remaining time
        for(int i = 0; i < n; i++){
            if(p[i].at <= time && p[i].rt > 0 && p[i].rt > max_rt){
                max_rt = p[i].rt;
                longest = i;
            }
        }

        if(longest == -1){
            time++;
            continue;
        }

        p[longest].rt--;
        time++;

        if(p[longest].rt == 0){
            completed++;
            p[longest].ct = time;
            p[longest].tat = p[longest].ct - p[longest].at;
            p[longest].wt = p[longest].tat - p[longest].bt;
        }
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
