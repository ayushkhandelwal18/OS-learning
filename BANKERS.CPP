#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n, m;      // processes & resources

    cout << "Enter number of processes: ";
    cin >> n;
    cout << "Enter number of resources: ";
    cin >> m;

    vector<vector<int>> alloc(n, vector<int>(m));
    vector<vector<int>> maxNeed(n, vector<int>(m));
    vector<vector<int>> need(n, vector<int>(m));
    vector<int> total(m), avail(m);

    cout << "\nEnter Allocation Matrix:\n";
    for(int i = 0; i < n; i++)
        for(int j = 0; j < m; j++)
            cin >> alloc[i][j];

    cout << "\nEnter Maximum Requirement Matrix:\n";
    for(int i = 0; i < n; i++)
        for(int j = 0; j < m; j++)
            cin >> maxNeed[i][j];

    cout << "\nEnter Total Resources (A B C ...): ";
    for(int j = 0; j < m; j++)
        cin >> total[j];

    // Calculate allocated total for each resource
    vector<int> allocated(m, 0);
    for(int j = 0; j < m; j++)
        for(int i = 0; i < n; i++)
            allocated[j] += alloc[i][j];

    // Calculate available = total - allocated
    for(int j = 0; j < m; j++)
        avail[j] = total[j] - allocated[j];

    // NEED matrix = MAX - ALLOCATION
    for(int i = 0; i < n; i++)
        for(int j = 0; j < m; j++)
            need[i][j] = maxNeed[i][j] - alloc[i][j];

    vector<int> finish(n, 0), safeSeq(n);
    int count = 0, index = 0, i = 0;

    // Sequential circular check
    while(count < n) {
        bool allocatedFlag = false;

        if(finish[i] == 0) {
            bool canRun = true;

            for(int j = 0; j < m; j++) {
                if(need[i][j] > avail[j]) {
                    canRun = false;
                    break;
                }
            }

            if(canRun) {
                for(int j = 0; j < m; j++)
                    avail[j] += alloc[i][j];

                safeSeq[index++] = i;
                finish[i] = 1;
                count++;
                allocatedFlag = true;
            }
        }

        i = (i + 1) % n;

        if(i == 0 && !allocatedFlag) {
            cout << "\nSystem is NOT SAFE (deadlock may occur)" << endl;
            return 0;
        }
    }

    cout << "\nSystem is SAFE.\nSafe Sequence: ";
    for(int k = 0; k < n; k++)
        cout << "P" << safeSeq[k]+1 << " ";
    cout << endl;

    return 0;
}
