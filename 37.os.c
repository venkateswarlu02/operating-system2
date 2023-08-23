#include <stdio.h>
#include <stdlib.h>

// Function to simulate FCFS disk scheduling
void fcfs(int requests[], int numRequests, int initialPosition) {
    int totalSeekTime = 0;
    int currentPosition = initialPosition;

    printf("Sequence of disk head movement:\n");
    printf("%d", currentPosition);

    for (int i = 0; i < numRequests; i++) {
        int seekDistance = abs(requests[i] - currentPosition);
        totalSeekTime += seekDistance;
        currentPosition = requests[i];

        printf(" -> %d", currentPosition);
    }

    printf("\nTotal seek time: %d\n", totalSeekTime);
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

    fcfs(requests, numRequests, initialPosition);

    return 0;
}
