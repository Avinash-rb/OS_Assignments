//4_Prioirity Non Preemptive
#include <iostream>
#include <vector>
#include <climits>
#include <iomanip>
#include<algorithm>
using namespace std;

struct Process {
    int pid, arrival_time, burst_time, priority;
    int completion_time, turnaround_time, waiting_time;
    bool is_completed = false;
};

void calculate_times(vector<Process>& p) {
    int time = 0, completed = 0, n = p.size();

    while (completed != n) {
        int idx = -1;
        int lowest_priority = INT_MAX;

        for (int i = 0; i < n; i++) {
            if (p[i].arrival_time <= time && !p[i].is_completed) {
                if (p[i].priority < lowest_priority || 
                    (p[i].priority == lowest_priority && p[i].arrival_time < p[idx].arrival_time)) {
                    lowest_priority = p[i].priority;
                    idx = i;
                }
            }
        }

        if (idx == -1) {
            time++;
            continue;
        }

        p[idx].completion_time = time + p[idx].burst_time;
        p[idx].turnaround_time = p[idx].completion_time - p[idx].arrival_time;
        p[idx].waiting_time = p[idx].turnaround_time - p[idx].burst_time;
        p[idx].is_completed = true;
        completed++;
        time = p[idx].completion_time;
    }
}

void print_gantt(const vector<Process>& proc) {
    vector<Process> p = proc;

    sort(p.begin(), p.end(), [](Process a, Process b) {
        return (a.completion_time - a.burst_time) < (b.completion_time - b.burst_time);
    });

    cout << "\nGantt Chart:\n ";
    for (auto& pr : p) {
        for (int j = 0; j < pr.burst_time; j++) cout << "--";
        cout << " ";
    }
    cout << "\n|";
    for (auto& pr : p) {
        for (int j = 0; j < pr.burst_time  - 1; j++) cout << " ";
        cout << "P" << pr.pid;
        for (int j = 0; j < pr.burst_time - 1 ; j++) cout << " ";
        cout << "|";
    }
    cout << "\n ";
    for (auto& pr : p) {
        for (int j = 0; j < pr.burst_time; j++) cout << "--";
        cout << " ";
    }
    cout << "\n";

    cout << p[0].completion_time - p[0].burst_time;
    for (auto& pr : p) {
        for (int j = 0; j < pr.burst_time ; j++) cout << "  ";
        cout  << pr.completion_time;
    }
    cout << "\n";
}

void print_results(const vector<Process>& p) {
    float avg_wait = 0, avg_tat = 0;

    cout << "\nProcess Details:\n";
    cout << "Process\tPriority\tArrival\tBurst\tCompletion\tWaiting\tTurnaround\n";
    cout << "--------------------------------------------------------------------------\n";

    for (auto& pr : p) {
        cout << "P" << pr.pid << "\t" << pr.priority << "\t\t"
             << pr.arrival_time << "\t" << pr.burst_time << "\t"
             << pr.completion_time << "\t\t" << pr.waiting_time << "\t"
             << pr.turnaround_time << "\n";
        avg_wait += pr.waiting_time;
        avg_tat += pr.turnaround_time;
    }

    cout << "--------------------------------------------------------------------------\n";
    cout << fixed << setprecision(2);
    cout << "Average Waiting Time: " << avg_wait / p.size() << endl;
    cout << "Average Turnaround Time: " << avg_tat / p.size() << endl;
}

int main() {
    int n;
    cout << "Enter number of processes: ";
    cin >> n;

    vector<Process> p(n);
    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;
        cout << "\nEnter details for Process " << p[i].pid << ":\n";
        cout << "Arrival Time: ";
        cin >> p[i].arrival_time;
        cout << "Burst Time: ";
        cin >> p[i].burst_time;
        cout << "Priority (lower number = higher priority): ";
        cin >> p[i].priority;
    }

    calculate_times(p);
    print_results(p);
    print_gantt(p);

    return 0;
}
