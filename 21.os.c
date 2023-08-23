#include <stdio.h>

#define MAX_MEMORY_SIZE 1000


struct MemoryBlock {
    int id;
    int size;
};


void worstFit(struct MemoryBlock memory[], int numBlocks, int processSize) {
    int worstFitIdx = -1;
    int largestBlockSize = -1;

   
    for (int i = 0; i < numBlocks; i++) {
        if (memory[i].size >= processSize && memory[i].size > largestBlockSize) {
            worstFitIdx = i;
            largestBlockSize = memory[i].size;
        }
    }

    if (worstFitIdx != -1) {
        memory[worstFitIdx].size -= processSize;
        printf("Process allocated to Memory Block %d of size %d\n", memory[worstFitIdx].id, processSize);
    } else {
        printf("Memory allocation failed for process of size %d\n", processSize);
    }
}

int main() {
    int numBlocks;
    printf("Enter the number of memory blocks: ");
    scanf("%d", &numBlocks);

    struct MemoryBlock memory[numBlocks];

    
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

        worstFit(memory, numBlocks, processSize);
    }

    return 0;
}
