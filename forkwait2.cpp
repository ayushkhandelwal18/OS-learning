#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
//These only work on Linux/Mac or WSL (Linux subsystem for Windows).
using namespace std;

int main() {
    pid_t p = fork(); 

    if (p == 0) {
        
        cout << "Child created and ";
        cout << "My PID: " << getpid();
        cout << " and My Parent PID: " << getppid() << endl;


    }
    else if (p < 0) {
        
        cout<< "Fork failed" << endl;
    }
    else {
         wait(NULL);
        cout << "I am the parent and ";
        cout<<"hello from parent " <<endl;
        cout << "My PID: " << getpid() << endl;
       
      
    
    }

    return 0;
}