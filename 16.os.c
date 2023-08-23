#include <stdio.h>
#include <stdlib.h>

#define FILENAME "employee_data.dat"
#define MAX_EMPLOYEES 100

struct Employee {
    int id;
    char name[50];
    float salary;
};

void writeEmployeeToFile(FILE *file, struct Employee emp) {
    fseek(file, (emp.id - 1) * sizeof(struct Employee), SEEK_SET);
    fwrite(&emp, sizeof(struct Employee), 1, file);
}

void readEmployeeFromFile(FILE *file, int id, struct Employee *emp) {
    fseek(file, (id - 1) * sizeof(struct Employee), SEEK_SET);
    fread(emp, sizeof(struct Employee), 1, file);
}

int main() {
    FILE *file = fopen(FILENAME, "r+");

    if (file == NULL) {
        file = fopen(FILENAME, "w+");
        if (file == NULL) {
            printf("Error creating the file.\n");
            return 1;
        }
    }

    int choice;
    do {
        printf("\n1. Add Employee\n");
        printf("2. Display Employee\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                if (ftell(file) / sizeof(struct Employee) >= MAX_EMPLOYEES) {
                    printf("Maximum number of employees reached.\n");
                } else {
                    struct Employee emp;
                    printf("Enter employee ID: ");
                    scanf("%d", &emp.id);
                    printf("Enter employee name: ");
                    scanf("%s", emp.name);
                    printf("Enter employee salary: ");
                    scanf("%f", &emp.salary);

                    writeEmployeeToFile(file, emp);
                    printf("Employee added successfully.\n");
                }
                break;

            case 2:
                printf("Enter employee ID to display: ");
                int id;
                scanf("%d", &id);

                struct Employee emp;
                readEmployeeFromFile(file, id, &emp);

                printf("Employee ID: %d\n", emp.id);
                printf("Employee Name: %s\n", emp.name);
                printf("Employee Salary: %.2f\n", emp.salary);
                break;

            case 3:
                printf("Exiting program.\n");
                break;

            default:
                printf("Invalid choice. Please enter a valid option.\n");
                break;
        }
    } while (choice != 3);

    fclose(file);
    return 0;
}
