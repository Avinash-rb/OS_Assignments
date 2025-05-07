//5 Safety Algorithm
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
             << need[i][0] << " " << need[i][1] << " " << need[i][2] << "    |\n";
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
                    if (need[i][j] > work[j]) {
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

int main() {
    int processes[P] = {0, 1, 2, 3, 4};

    int available[R];
    int max[P][R];
    int allocation[P][R];

    cout << "Enter Available Resources (A B C): ";
    for (int i = 0; i < R; i++)
        cin >> available[i];

    cout << "\nEnter Allocation Matrix (P x R):\n";
    for (int i = 0; i < P; i++) {
        cout << "Allocation for T" << i << ": ";
        for (int j = 0; j < R; j++)
            cin >> allocation[i][j];
    }

    cout << "\nEnter Max Matrix (P x R):\n";
    for (int i = 0; i < P; i++) {
        cout << "Max for T" << i << ": ";
        for (int j = 0; j < R; j++)
            cin >> max[i][j];
    }

    cout << "\nChecking system state:\n";
    isSafeState(processes, available, max, allocation);

    return 0;
}
