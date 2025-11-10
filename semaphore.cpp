#include <iostream>
#include <queue>

using namespace std;

class Semaphore {
public:
    int value;
    queue<int> suspended;  

    Semaphore(int x) {
        value = x;
    }

    void wait(int processID) {
        value--;
        if (value < 0) {
            cout << "Process " << processID << " is suspended." << endl;
            suspended.push(processID);
        } else {
            cout << "Process " << processID << " is executing." << endl;
        }
    }

    void signal() {
        value++;
        if (value <= 0) {
            int pid = suspended.front();
            suspended.pop();
            cout << "Process " << pid << " is resumed." << endl;
        }
    }
};


int main() {
    Semaphore sem(1);  // 1 resource hai ( shared resource ya data 1 hi hai)

    sem.wait(1);  //process 1 resource lene ki koshish karta hai value 1->0
    sem.wait(2); //process 2  resource lene ki koshish karta hai. value 0->-1
    sem.signal(); //-1 -> 0
    sem.signal(); //0 ->1
    sem.wait(2); //1->0
    sem.wait(1); //0->-1

    return 0;
}


// Semaphore ek resource manager hai jo batata hai ki kitne processes ek resource use kar sakte hain.

// Jab resource available nahi, toh process ko wait karwana padta hai (suspend karte hain).

// Jab resource free hota hai, toh wait kar raha process resume hota hai.
