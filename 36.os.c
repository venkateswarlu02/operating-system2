#include <stdio.h>
#include <stdlib.h>

// Define the structure of a disk block
typedef struct Block {
    int data;
    struct Block* next;
} Block;

// Function to create a new block
Block* createBlock(int data) {
    Block* newBlock = (Block*)malloc(sizeof(Block));
    if (newBlock) {
        newBlock->data = data;
        newBlock->next = NULL;
    }
    return newBlock;
}

// Function to allocate a block to a file
void allocateBlock(Block** file, int data) {
    Block* newBlock = createBlock(data);
    if (*file == NULL) {
        *file = newBlock;
    } else {
        Block* currentBlock = *file;
        while (currentBlock->next != NULL) {
            currentBlock = currentBlock->next;
        }
        currentBlock->next = newBlock;
    }
}

// Function to print the content of a file
void printFile(Block* file) {
    Block* currentBlock = file;
    while (currentBlock != NULL) {
        printf("%d -> ", currentBlock->data);
        currentBlock = currentBlock->next;
    }
    printf("NULL\n");
}

// Function to deallocate the blocks of a file
void deallocateFile(Block** file) {
    Block* currentBlock = *file;
    while (currentBlock != NULL) {
        Block* nextBlock = currentBlock->next;
        free(currentBlock);
        currentBlock = nextBlock;
    }
    *file = NULL;
}

int main() {
    Block* file = NULL;

    // Simulate allocation of blocks
    allocateBlock(&file, 1);
    allocateBlock(&file, 2);
    allocateBlock(&file, 3);

    // Print the content of the file
    printf("File content:\n");
    printFile(file);

    // Deallocate the file blocks
    deallocateFile(&file);

    return 0;
}
