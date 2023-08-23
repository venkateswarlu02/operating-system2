#include <stdio.h>
#include <stdlib.h>

#define DIRECTION_LEFT -1
#define DIRECTION_RIGHT 1

// Function to simulate SCAN disk scheduling
void scan(int requests[], int numRequests, int initialPosition, int direction, int diskSize) {
    int totalSeekTime = 0;
    int currentPosition = initialPosition;

    printf("Sequence of disk head movement:\n");

    if (direction == DIRECTION_RIGHT) {
        // Move right
        for (int i = currentPosition; i <= diskSize; i++) {
            printf("%d -> ", i);
        }
        // Move back to 0
        for (int i = diskSize - 1; i >= 0; i--) {
            printf("%d -> ", i);
        }
    } else if (direction == DIRECTION_LEFT) {
        // Move left
        for (int i = currentPosition; i >= 0; i--) {
            printf("%d -> ", i);
        }
        // Move back to diskSize
        for (int i = 1; i <= diskSize; i++) {
            printf("%d -> ", i);
        }
    }

    printf("\nTotal seek time: %d\n", diskSize);

}

int main() {
    int numRequests;
    printf("Enter the number of disk requests: ");
    scanf("%d", &numRequests);

    int requests[numRequests];
    printf("Enter the disk request queue:\n");
    for (int i = 0; i < numRequests; i++) {
        scanf("%d", &requests[i]);
    }

    int initialPosition;
    printf("Enter the initial position of the disk head: ");
    scanf("%d", &initialPosition);

    int diskSize;
    printf("Enter the size of the disk: ");
    scanf("%d", &diskSize);

    int direction;
    printf("Enter the direction (left: -1, right: 1): ");
    scanf("%d", &direction);

    scan(requests, numRequests, initialPosition, direction, diskSize);

    return 0;
}
