#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *file;  
    char filename[] = "example.txt";  
    char content[] = "Hello, world!\nThis is a simple file management example.\n";

  
    file = fopen(filename, "w");
    if (file == NULL) {
        perror("Error creating file");
        return 1;
    }

    
    if (fputs(content, file) == EOF) {
        perror("Error writing to file");
        fclose(file);
        return 1;
    }

   
    fclose(file);

   
    file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file for reading");
        return 1;
    }

    
    char buffer[1024];
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        printf("%s", buffer);
    }

   
   
    fclose(file);

    return 0;
}
