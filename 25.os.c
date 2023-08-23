#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>

int main() {
    // Open a file using open and fcntl
    int fd = open("io_example.txt", O_RDWR | O_CREAT, 0644);
    if (fd == -1) {
        perror("Error opening file");
        return 1;
    }
    printf("File opened successfully.\n");

    // Use fcntl to set the file status flags
    int flags = fcntl(fd, F_GETFL, 0);
    if (flags == -1) {
        perror("Error getting file flags");
        close(fd);
        return 1;
    }
    flags |= O_APPEND;  // Append mode
    if (fcntl(fd, F_SETFL, flags) == -1) {
        perror("Error setting file flags");
        close(fd);
        return 1;
    }
    printf("File flags set to append mode.\n");

    // Write data to the file
    const char *data = "Hello, I/O!\n";
    ssize_t bytes_written = write(fd, data, strlen(data));
    if (bytes_written == -1) {
        perror("Error writing to file");
        close(fd);
        return 1;
    }
    printf("Data written to the file: %s", data);

    // Perform lseek to move the file pointer
    off_t offset = lseek(fd, 0, SEEK_SET);
    if (offset == -1) {
        perror("Error seeking in file");
        close(fd);
        return 1;
    }

    // Use stat to retrieve file information
    struct stat file_info;
    if (stat("io_example.txt", &file_info) == -1) {
        perror("Error getting file information");
        close(fd);
        return 1;
    }
    printf("File size: %ld bytes\n", file_info.st_size);

    // Open a directory using opendir
    DIR *dir = opendir(".");
    if (dir == NULL) {
        perror("Error opening directory");
        return 1;
    }
    printf("Directory opened successfully.\n");

    // Use readdir to read directory entries
    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        printf("Entry: %s\n", entry->d_name);
    }

    // Close the directory
    closedir(dir);

    // Close the file
    close(fd);

    return 0;
}
