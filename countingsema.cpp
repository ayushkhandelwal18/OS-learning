#include<iostream>
#include<queue>
using namespace std;

class countingsemaphore {
public:
    queue<int> suspendedProcess;
    int val;

    countingsemaphore(int x) {
        val = x;  
        cout << "shared resource : " << x << endl;
    }

    void wait(int pid){
        val--;
        cout << "After wait, val = " << val << endl;
        if(val < 0){
            cout << "Process " << pid << " is suspended" << endl;
            suspendedProcess.push(pid);
        }
        else{
            cout << "Process " << pid << " is running" << endl;
        }
    }

void signal(){
        val++;
        cout << "After signal, val = " << val << endl;
        if(val <= 0 && !suspendedProcess.empty()){
            int pid = suspendedProcess.front();
            suspendedProcess.pop();
            cout << "Process " << pid << " is resumed" << endl;
        }
        else if(val > 0){
            cout << "Resource is free" << endl;
        }
    }
};



int main(){
    countingsemaphore s(2);  // 2 resources

    s.wait(1);  // val 2->1, process1 running
    s.wait(2);  // val 1->0, process2 running
    s.wait(3);  // val 0->-1, process3 suspended
    s.signal(); // val -1->0, process3 resumed
    s.signal(); // val 0->1 (resource free)
    s.wait(4);  // val 1->0, process4 running
    s.wait(5);  // val 0->-1, process5 suspended

    return 0;
}