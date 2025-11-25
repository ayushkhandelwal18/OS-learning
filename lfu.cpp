#include <iostream>
#include <vector>
using namespace std;

int pageFaultsLFU(int pages[], int n, int capacity) {

    vector<int> frame;        // store pages
    vector<int> freq;         // frequency count
    vector<int> arrival;      // arrival order timestamp

    int faults = 0;
    int time = 0;             // arrival counter

    for(int i = 0; i < n; i++){
        time++;
        int current = pages[i];
        bool found = false;
        int index = -1;

        // check if already in frame
        for(int j = 0; j < frame.size(); j++){
            if(frame[j] == current){
                found = true;
                index = j;
                break;
            }
        }

        if(found){
            freq[index]++;            // update frequency
        }
        else {
            // page fault
            if(frame.size() < capacity){
                frame.push_back(current);
                freq.push_back(1);
                arrival.push_back(time);
            }
            else {
                // find LFU + earliest arrival tie breaking
                int lfu_index = 0;
                for(int j = 1; j < frame.size(); j++){
                    if(freq[j] < freq[lfu_index] ||
                      (freq[j] == freq[lfu_index] && arrival[j] < arrival[lfu_index])) {

                        lfu_index = j;
                    }
                }

                // replace
                frame[lfu_index] = current;
                freq[lfu_index] = 1;
                arrival[lfu_index] = time;
            }

            faults++;
        }
    }

    return faults;
}

int main() {

    int pages[] =  { 1, 2, 3, 4, 2, 1, 5 };
    int n = sizeof(pages)/sizeof(pages[0]);
    int capacity = 3;

    cout << "Page Faults (LFU) = " << pageFaultsLFU(pages, n, capacity) << endl;
    return 0;
}
