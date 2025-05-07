// 6 Deadlock Detection
#include <iostream>
using namespace std;

#define P 5
#define R 3

void printTable(int processes[], int avail[], int alloc[][R], int request[][R]) {
    cout << "\nProcess\tAllocation\tRequest\t\tAvailable\n";
    for (int i = 0; i < P; i++) {
        cout << "T" << i << "\t";
        for (int j = 0; j < R; j++) cout << alloc[i][j] << " ";
        cout << "\t\t";
        for (int j = 0; j < R; j++) cout << request[i][j] << " ";
        if (i == 0) {
            cout << "\t\t";
            for (int j = 0; j < R; j++) cout << avail[j] << " ";
        }
        cout << "\n";
    }
}

bool isSafeState(int processes[], int avail[], int request[][R], int alloc[][R]) {
    bool finish[P] = {false};
    int work[R];

    for (int i = 0; i < R; i++)
        work[i] = avail[i];

    cout << "\nInitial State:\n";
    printTable(processes, avail, alloc, request);

    int safeSequence[P];
    int count = 0;

    while (count < P) {
        bool found = false;
        for (int i = 0; i < P; i++) {
            if (!finish[i]) {
                bool canExecute = true;
                for (int j = 0; j < R; j++) {
                    if (request[i][j] > work[j]) {
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

                    cout << "Updated Available: ";
                    for (int j = 0; j < R; j++)
                        cout << work[j] << " ";
                    cout << "\n";

                    found = true;
                    break;
                }
            }
        }

        if (!found) {
            return false;
        }
    }

    cout << "\nSafe Sequence: ";
    for (int i = 0; i < P; i++)
        cout << "T" << safeSequence[i] << (i == P - 1 ? "" : " -> ");
    cout << "\n";

    return true;
}

int main() {
    int processes[P] = {0, 1, 2, 3, 4};
    int allocation[P][R], request[P][R], available[R];

    cout << "Enter Available Resources (A B C): ";
    for (int i = 0; i < R; i++)
        cin >> available[i];

    cout << "\nEnter Allocation Matrix (P x R):\n";
    for (int i = 0; i < P; i++) {
        cout << "Allocation for T" << i << ": ";
        for (int j = 0; j < R; j++)
            cin >> allocation[i][j];
    }

    cout << "\nEnter Request Matrix (P x R):\n";
    for (int i = 0; i < P; i++) {
        cout << "Request for T" << i << ": ";
        for (int j = 0; j < R; j++)
            cin >> request[i][j];
    }

    if (isSafeState(processes, available, request, allocation))
        cout << "\nNo deadlock detected. System is in a safe state.\n";
    else
        cout << "\nDeadlock detected!\n";

    return 0;
}

