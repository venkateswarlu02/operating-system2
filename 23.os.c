#include <stdio.h>

#define MAX_MEMORY_SIZE 1000

// Structure to represent a memory block
struct MemoryBlock {
    int id;
    int size;
};

// Function to allocate memory using first-fit algorithm
void firstFit(struct MemoryBlock memory[], int numBlocks, int processSize) {
    for (int i = 0; i < numBlocks; i++) {
        if (memory[i].size >= processSize) {
            memory[i].size -= processSize;
            printf("Process allocated to Memory Block %d of size %d\n", memory[i].id, processSize);
            return; // Allocation successful, exit the function
        }
    }

    printf("Memory allocation failed for process of size %d\n", processSize);
}

int main() {
    int numBlocks;
    printf("Enter the number of memory blocks: ");
    scanf("%d", &numBlocks);

    struct MemoryBlock memory[numBlocks];

    // Initialize memory blocks
    for (int i = 0; i < numBlocks; i++) {
        memory[i].id = i + 1;
        printf("Enter size of Memory Block %d: ", memory[i].id);
        scanf("%d", &memory[i].size);
    }

    int numProcesses;
    printf("Enter the number of processes: ");
    scanf("%d", &numProcesses);

    for (int i = 0; i < numProcesses; i++) {
        int processSize;
        printf("Enter size of Process %d: ", i + 1);
        scanf("%d", &processSize);

        firstFit(memory, numBlocks, processSize);
    }

    return 0;
}
