//4 Prioirity Preemptive
#include <iostream>
#include <vector>
#include <climits>
#include <iomanip>
using namespace std;

struct Process {
    int pid, arrival_time, burst_time, priority;
    int remaining_time, completion_time, turnaround_time;
    int waiting_time, response_time, first_response;
};

void calculate_times(vector<Process>& p, vector<int>& gantt, vector<int>& stamps) {
    int n = p.size();
    int current_time = 0, completed = 0;
    stamps.clear(); gantt.clear();

    for (int i = 0; i < n; i++) {
        p[i].remaining_time = p[i].burst_time;
        p[i].first_response = -1;
    }

    while (completed != n) {
        int idx = -1, highest_priority = INT_MAX;

        for (int i = 0; i < n; i++) {
            if (p[i].arrival_time <= current_time && p[i].remaining_time > 0) {
                if (p[i].priority < highest_priority || 
                   (p[i].priority == highest_priority && p[i].arrival_time < p[idx].arrival_time)) {
                    highest_priority = p[i].priority;
                    idx = i;
                }
            }
        }

        if (idx == -1) {
            current_time++;
            continue;
        }

        if (p[idx].first_response == -1) {
            p[idx].first_response = current_time;
            p[idx].response_time = current_time - p[idx].arrival_time;
        }

        if (gantt.empty() || gantt.back() != p[idx].pid) {
            gantt.push_back(p[idx].pid);
            stamps.push_back(current_time);
        }

        p[idx].remaining_time--;
        current_time++;

        if (p[idx].remaining_time == 0) {
            completed++;
            p[idx].completion_time = current_time;
            p[idx].turnaround_time = p[idx].completion_time - p[idx].arrival_time;
            p[idx].waiting_time = p[idx].turnaround_time - p[idx].burst_time;
        }
    }
    stamps.push_back(current_time); 
}

void print_gantt_chart(const vector<int>& gantt, const vector<int>& stamps) {
    cout << "\nGantt Chart:\n";

    for (size_t i = 0; i < gantt.size(); ++i) {
        cout << "+";
        for (int j = 0; j < stamps[i + 1] - stamps[i]; ++j) cout << "--";
    }
    cout << "+\n";

    for (size_t i = 0; i < gantt.size(); ++i) {
        cout << "|";
        int len = stamps[i + 1] - stamps[i];
        for(int j = 0; j < len -1; j++) cout<<" ";
        cout << "P" << gantt[i];
        for (int j = 0; j < len - 1; j++) cout << " ";
    }
    cout << "|\n";

    for (size_t i = 0; i < gantt.size(); ++i) {
        cout << "+";
        for (int j = 0; j < stamps[i + 1] - stamps[i]; ++j) cout << "--";
    }
    cout << "+\n";

    cout << stamps[0];
    for (size_t i = 0; i < gantt.size(); ++i) {
        int space = stamps[i + 1] - stamps[i];
        for(int j =0; j < space; j++) cout<<"  ";
        cout << stamps[i + 1];
    }
    cout << "\n";
}

void print_process_info(const vector<Process>& p) {
    float avg_wait = 0, avg_turnaround = 0, avg_response = 0;
    cout << "\nProcess Details:\n";
    cout << "PID\tPriority Arrival Burst  Completion  Response  Waiting  Turnaround\n";
    for (const auto& proc : p) {
        cout << "P" << proc.pid << "\t" << proc.priority << "\t   "
             << proc.arrival_time << "\t  " << proc.burst_time << "\t  "
             << proc.completion_time << "\t    " << proc.response_time << "\t    "
             << proc.waiting_time << "\t    " << proc.turnaround_time << "\n";
        avg_wait += proc.waiting_time;
        avg_turnaround += proc.turnaround_time;
        avg_response += proc.response_time;
    }

    int n = p.size();
    cout << fixed << setprecision(2);
    cout << "Average Response Time: " << avg_response / n << "\n";
    cout << "Average Waiting Time: " << avg_wait / n << "\n";
    cout << "Average Turnaround Time: " << avg_turnaround / n << "\n";
}

int main() {
    int n;
    cout << "Enter number of processes: ";
    cin >> n;

    vector<Process> p(n);
    vector<int> gantt, stamps;

    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;
        cout << "\nEnter details for Process " << i + 1 << ":\n";
        cout << "Arrival Time: ";
        cin >> p[i].arrival_time;
        cout << "Burst Time: ";
        cin >> p[i].burst_time;
        cout << "Priority (lower number = higher priority): ";
        cin >> p[i].priority;
    }

    calculate_times(p, gantt, stamps);
    print_process_info(p);
    print_gantt_chart(gantt, stamps);

    return 0;
}
