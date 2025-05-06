//4.SRTF
#include <iostream>
#include <vector>
#include <limits>
#include <iomanip>

using namespace std;

struct Process {
    int pid, burst_time, arrival_time;
    int waiting_time = 0, turnaround_time = 0, completion_time = 0;
    int remaining_time = 0;
};

void calculate_times(vector<Process>& p, vector<int>& gantt, vector<int>& stamps) {
    int time = 0, done = 0, size = 0;
    int n = p.size();

    while (done != n) {
        int shortest = -1;
        int min_rem = INT_MAX;

        for (int i = 0; i < n; i++) {
            if (p[i].arrival_time <= time && p[i].remaining_time > 0 && p[i].remaining_time < min_rem) {
                min_rem = p[i].remaining_time;
                shortest = i;
            }
        }

        if (shortest == -1) {
            time++;
            continue;
        }

        if (gantt.empty() || gantt.back() != p[shortest].pid) {
            gantt.push_back(p[shortest].pid);
            stamps.push_back(time);
        }

        p[shortest].remaining_time--;
        time++;

        if (p[shortest].remaining_time == 0) {
            done++;
            p[shortest].completion_time = time;
            p[shortest].turnaround_time = time - p[shortest].arrival_time;
            p[shortest].waiting_time = p[shortest].turnaround_time - p[shortest].burst_time;
        }
    }
    stamps.push_back(time); 
}

void print_results(const vector<Process>& p) {
    float avg_wait = 0, avg_tat = 0;
    cout << "\nProcess\tArrival\tBurst\tCompletion\tWaiting\tTurnaround\n";

    for (const auto& proc : p) {
        cout << "P" << proc.pid << "\t" << proc.arrival_time << "\t" << proc.burst_time << "\t"
             << proc.completion_time << "\t\t" << proc.waiting_time << "\t" << proc.turnaround_time << "\n";
        avg_wait += proc.waiting_time;
        avg_tat += proc.turnaround_time;
    }

    cout << fixed << setprecision(2);
    cout << "\nAverage Waiting Time: " << avg_wait / p.size();
    cout << "\nAverage Turnaround Time: " << avg_tat / p.size() << "\n";
}

void print_gantt(const vector<int>& gantt, const vector<int>& stamps) {
    cout << "\nGantt Chart:\n";

    for (int i = 0; i < gantt.size(); i++) {
        cout << "+";
        for (int j = stamps[i]; j < stamps[i + 1]; j++) cout << "-";
    }
    cout << "+\n";

    for (int i = 0; i < gantt.size(); i++) {
        cout << "|";
        int len = stamps[i + 1] - stamps[i];
        int pad = (len - 1) / 2;
        for (int j = 0; j < pad; j++) cout << " ";
        cout << "P" << gantt[i];
        for (int j = 0; j < (len - 1) - pad; j++) cout << " ";
    }
    cout << "|\n";

    for (int i = 0; i < gantt.size(); i++) {
        cout << "+";
        for (int j = stamps[i]; j < stamps[i + 1]; j++) cout << "-";
    }
    cout << "+\n";

    cout << stamps[0];
    for (int i = 0; i < gantt.size(); i++) {
        int len = stamps[i + 1] - stamps[i];
        for (int j = 0; j < len; j++) cout << " ";
        cout << stamps[i + 1];
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
        cout << "\nEnter details for Process " << processes[i].pid << ":\n";
        cout << "Arrival Time: ";
        cin >> processes[i].arrival_time;
        cout << "Burst Time: ";
        cin >> processes[i].burst_time;
        processes[i].remaining_time = processes[i].burst_time;
    }

    vector<int> gantt, stamps;
    calculate_times(processes, gantt, stamps);
    print_results(processes);
    print_gantt(gantt, stamps);

    return 0;
}
