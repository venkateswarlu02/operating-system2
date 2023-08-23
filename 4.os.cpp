#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int process_id;
    int arrival_time;
    int burst_time;
    int remaining_time;
} Process;

void swap(Process *a, Process *b) {
    Process temp = *a;
    *a = *b;
    *b = temp;
}

void sort_by_arrival_time(Process processes[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (processes[j].arrival_time > processes[j + 1].arrival_time) {
                swap(&processes[j], &processes[j + 1]);
            }
        }
    }
}

void shortest_job_next(Process processes[], int n) {
    sort_by_arrival_time(processes, n);

    int current_time = 0;
    int total_waiting_time = 0;
    int total_turnaround_time = 0;

    printf("Process Execution Order:\n");

    for (int i = 0; i < n; i++) {
        int shortest_job_index = -1;
        for (int j = 0; j < n; j++) {
            if (processes[j].arrival_time <= current_time && processes[j].remaining_time > 0) {
                if (shortest_job_index == -1 || processes[j].burst_time < processes[shortest_job_index].burst_time) {
                    shortest_job_index = j;
                }
            }
        }

        if (shortest_job_index == -1) {
            current_time++;
            i--; // No eligible process found, stay on the same iteration
            continue;
        }

        Process *selected_process = &processes[shortest_job_index];
        printf("Time %d: Executing Process %d\n", current_time, selected_process->process_id);

        current_time += selected_process->burst_time;
        selected_process->remaining_time = 0;

        int turnaround_time = current_time - selected_process->arrival_time;
        int waiting_time = turnaround_time - selected_process->burst_time;
        total_turnaround_time += turnaround_time;
        total_waiting_time += waiting_time;
    }

    float avg_turnaround_time = (float) total_turnaround_time / n;
    float avg_waiting_time = (float) total_waiting_time / n;

    printf("\nAverage Turnaround Time: %.2f\n", avg_turnaround_time);
    printf("Average Waiting Time: %.2f\n", avg_waiting_time);
}

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    Process *processes = (Process *) malloc(n * sizeof(Process));
    for (int i = 0; i < n; i++) {
        printf("Enter arrival time and burst time for Process %d: ", i + 1);
        scanf("%d %d", &processes[i].arrival_time, &processes[i].burst_time);
        processes[i].process_id = i + 1;
        processes[i].remaining_time = processes[i].burst_time;
    }

    shortest_job_next(processes, n);

    free(processes);

    return 0;
}
