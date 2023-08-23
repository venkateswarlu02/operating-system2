#include <stdio.h>
#include <stdbool.h>

typedef struct {
    int process_id;
    int arrival_time;
    int burst_time;
    int remaining_time;
} Process;

void roundRobin(Process processes[], int n, int time_quantum) {
    int total_waiting_time = 0;
    int total_turnaround_time = 0;
    int current_time = 0;
    int completed_processes = 0;

    while (completed_processes < n) {
        bool process_executed = false;

        for (int i = 0; i < n; i++) {
            if (processes[i].remaining_time > 0 && processes[i].arrival_time <= current_time) {
                process_executed = true;

                if (processes[i].remaining_time <= time_quantum) {
                    current_time += processes[i].remaining_time;
                    processes[i].remaining_time = 0;
                } else {
                    current_time += time_quantum;
                    processes[i].remaining_time -= time_quantum;
                }

                printf("Time %d: Executing Process %d\n", current_time, processes[i].process_id);

                if (processes[i].remaining_time == 0) {
                    int turnaround_time = current_time - processes[i].arrival_time;
                    int waiting_time = turnaround_time - processes[i].burst_time;
                    total_turnaround_time += turnaround_time;
                    total_waiting_time += waiting_time;
                    completed_processes++;
                }
            }
        }

        if (!process_executed) {
            current_time++;
        }
    }

    float avg_turnaround_time = (float) total_turnaround_time / n;
    float avg_waiting_time = (float) total_waiting_time / n;

    printf("\nAverage Turnaround Time: %.2f\n", avg_turnaround_time);
    printf("Average Waiting Time: %.2f\n", avg_waiting_time);
}

int main() {
    int n, time_quantum;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    Process processes[n];

    for (int i = 0; i < n; i++) {
        printf("Enter arrival time and burst time for Process %d: ", i + 1);
        scanf("%d %d", &processes[i].arrival_time, &processes[i].burst_time);
        processes[i].process_id = i + 1;
        processes[i].remaining_time = processes[i].burst_time;
    }

    printf("Enter the time quantum: ");
    scanf("%d", &time_quantum);

    roundRobin(processes, n, time_quantum);

    return 0;
}
