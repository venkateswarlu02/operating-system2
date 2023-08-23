#include <stdio.h>
#include <stdbool.h>

#define MAX_PROCESSES 5
#define MAX_RESOURCES 3

int available[MAX_RESOURCES];
int max[MAX_PROCESSES][MAX_RESOURCES];
int allocation[MAX_PROCESSES][MAX_RESOURCES];
int need[MAX_PROCESSES][MAX_RESOURCES];

bool isSafeState(int process, int request[]) {
    int work[MAX_RESOURCES];
    int finish[MAX_PROCESSES] = {0};
    
    
    for (int i = 0; i < MAX_RESOURCES; ++i) {
        work[i] = available[i];
    }

    
    for (int i = 0; i < MAX_RESOURCES; ++i) {
        work[i] -= request[i];
        allocation[process][i] += request[i];
        need[process][i] -= request[i];
    }

  
    bool found = true;
    while (found) {
        found = false;
        for (int i = 0; i < MAX_PROCESSES; ++i) {
            if (!finish[i]) {
                bool canAllocate = true;
                for (int j = 0; j < MAX_RESOURCES; ++j) {
                    if (need[i][j] > work[j]) {
                        canAllocate = false;
                        break;
                    }
                }
                if (canAllocate) {
                    for (int j = 0; j < MAX_RESOURCES; ++j) {
                        work[j] += allocation[i][j];
                    }
                    finish[i] = 1;
                    found = true;
                }
            }
        }
    }

   
    for (int i = 0; i < MAX_PROCESSES; ++i) {
        if (!finish[i]) {
            return false; 
        }
    }

    return true; 
}

void requestResource(int process) {
    int request[MAX_RESOURCES];

    printf("Enter request for process P%d: ", process);
    for (int i = 0; i < MAX_RESOURCES; ++i) {
        scanf("%d", &request[i]);
    }

    if (isSafeState(process, request)) {
        printf("Request granted. Safe state maintained.\n");
    } else {
        printf("Request denied. Unsafe state detected.\n");
    }
}

int main() {
    
    int available[MAX_RESOURCES] = {3, 3, 2};
    int max[MAX_PROCESSES][MAX_RESOURCES] = {{7, 5, 3}, {3, 2, 2}, {9, 0, 2}, {2, 2, 2}, {4, 3, 3}};
    int allocation[MAX_PROCESSES][MAX_RESOURCES] = {{0, 1, 0}, {2, 0, 0}, {3, 0, 2}, {2, 1, 1}, {0, 0, 2}};
    int need[MAX_PROCESSES][MAX_RESOURCES];

    for (int i = 0; i < MAX_PROCESSES; ++i) {
        for (int j = 0; j < MAX_RESOURCES; ++j) {
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }

   
    for (int i = 0; i < MAX_PROCESSES; ++i) {
        requestResource(i);
    }

    return 0;
}
