#include <stdio.h>
#include <stdlib.h>

#define MAX_BLOCKS 100
#define MAX_FILES 10

// Index block structure
struct IndexBlock {
    int pointers[MAX_BLOCKS];
};

// File structure
struct File {
    int numBlocks;
    struct IndexBlock indexBlock;
};

// Function to allocate blocks for a file
void allocateBlocks(struct File *file) {
    for (int i = 0; i < file->numBlocks; i++) {
        file->indexBlock.pointers[i] = rand() % MAX_BLOCKS; // Simulating block allocation
    }
}

// Function to print the index block of a file
void printIndexBlock(struct File *file) {
    printf("Index Block: [");
    for (int i = 0; i < file->numBlocks; i++) {
        printf(" %d", file->indexBlock.pointers[i]);
    }
    printf(" ]\n");
}

int main() {
    srand(time(NULL)); // Seed the random number generator
    
    struct File files[MAX_FILES];
    
    // Initialize files with random number of blocks
    for (int i = 0; i < MAX_FILES; i++) {
        files[i].numBlocks = rand() % (MAX_BLOCKS / 2) + 1; // Each file has at least 1 block
        allocateBlocks(&files[i]);
    }
    
    // Print the index blocks of all files
    for (int i = 0; i < MAX_FILES; i++) {
        printf("File %d:\n", i + 1);
        printIndexBlock(&files[i]);
    }
    
    return 0;
}
