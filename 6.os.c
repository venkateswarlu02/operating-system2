#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int process_id;
    int arrival_time;
    int burst_time;
    int priority;
    int remaining_time;
} Process;

typedef struct {
    int front, rear;
    Process *array;
} PriorityQueue;

PriorityQueue* createPriorityQueue(int capacity) {
    PriorityQueue* queue = (PriorityQueue*)malloc(sizeof(PriorityQueue));
    queue->front = queue->rear = -1;
    queue->array = (Process*)malloc(capacity * sizeof(Process));
    return queue;
}

void enqueue(PriorityQueue *queue, Process process) {
    if (queue->rear == -1) {
        queue->front = queue->rear = 0;
        queue->array[queue->rear] = process;
    } else {
        int i = queue->rear;
        while (i >= 0 && queue->array[i].priority > process.priority) {
            queue->array[i + 1] = queue->array[i];
            i--;
        }
        i++;
        queue->array[i] = process;
        queue->rear++;
    }
}

Process dequeue(PriorityQueue *queue) {
    if (queue->front == -1) {
        Process empty_process = { -1, -1, -1, -1, -1 };
        return empty_process;
    }

    Process process = queue->array[queue->front];
    if (queue->front == queue->rear) {
        queue->front = queue->rear = -1;
    } else {
        queue->front++;
    }
    return process;
}

int isQueueEmpty(PriorityQueue *queue) {
    return queue->front == -1;
}

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    PriorityQueue *ready_queue = createPriorityQueue(n);
    Process *processes = (Process *)malloc(n * sizeof(Process));

    for (int i = 0; i < n; i++) {
        printf("Enter arrival time, burst time, and priority for Process %d: ", i + 1);
        scanf("%d %d %d", &processes[i].arrival_time, &processes[i].burst_time, &processes[i].priority);
        processes[i].process_id = i + 1;
        processes[i].remaining_time = processes[i].burst_time;
    }

    int current_time = 0;
    int completed_processes = 0;
    Process running_process = { -1, -1, -1, -1, -1 };

    printf("Process Execution Order:\n");

    while (completed_processes < n) {
        for (int i = 0; i < n; i++) {
            if (processes[i].arrival_time <= current_time && processes[i].remaining_time > 0) {
                enqueue(ready_queue, processes[i]);
            }
        }

        if (!isQueueEmpty(ready_queue)) {
            Process next_process = dequeue(ready_queue);

            if (next_process.process_id != running_process.process_id) {
                if (running_process.process_id != -1) {
                    enqueue(ready_queue, running_process);
                }
                running_process = next_process;
                printf("Time %d: Executing Process %d\n", current_time, running_process.process_id);
            }

            running_process.remaining_time--;

            if (running_process.remaining_time == 0) {
                completed_processes++;
                running_process.process_id = -1;
            }
        } else {
            printf("Time %d: CPU Idle\n", current_time);
        }

        current_time++;
    }

    free(processes);
    free(ready_queue->array);
    free(ready_queue);

    return 0;
}
