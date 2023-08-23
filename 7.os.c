#include <stdio.h>

struct Process {
    int pid;
    int arrival_time;
    int burst_time;
    int completion_time;
    int turnaround_time;
    int waiting_time;
};

void calculateTimes(struct Process processes[], int n) {
    int total_waiting_time = 0;
    int total_turnaround_time = 0;

    processes[0].completion_time = processes[0].burst_time;
    processes[0].turnaround_time = processes[0].completion_time - processes[0].arrival_time;
    processes[0].waiting_time = 0;

    total_waiting_time += processes[0].waiting_time;
    total_turnaround_time += processes[0].turnaround_time;

    for (int i = 1; i < n; i++) {
        // Find the process with the shortest burst time among waiting processes
        int shortest_burst_index = i;
        for (int j = i + 1; j < n; j++) {
            if (processes[j].arrival_time <= processes[i - 1].completion_time && 
                processes[j].burst_time < processes[shortest_burst_index].burst_time) {
                shortest_burst_index = j;
            }
        }

        // Swap the processes to execute the one with the shortest burst time next
        struct Process temp = processes[i];
        processes[i] = processes[shortest_burst_index];
        processes[shortest_burst_index] = temp;

        // Calculate completion time, turnaround time, and waiting time for the selected process
        processes[i].completion_time = processes[i - 1].completion_time + processes[i].burst_time;
        processes[i].turnaround_time = processes[i].completion_time - processes[i].arrival_time;
        processes[i].waiting_time = processes[i].turnaround_time - processes[i].burst_time;

        total_waiting_time += processes[i].waiting_time;
        total_turnaround_time += processes[i].turnaround_time;
    }

    double average_waiting_time = (double) total_waiting_time / n;
    double average_turnaround_time = (double) total_turnaround_time / n;

    printf("PID\tArrival Time\tBurst Time\tCompletion Time\tTurnaround Time\tWaiting Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n",
               processes[i].pid, processes[i].arrival_time, processes[i].burst_time,
               processes[i].completion_time, processes[i].turnaround_time, processes[i].waiting_time);
    }
    printf("Average Turnaround Time: %.2lf\n", average_turnaround_time);
    printf("Average Waiting Time: %.2lf\n", average_waiting_time);
}

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process processes[n];

    printf("Enter arrival time and burst time for each process:\n");
    for (int i = 0; i < n; i++) {
        processes[i].pid = i + 1;
        printf("Process %d\n", i + 1);
        printf("Arrival Time: ");
        scanf("%d", &processes[i].arrival_time);
        printf("Burst Time: ");
        scanf("%d", &processes[i].burst_time);
    }

    calculateTimes(processes, n);

    return 0;
}
