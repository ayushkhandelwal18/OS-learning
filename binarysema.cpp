#include<iostream>
#include<queue>
using namespace std;

class binarysemaphonre{
public:

queue<int>suspendedProcess;

int val;

binarysemaphonre(int x){
    val=x;
    cout<<"shared resource : " <<x <<endl;

}

void wait(int pid){
    val--;
    cout << "After wait, val = " << val << endl;
    if(val<0){
        cout<<"Process" <<pid <<"is suspended" <<endl;
        suspendedProcess.push(pid);
  }
  else{
   cout<<"Process" <<pid <<"is running" <<endl;
  }

}

void signal(){
    val++;
    cout << "After signal, val = " << val << endl;
    if(val <= 0){
        if(!suspendedProcess.empty()) {
            int pid = suspendedProcess.front();
            suspendedProcess.pop();
            cout << "Process " << pid << " is resumed" << endl;
        }
    }
    else {
        cout << "Resource is free" << endl;
    }
}

};


int main(){
    binarysemaphonre s(1); //// 1 resource hai ( shared resource ya data 1 hi hai)
    s.wait(1); //process1 resource lene ki koshish karta hai value 1->0
    s.wait(2); //process 2  resource lene ki koshish karta hai. value 0->-1
    s.signal(); //-1 -> 0 // process resume
    s.signal();  //0 ->1 //resource free
    s.wait(2); //1->0
    s.wait(1);  //0->-1
  

    return 0;
}