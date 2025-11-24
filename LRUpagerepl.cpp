#include<iostream>
#include<vector>
using namespace std;

int pageFaults(int pages[] , int n , int capacity){

    vector<int> frame;   // to store pages currently in memory
    
    int fault = 0;       // page fault counter

    for(int i = 0; i < n; i++){
        int x=frame.size();
        int current = pages[i];

        //Check kro current page already frame me hai ya nhi 
        bool found = false;
        for(int p : frame){
            if(p == current){
                found = true;
                break;
            }
        }

        
        if(!found){

          
            if(x< capacity){ //frame me space hai to directly push krdo
                frame.push_back(current);  
            }
            else{ // main logic -- frame full hai to 
              

                int lru_index = -1; // least recenlty nikalne ke liye 
                int farthest = i;    // comparison ke liye current wala 

                
                for(int j = 0; j < x; j++){
                    int k;

                    
                    for(k = i - 1; k >= 0; k--){ //backwar search 
                        if(frame[j] == pages[k]) 
                            break;   // found previous usage at index k
                    }

                    // If this page was used earlier than others, mark it as LRU
                    if(k < farthest){   // smallest k = oldest usage
                        farthest = k;
                        lru_index = j;
                    }
                }

                
                frame.erase(frame.begin() + lru_index);// remove least recenlty 

               
                frame.push_back(current);
            }

            
            fault++;
        }
    }

    return fault;
}

int main(){
    int pages[] = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2};
    int n = sizeof(pages)/sizeof(pages[0]);
    int capacity = 4;

    cout << "Page Faults = " << pageFaults(pages, n, capacity);
    cout<<endl;
    return 0;
}