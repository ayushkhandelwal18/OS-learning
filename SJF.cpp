//implementing SJF non preemptive 

#include<iostream>
using namespace std;
#include<vector>
#include<climits>


int main(){
    int np;
    cout << "Enter number of processes: ";
    cin >> np;

    vector<int> pid(np);
    vector<int> at(np);
    vector<int> bt(np);
    vector<int> ct(np, 0);
    vector<int> tat(np, 0);
    vector<int> wt(np, 0);
    vector<bool> done(np, false);

    for (int i = 0; i < np; i++) {
        pid[i] = i + 1;
        cout << "enter arrival and burst time for process " << i+1<< ": ";
        cin >> at[i] >> bt[i];
    }

    int completedprocess=0;
    int presenttime=0;
 
    cout << "pid\t at\t bt\t ct\t tat\t wt\n";

    while(completedprocess < np){

        int idx=-1;
        int minimumBT =INT_MAX;

        for(int i=0 ;i<np ;i++){
            if( !done[i] &&  at[i]<=presenttime && bt[i]<minimumBT){
                minimumBT=bt[i];
                idx =i;
            }
        }

        if(idx != -1){
            presenttime = presenttime + bt[idx];
            ct[idx] = presenttime;
            tat[idx]= ct[idx]-at[idx];
            wt[idx]=tat[idx]-bt[idx];
            done[idx]=true;
            completedprocess++;

        }
        else{
            presenttime++;
        }

        //jo process phle ho rhi hai us according print krna
        cout << pid[idx] << "\t" << at[idx] << "\t" << bt[idx] << "\t" << ct[idx] << "\t" << tat[idx] << "\t" << wt[idx] << endl;

      }
     
      // ye p1-p2-p3--- wale format me print krna
    //      cout << "pid\t at\t bt\t ct\t tat\t wt\n";
    //      for (int i = 0; i < np; i++) {
    //     cout << pid[i] << "\t" << at[i] << "\t" << bt[i] << "\t" << ct[i] << "\t" << tat[i] << "\t" << wt[i] << endl;
    // }

       
    double totalTAT = 0, totalWT = 0;
    for (int i = 0; i < np; i++) {
        totalTAT += tat[i];
        totalWT += wt[i];
    }

    cout << "\nAverage Turnaround Time: " << totalTAT / np;
    cout << "\nAverage Waiting Time: " << totalWT / np << endl;

    return 0;





  




}