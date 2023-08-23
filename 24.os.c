#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>

int main() {
    int fd;         // File descriptor
    char buffer[50]; // Buffer for reading/writing data

    // Create a new file
    fd = creat("example.txt", 0644);
    if (fd == -1) {
        perror("Error creating file");
        return 1;
    }
    printf("File 'example.txt' created successfully.\n");

    // Write data to the file
    const char *data = "Hello, World!\n";
    ssize_t bytes_written = write(fd, data, strlen(data));
    if (bytes_written == -1) {
        perror("Error writing to file");
        close(fd);
        return 1;
    }
    printf("Data written to the file: %s", data);

    // Close the file
    close(fd);

    // Open the file for reading
    fd = open("example.txt", O_RDONLY);
    if (fd == -1) {
        perror("Error opening file");
        return 1;
    }

    // Read data from the file
    ssize_t bytes_read = read(fd, buffer, sizeof(buffer) - 1);
    if (bytes_read == -1) {
        perror("Error reading from file");
        close(fd);
        return 1;
    }
    buffer[bytes_read] = '\0'; // Null-terminate the string
    printf("Data read from the file: %s", buffer);

    // Close the file
    close(fd);

    // Delete the file
    if (unlink("example.txt") == -1) {
        perror("Error deleting file");
        return 1;
    }
    printf("File 'example.txt' deleted successfully.\n");

    return 0;
}
