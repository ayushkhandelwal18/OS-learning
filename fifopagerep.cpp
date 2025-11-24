#include <iostream>
#include <queue>
using namespace std;

int pageFaults(int pages[], int n, int capacity) {

    queue<int> q;   // to store pages in order of arrival
    int fault = 0;

    for(int i = 0; i < n; i++){
        int current = pages[i];

        bool found = false;

        
        queue<int> temp = q; // check if already present
        while(!temp.empty()){
            if(temp.front() == current){
                found = true;
                break;
            }
            temp.pop();
        }

        if(!found){
            if(q.size() == capacity){
                q.pop();   // remove oldest page or front
            }
            q.push(current);  // insert new page
            fault++;
        }
    }

    return fault;
}

int main(){
    int pages[] = {1, 3, 0, 3, 5, 6};
    int n = sizeof(pages)/sizeof(pages[0]);
    int capacity = 3;

    cout << "Page Faults (FIFO) = " << pageFaults(pages, n, capacity) << endl;
    return 0;
}