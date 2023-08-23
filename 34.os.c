#include <stdio.h>
#include <stdlib.h>

#define MAX_RECORDS 100

// Simulated record structure
struct Record {
    int record_id;
    char data[50];
};

int main() {
    struct Record file[MAX_RECORDS];
    int num_records = 0;

    printf("Sequential File Allocation Simulation\n");

    while (1) {
        int choice;
        printf("\nMenu:\n");
        printf("1. Add Record\n");
        printf("2. Read Records\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: {
                if (num_records < MAX_RECORDS) {
                    printf("Enter data for record %d: ", num_records);
                    scanf("%s", file[num_records].data);
                    file[num_records].record_id = num_records;
                    num_records++;
                    printf("Record added.\n");
                } else {
                    printf("File is full, cannot add more records.\n");
                }
                break;
            }
            case 2: {
                printf("\nReading Records:\n");
                for (int i = 0; i < num_records; i++) {
                    printf("Record %d: %s\n", file[i].record_id, file[i].data);
                }
                break;
            }
            case 3: {
                printf("Exiting...\n");
                exit(0);
            }
            default: {
                printf("Invalid choice, please select again.\n");
                break;
            }
        }
    }

    return 0;
}
