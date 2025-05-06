//4_SJFS
#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm>

using namespace std;

struct Process {
    int pid;
    int burst_time;
    int arrival_time;
    int waiting_time = 0;
    int turnaround_time = 0;
    int completion_time = 0;
    bool is_completed = false;
};

void calculate_times(vector<Process> &processes) {
    int current_time = 0, completed = 0;
    int n = processes.size();

    while (completed != n) {
        int shortest = -1;
        int min_burst = INT_MAX;

        for (int i = 0; i < n; i++) {
            if (processes[i].arrival_time <= current_time && !processes[i].is_completed &&
                processes[i].burst_time < min_burst) {
                min_burst = processes[i].burst_time;
                shortest = i;
            }
        }

        if (shortest == -1) {
            current_time++;
            continue;
        }

        Process &p = processes[shortest];
        p.completion_time = current_time + p.burst_time;
        p.turnaround_time = p.completion_time - p.arrival_time;
        p.waiting_time = p.turnaround_time - p.burst_time;
        p.is_completed = true;
        completed++;
        current_time = p.completion_time;
    }
}

void print_results(const vector<Process> &processes) {
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

void print_gantt_chart(const vector<Process> &processes) {
    vector<Process> sorted = processes;
    sort(sorted.begin(), sorted.end(), [](const Process &a, const Process &b) {
        return (a.completion_time - a.burst_time) < (b.completion_time - b.burst_time);
    });

    cout << "\nGantt Chart:\n ";
    for (const auto &p : sorted)
        for (int j = 0; j < p.burst_time; ++j) cout << "--";
    cout << " \n|";

    for (const auto &p : sorted) {
        for (int j = 0; j < p.burst_time - 1; ++j) cout << " ";
        cout << "P" << p.pid;
        for (int j = 0; j < p.burst_time - 1; ++j) cout << " ";
        cout << "|";
    }

    cout << "\n ";
    for (const auto &p : sorted)
        for (int j = 0; j < p.burst_time; ++j) cout << "--";
    cout << " \n";

    cout << sorted[0].completion_time - sorted[0].burst_time;
    for (const auto &p : sorted) {
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

    calculate_times(processes);
    print_results(processes);
    print_gantt_chart(processes);

    return 0;
}
