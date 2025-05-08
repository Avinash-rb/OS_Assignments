//9 Disk Scheduling
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <climits>

using namespace std;

void FCFS(const vector<int>& requests, int head) {
    int total_movement = 0;
    int current_head = head;
    
    cout << "\n[FCFS]\nOrder of execution:\n" << head << " -> ";
    
    for (int request : requests) {
        cout << request << " -> ";
        total_movement += abs(request - current_head);
        current_head = request;
    }
    
    cout << "\nTotal head movement: " << total_movement << endl;
}

void SSTF(const vector<int>& requests, int head) {
    int total_movement = 0;
    int current_head = head;
    vector<bool> visited(requests.size(), false);
    
    cout << "\n[SSTF]\nOrder of execution:\n" << head << " -> ";
    
    for (size_t i = 0; i < requests.size(); i++) {
        int min_distance = INT_MAX;
        int min_index = -1;
        
        for (size_t j = 0; j < requests.size(); j++) {
            if (!visited[j]) {
                int distance = abs(requests[j] - current_head);
                if (distance < min_distance) {
                    min_distance = distance;
                    min_index = j;
                }
            }
        }
        
        if (min_index != -1) {
            visited[min_index] = true;
            total_movement += min_distance;
            current_head = requests[min_index];
            cout << requests[min_index] << " -> ";
        }
    }
    
    cout << "\nTotal head movement: " << total_movement << endl;
}

void SCAN(const vector<int>& requests, int head) {
    vector<int> left;
    vector<int> right;
    int total_movement = 0;
    int current_head = head;
    
    for (int request : requests) {
        if (request < head) {
            left.push_back(request);
        } else {
            right.push_back(request);
        }
    }

    sort(left.begin(), left.end(), greater<int>());
    sort(right.begin(), right.end());
    
    cout << "\n[SCAN]\nHead movement:\n" << head << " -> ";
    
    for (int request : left) {
        total_movement += abs(current_head - request);
        current_head = request;
        cout << current_head << " -> ";
    }
    
    for (int request : right) {
        total_movement += abs(current_head - request);
        current_head = request;
        cout << current_head << " -> ";
    }
    
    cout << "\nTotal head movement: " << total_movement << endl;
}

void C_SCAN(const vector<int>& requests, int head) {
    vector<int> left;
    vector<int> right;
    int total_movement = 0;
    int current_head = head;

    for (int request : requests) {
        if (request < head) {
            left.push_back(request);
        } else {
            right.push_back(request);
        }
    }

    sort(left.begin(), left.end());
    sort(right.begin(), right.end());
    
    cout << "\n[C-SCAN]\nHead movement:\n" << head << " -> ";
    
    for (int request : right) {
        total_movement += abs(current_head - request);
        current_head = request;
        cout << current_head << " -> ";
    }
    
    if (!left.empty()) {
        total_movement += current_head;
        current_head = 0;
        cout << "0 -> ";

        for (int request : left) {
            total_movement += abs(current_head - request);
            current_head = request;
            cout << current_head << " -> ";
        }
    }
    
    cout << "\nTotal head movement: " << total_movement << endl;
}

int main() {
    int n, head, choice;
    
    cout << "Enter the number of requests: ";
    cin >> n;
    
    vector<int> requests(n);
    
    cout << "Enter the request queue:\n";
    for (int i = 0; i < n; i++) {
        cin >> requests[i];
    }
    
    cout << "Enter the initial position of the head: ";
    cin >> head;
    
    do {
        cout << "\n==== Disk Scheduling Algorithms ====\n";
        cout << "1. FCFS (First Come First Served)\n";
        cout << "2. SSTF (Shortest Seek Time First)\n";
        cout << "3. SCAN (Elevator Algorithm)\n";
        cout << "4. C-SCAN (Circular SCAN)\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        
        switch (choice) {
            case 1:
                FCFS(requests, head);
                break;
                
            case 2:
                SSTF(requests, head);
                break;
                
            case 3:
                SCAN(requests, head);
                break;
                
            case 4:
                C_SCAN(requests, head);
                break;
                
            case 0:
                cout << "Exiting program...\n";
                break;
                
            default:
                cout << "Invalid choice! Please try again.\n";
        }
    } while (choice != 0);
    
    return 0;
}

  
