#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
//These only work on Linux/Mac or WSL (Linux subsystem for Windows).
using namespace std;

int main() {
    pid_t p = fork(); 
    if (p < 0) {
        cout<< "Fork failed" << endl;
        return 1;
    }
    else if (p == 0) {
        
        cout << "Hello world from Child process" << endl;
        cout << "Child PID: " << getpid() << ", Parent PID: " << getppid() << endl;
    }
    else {
       
        cout << "Hello world from Parent process" << endl;
        wait(NULL);
        cout << "Parent PID: " << getpid() << ", Child PID: " << p << endl;
        
    }

    return 0;
}