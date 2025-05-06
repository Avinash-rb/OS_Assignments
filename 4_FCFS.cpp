//4_FCFS
#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
using namespace std;

struct Process {
    int pid, burst_time, arrival_time;
    int waiting_time = 0, turnaround_time = 0, completion_time = 0;
};

bool compare_arrival_time(const Process &a, const Process &b) {
    return a.arrival_time < b.arrival_time;
}

void calculate_times(vector<Process> &processes) {
    processes[0].completion_time = processes[0].arrival_time + processes[0].burst_time;
    processes[0].waiting_time = 0;
    processes[0].turnaround_time = processes[0].burst_time;

    for (size_t i = 1; i < processes.size(); ++i) {
        if (processes[i].arrival_time > processes[i - 1].completion_time) {
            processes[i].completion_time = processes[i].arrival_time + processes[i].burst_time;
            processes[i].waiting_time = 0;
        } else {
            processes[i].completion_time = processes[i - 1].completion_time + processes[i].burst_time;
            processes[i].waiting_time = processes[i - 1].completion_time - processes[i].arrival_time;
        }
        processes[i].turnaround_time = processes[i].completion_time - processes[i].arrival_time;
    }
}

void display_process_info(const vector<Process> &processes) {
    float total_waiting = 0, total_turnaround = 0;

    cout << "\nProcess\tArrival\tBurst\tCompletion\tWaiting\tTurnaround\n";
    for (const auto &p : processes) {
        cout << "P" << p.pid << "\t" << p.arrival_time << "\t" << p.burst_time << "\t"
             << p.completion_time << "\t\t" << p.waiting_time << "\t" << p.turnaround_time << "\n";
        total_waiting += p.waiting_time;
        total_turnaround += p.turnaround_time;
    }

    cout << fixed << setprecision(2);
    cout << "\nAverage Waiting Time: " << total_waiting / processes.size();
    cout << "\nAverage Turnaround Time: " << total_turnaround / processes.size() << "\n";
}

void display_gantt_chart(const vector<Process> &processes) {
    cout << "\nGantt Chart:\n ";
    for (const auto &p : processes)
        for (int j = 0; j < p.burst_time; ++j) cout << "--";
    cout << " \n|";

    for (const auto &p : processes) {
        for (int j = 0; j < p.burst_time - 1; ++j) cout << " ";
        cout << "P" << p.pid;
        for (int j = 0; j < p.burst_time - 1; ++j) cout << " ";
        cout << "|";
    }

    cout << "\n ";
    for (const auto &p : processes)
        for (int j = 0; j < p.burst_time; ++j) cout << "--";
    cout << " \n";

    cout << processes[0].arrival_time;
    for (const auto &p : processes) {
        for (int j = 0; j < p.burst_time; ++j) cout << "  ";
        cout << p.completion_time;
    }
    cout << "\n";
}

int main() {
    int n;
    cout << "Enter number of processes: ";
    cin >> n;

    vector<Process> processes(n);
    for (int i = 0; i < n; ++i) {
        processes[i].pid = i + 1;
        cout << "\nEnter details for Process " << i + 1 << ":\n";
        cout << "Arrival Time: ";
        cin >> processes[i].arrival_time;
        cout << "Burst Time: ";
        cin >> processes[i].burst_time;
    }

    cout << "\nBefore Sorting:\n";
    display_process_info(processes);

    sort(processes.begin(), processes.end(), compare_arrival_time);

    cout << "\nAfter Sorting:\n";
    display_process_info(processes);

    calculate_times(processes);

    cout << "\nFinal Results:\n";
    display_process_info(processes);

    display_gantt_chart(processes);

    return 0;
}
