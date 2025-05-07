// 5 bankers Algorithm (safety + bankers)
#include <iostream>
using namespace std;

const int P = 5;
const int R = 3;

void printTable(int processes[], int avail[], int alloc[][R], int max[][R], int need[][R]) {
    cout << "+----+----------+----------+----------+---------+\n";
    cout << "| Ti | Available|Allocation|    Max   |   Need  |\n";
    cout << "+----+----------+----------+----------+---------+\n";

    for (int i = 0; i < P; i++) {
        cout << "| T" << i << " | ";
        if (i == 0)
            cout << avail[0] << " " << avail[1] << " " << avail[2] << "    | ";
        else
            cout << "         | ";

        cout << alloc[i][0] << " " << alloc[i][1] << " " << alloc[i][2] << "    | "
             << max[i][0] << " " << max[i][1] << " " << max[i][2] << "    | "
             << max[i][0] - alloc[i][0] << " " << max[i][1] - alloc[i][1] << " " << max[i][2] - alloc[i][2] << "    |\n";
    }

    cout << "+----+----------+----------+----------+---------+\n";
}

bool isSafeState(int processes[], int avail[], int max[][R], int alloc[][R]) {
    int need[P][R];
    bool finish[P] = {false};
    int work[R];

    for (int i = 0; i < P; i++)
        for (int j = 0; j < R; j++)
            need[i][j] = max[i][j] - alloc[i][j];

    for (int i = 0; i < R; i++)
        work[i] = avail[i];

    cout << "\nInitial State:\n";
    printTable(processes, avail, alloc, max, need);

    int safeSequence[P];
    int count = 0;

    while (count < P) {
        bool found = false;
        for (int i = 0; i < P; i++) {
            if (!finish[i]) {
                bool canExecute = true;
                for (int j = 0; j < R; j++) {
                    if (max[i][j] - alloc[i][j] > work[j]) {
                        canExecute = false;
                        break;
                    }
                }

                if (canExecute) {
                    cout << "Executing Process T" << i << "...\n";

                    for (int j = 0; j < R; j++)
                        work[j] += alloc[i][j];

                    safeSequence[count++] = i;
                    finish[i] = true;
                    cout << "Updated Available: " << work[0] << " " << work[1] << " " << work[2] << "\n";

                    found = true;
                }
            }
        }

        if (!found) {
            cout << "System is in an unsafe state!" << endl;
            return false;
        }
    }

    cout << "\nSystem is in a safe state.\nSafe sequence: ";
    for (int i = 0; i < P; i++)
        cout << "T" << safeSequence[i] << " ";
    cout << endl;
    return true;
}

bool requestResources(int processID, int request[], int avail[], int alloc[][R], int max[][R]) {
    int need[P][R];
    for (int i = 0; i < P; i++)
        for (int j = 0; j < R; j++)
            need[i][j] = max[i][j] - alloc[i][j];

    for (int j = 0; j < R; j++) {
        if (request[j] > need[processID][j]) {
            cout << "Error: Process T" << processID << " requested more than its need.\n";
            return false;
        }
    }

    for (int j = 0; j < R; j++) {
        if (request[j] > avail[j]) {
            cout << "Process T" << processID << " must wait. Requested resources are not available.\n";
            return false;
        }
    }

    for (int j = 0; j < R; j++) {
        avail[j] -= request[j];
        alloc[processID][j] += request[j];
        need[processID][j] -= request[j];
    }

    cout << "\nAfter granting request from T" << processID << ":\n";
    int processes[P] = {0, 1, 2, 3, 4};
    printTable(processes, avail, alloc, max, need);

    if (isSafeState(processes, avail, max, alloc)) {
        cout << "Request granted to T" << processID << ".\n";
        return true;
    } else {
        for (int j = 0; j < R; j++) {
            avail[j] += request[j];
            alloc[processID][j] -= request[j];
        }
        cout << "Request denied. System would enter an unsafe state.\n";
        return false;
    }
}

int main() {
    int processes[P] = {0, 1, 2, 3, 4};

    int available[R];
    cout << "Enter Available Resources (R1 R2 R3): ";
    for (int i = 0; i < R; i++)
        cin >> available[i];

    int max[P][R], allocation[P][R];

    cout << "Enter Max Matrix (" << P << "x" << R << "):\n";
    for (int i = 0; i < P; i++) {
        cout << "Max for P" << i << ": ";
        for (int j = 0; j < R; j++)
            cin >> max[i][j];
    }

    cout << "Enter Allocation Matrix (" << P << "x" << R << "):\n";
    for (int i = 0; i < P; i++) {
        cout << "Allocated to P" << i << ": ";
        for (int j = 0; j < R; j++)
            cin >> allocation[i][j];
    }

    int pid;
    int request[R];
    cout << "Enter Process ID making request (0 to " << P - 1 << "): ";
    cin >> pid;

    cout << "Enter Request Vector (R1 R2 R3): ";
    for (int i = 0; i < R; i++)
        cin >> request[i];
    
    isSafeState(processes, available, max, allocation);

    requestResources(pid, request, available, allocation, max);

    return 0;
}
