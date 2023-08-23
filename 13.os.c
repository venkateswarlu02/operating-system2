#include <stdio.h>
#include <stdbool.h>

#define MEMORY_SIZE 1000

// Memory block structure
typedef struct {
    int start;
    int end;
    int size;
    bool allocated;
} MemoryBlock;

// Function prototypes
void initializeMemory(MemoryBlock memory[], int size);
void displayMemory(MemoryBlock memory[], int size);
void allocateFirstFit(MemoryBlock memory[], int size, int processSize);
void allocateBestFit(MemoryBlock memory[], int size, int processSize);
void allocateWorstFit(MemoryBlock memory[], int size, int processSize);

int main() {
    MemoryBlock memory[MEMORY_SIZE];
    int processSize;

    initializeMemory(memory, MEMORY_SIZE);
    displayMemory(memory, MEMORY_SIZE);

    printf("Enter process size: ");
    scanf("%d", &processSize);

    allocateFirstFit(memory, MEMORY_SIZE, processSize);
    displayMemory(memory, MEMORY_SIZE);

    allocateBestFit(memory, MEMORY_SIZE, processSize);
    displayMemory(memory, MEMORY_SIZE);

    allocateWorstFit(memory, MEMORY_SIZE, processSize);
    displayMemory(memory, MEMORY_SIZE);

    return 0;
}

void initializeMemory(MemoryBlock memory[], int size) {
    memory[0].start = 0;
    memory[0].end = size - 1;
    memory[0].size = size;
    memory[0].allocated = false;
}

void displayMemory(MemoryBlock memory[], int size) {
    printf("Memory Block:\n");
    for (int i = 0; i < size; i++) {
        printf("Block %d: Start = %d, End = %d, Size = %d, Allocated = %s\n",
               i, memory[i].start, memory[i].end, memory[i].size,
               memory[i].allocated ? "True" : "False");
    }
    printf("\n");
}

void allocateFirstFit(MemoryBlock memory[], int size, int processSize) {
    for (int i = 0; i < size; i++) {
        if (!memory[i].allocated && memory[i].size >= processSize) {
            memory[i].allocated = true;
            break;
        }
    }
}

void allocateBestFit(MemoryBlock memory[], int size, int processSize) {
    int bestFitIndex = -1;
    int bestFitSize = MEMORY_SIZE + 1;

    for (int i = 0; i < size; i++) {
        if (!memory[i].allocated && memory[i].size >= processSize &&
            memory[i].size < bestFitSize) {
            bestFitIndex = i;
            bestFitSize = memory[i].size;
        }
    }

    if (bestFitIndex != -1) {
        memory[bestFitIndex].allocated = true;
    }
}

void allocateWorstFit(MemoryBlock memory[], int size, int processSize) {
    int worstFitIndex = -1;
    int worstFitSize = -1;

    for (int i = 0; i < size; i++) {
        if (!memory[i].allocated && memory[i].size >= processSize &&
            memory[i].size > worstFitSize) {
            worstFitIndex = i;
            worstFitSize = memory[i].size;
        }
    }

    if (worstFitIndex != -1) {
        memory[worstFitIndex].allocated = true;
    }
}
