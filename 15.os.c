#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FILES 10
#define MAX_FILENAME_LENGTH 50
#define MAX_SUBDIRECTORIES 5
#define MAX_SUBDIR_NAME_LENGTH 20


struct File {
    char filename[MAX_FILENAME_LENGTH];
};


struct Subdirectory {
    char name[MAX_SUBDIR_NAME_LENGTH];
    struct File files[MAX_FILES];
    int fileCount;
};


struct MainDirectory {
    struct Subdirectory subdirectories[MAX_SUBDIRECTORIES];
    int subdirCount;
};

int main() {
    struct MainDirectory mainDir;
    mainDir.subdirCount = 0;

    
    strcpy(mainDir.subdirectories[mainDir.subdirCount].name, "Subdir1");
    mainDir.subdirectories[mainDir.subdirCount].fileCount = 0;
    mainDir.subdirCount++;

   
    strcpy(mainDir.subdirectories[0].files[mainDir.subdirectories[0].fileCount].filename, "file1.txt");
    mainDir.subdirectories[0].fileCount++;

    strcpy(mainDir.subdirectories[0].files[mainDir.subdirectories[0].fileCount].filename, "file2.txt");
    mainDir.subdirectories[0].fileCount++;

    
    printf("Main Directory\n");
    printf("--------------------\n");
    for (int i = 0; i < mainDir.subdirCount; i++) {
        printf("Subdirectory: %s\n", mainDir.subdirectories[i].name);
        printf("Files: ");
        for (int j = 0; j < mainDir.subdirectories[i].fileCount; j++) {
            printf("%s ", mainDir.subdirectories[i].files[j].filename);
        }
        printf("\n");
        printf("--------------------\n");
    }

    return 0;
}
