// 7 Memory Allocation
#include <iostream>
using namespace std;

void firstFit(int blockSize[], int m, int processSize[], int n) {
    int allocation[n];
    fill_n(allocation, n, -1);
    
    bool allocatedBlocks[m] = {false};
    
    cout << "First Fit Allocation:\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (!allocatedBlocks[j] && blockSize[j] >= processSize[i]) {
                allocation[i] = j;
                allocatedBlocks[j] = true; 
                break;
            }
        }
        cout << "Process " << i + 1 << " (Size: " << processSize[i] << ") -> Block " 
             << (allocation[i] != -1 ? to_string(allocation[i] + 1) + " (Size: " + to_string(blockSize[allocation[i]]) + ")" : "Not Allocated") << endl;
    }
}

void bestFit(int blockSize[], int m, int processSize[], int n) {
    int allocation[n];
    fill_n(allocation, n, -1);
    
    bool allocatedBlocks[m] = {false};
    
    cout << "Best Fit Allocation:\n";
    for (int i = 0; i < n; i++) {
        int bestIdx = -1;
        for (int j = 0; j < m; j++) {
            if (!allocatedBlocks[j] && blockSize[j] >= processSize[i]) {
                if (bestIdx == -1 || blockSize[j] < blockSize[bestIdx]) {
                    bestIdx = j;
                }
            }
        }
        if (bestIdx != -1) {
            allocation[i] = bestIdx;
            allocatedBlocks[bestIdx] = true;
        }
        cout << "Process " << i + 1 << " (Size: " << processSize[i] << ") -> Block " 
             << (allocation[i] != -1 ? to_string(allocation[i] + 1) + " (Size: " + to_string(blockSize[allocation[i]]) + ")" : "Not Allocated") << endl;
    }
}

void worstFit(int blockSize[], int m, int processSize[], int n) {
    int allocation[n];
    fill_n(allocation, n, -1);
    
    bool allocatedBlocks[m] = {false};
    
    cout << "Worst Fit Allocation:\n";
    for (int i = 0; i < n; i++) {
        int worstIdx = -1;
        for (int j = 0; j < m; j++) {
            if (!allocatedBlocks[j] && blockSize[j] >= processSize[i]) {
                if (worstIdx == -1 || blockSize[j] > blockSize[worstIdx]) {
                    worstIdx = j;
                }
            }
        }
        if (worstIdx != -1) {
            allocation[i] = worstIdx;
            allocatedBlocks[worstIdx] = true;
        }
        cout << "Process " << i + 1 << " (Size: " << processSize[i] << ") -> Block " 
             << (allocation[i] != -1 ? to_string(allocation[i] + 1) + " (Size: " + to_string(blockSize[allocation[i]]) + ")" : "Not Allocated") << endl;
    }
}

void nextFit(int blockSize[], int m, int processSize[], int n) {
    int allocation[n];
    fill_n(allocation, n, -1);
    int lastAllocated = 0;
    
    bool allocatedBlocks[m] = {false};
    
    cout << "Next Fit Allocation:\n";
    for (int i = 0; i < n; i++) {
        int j = lastAllocated;   
        while (j < m) {
            if (!allocatedBlocks[j] && blockSize[j] >= processSize[i]) {
                allocation[i] = j;
                allocatedBlocks[j] = true;
                lastAllocated = j;
                break;
            }
            j++;
        }
        cout << "Process " << i + 1 << " (Size: " << processSize[i] << ") -> Block " 
             << (allocation[i] != -1 ? to_string(allocation[i] + 1) + " (Size: " + to_string(blockSize[allocation[i]]) + ")" : "Not Allocated") << endl;
    }
}

int main() {
    int m, n;
    cout << "Enter number of memory blocks: ";
    cin >> m;
    int blockSize[m];
    cout << "Enter sizes of memory blocks: ";
    for (int i = 0; i < m; i++) {
        cin >> blockSize[i];
    }
    
    cout << "Enter number of processes: ";
    cin >> n;
    int processSize[n];
    cout << "Enter sizes of processes: ";
    for (int i = 0; i < n; i++) {
        cin >> processSize[i];
    }
    
    int choice;
    
    do {
        cout << "\nChoose Allocation Strategy:\n";
        cout << "1. First Fit\n";
        cout << "2. Best Fit\n";
        cout << "3. Worst Fit\n";
        cout << "4. Next Fit\n";
        cout << "5. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;
        
        switch (choice) {
            case 1: firstFit(blockSize, m, processSize, n); break;
            case 2: bestFit(blockSize, m, processSize, n); break;
            case 3: worstFit(blockSize, m, processSize, n); break;
            case 4: nextFit(blockSize, m, processSize, n); break;
            case 5: cout << "Exiting...\n"; break;
            default: cout << "Invalid choice, please enter again.\n";
        }
        
    } while (choice != 5);
    
    return 0;
}

