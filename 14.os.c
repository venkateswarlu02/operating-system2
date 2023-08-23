#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FILES 100
#define MAX_FILENAME_LENGTH 50

typedef struct {
    char name[MAX_FILENAME_LENGTH];
} File;

typedef struct {
    File files[MAX_FILES];
    int numFiles;
} Directory;

void initializeDirectory(Directory *dir) {
    dir->numFiles = 0;
}

void addFile(Directory *dir, const char *filename) {
    if (dir->numFiles < MAX_FILES) {
        strcpy(dir->files[dir->numFiles].name, filename);
        dir->numFiles++;
        printf("File '%s' added to directory.\n", filename);
    } else {
        printf("Directory is full. Cannot add file '%s'.\n", filename);
    }
}

void listFiles(Directory *dir) {
    printf("Files in the directory:\n");
    for (int i = 0; i < dir->numFiles; i++) {
        printf("%d. %s\n", i + 1, dir->files[i].name);
    }
}

int main() {
    Directory directory;
    initializeDirectory(&directory);

    int choice;
    char filename[MAX_FILENAME_LENGTH];

    do {
        printf("\nMenu:\n");
        printf("1. Add a file\n");
        printf("2. List files\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter filename: ");
                scanf("%s", filename);
                addFile(&directory, filename);
                break;
            case 2:
                listFiles(&directory);
                break;
            case 3:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice.\n");
        }
    } while (choice != 3);

    return 0;
}
